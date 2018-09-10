/*
 * http_hdr.cpp
 *
 *  Created on: 2012-6-14
 *      Author: hy
 */
#include <cstdlib>
#include "common.h"
#include "http-hdr.h"

#include "loopbuffer.h"

typedef http_head::_value_pair_t _value_pair_t;
static void _reverse_list( _value_pair_t *&head ) {
	_value_pair_t *reordered_head = 0, *list = head;

	while( list ) {
		_value_pair_t * cur_node = list;
		list = cur_node->_next;
		cur_node->_next = reordered_head;
		reordered_head = cur_node;
	}
	head = reordered_head;
}
static inline int _hex_value( int c ) {
	if ( 'a' <= c && c <= 'f' ) {
		return c-'a' + 10;
	}
	if ( 'A' <= c && c <= 'F' ) {
		return c-'A' + 10;
	}
	if ( '0' <= c && c <= '9' ) {
		return c - '0';
	}
	return -1;
}
static inline bool _is_cr_lf(int c) {
	return c == '\r' || c == '\n';
}
static inline bool _is_space(int c) {
	return c == ' ' || c == '\t';
}
static inline bool _is_valid_char(int c) {
	return c >= 32 && c < 127;
}
static inline bool _is_number(int c) {
	return c >= '0' && c <= '9';
}
static const _value_pair_t *_find( const _value_pair_t *head, const char *param, const _value_pair_t *begin = 0 ) {
	if ( begin == 0 ) {
		begin = head;
	}
	while( begin ) {
		if ( begin->_name && strcasecmp( begin->_name, param ) == 0 ) {
			return begin;
		}
		begin = begin->_next;
	}
	return 0;
}

static int _find_int( _value_pair_t *head, const char *param, int defval = int() ) {
	const _value_pair_t *hdr = _find( head, param );
	if ( hdr ) {
		defval = atoi(hdr->_value);
	}
	return defval;
}
static const char * _find_string( _value_pair_t *head, const char *param, const char * defval = 0 ) {
	const _value_pair_t *hdr = _find( head, param );
	if ( hdr ) {
		defval = hdr->_value;
	}
	return defval;
}

template<typename _T>
static void _rebase_ptr( _T *&ptr, void *old_base, void *new_base ) {
	if ( ptr != 0 ) {
		ptr = reinterpret_cast<_T*>(reinterpret_cast<char*>(ptr) - reinterpret_cast<char*>(old_base) + reinterpret_cast<char*>(new_base));
	}
}
static void _rebase_ptr( _value_pair_t *&head, void *old_base, void *new_base ) {
	_rebase_ptr( *(char**)&head, old_base, new_base );
	_value_pair_t * node = head;
	while( node != 0 ) {
		_rebase_ptr( node->_name, old_base, new_base );
		_rebase_ptr( node->_value, old_base, new_base );
		_rebase_ptr( *(char**)&(node->_next), old_base, new_base );
		node = node->_next;
	}
}

http_head::http_head()
: _method(0), _url(0), _protocol(0), _msg(0), _code(-1), _query(0)
, _params(0), _max_len(_default_buffer_size), _data((char*)sdk_mem_malloc(_default_buffer_size))
, _parse_status(0), _parse_pos(0), _write_pos(0)
{}
http_head::~http_head() {
	sdk_mem_free(_data);
}
// return value
// -1 error
// >= 0 number of bytes parsed
int http_head::parse( const char*buf, int len ) {
	static const unsigned long METHOD_HTTP = *(unsigned long*)"HTTP";
	static const unsigned long METHOD_RTSP = *(unsigned long*)"RTSP";

	int read_len = 0;
	while( read_len < len && _parse_status != STATE_PARSE_FINISHED) {
		char c = buf[read_len];
		if ( _write_pos >= _max_len && !_enlarge_buffer(_default_buffer_size/2) ) {
			// failed enlarge buffer
			return -13;
		}
		switch( _parse_status ) {
		case 0:	// read method
			if ( _is_space(c) ) {
				// end of method
				_data[_write_pos] = 0;
				++_write_pos;
				if ( _write_pos - _parse_pos <= 1 ) {
					// method field is empty!!!
					return -1;
				}
				_method = _data + _parse_pos;
				_parse_pos = _write_pos;
				unsigned long methodVal = *(unsigned long*)_method;
				if ((methodVal == METHOD_HTTP || methodVal == METHOD_RTSP) && _method[4] == '/') {
					_type = RESPONSE;
					_protocol = _method;
					// parse code
					_parse_status = 6;
				} else {
					_type = REQUEST;
					// parse url
					_parse_status = 1;
				}
			} else if ( _is_valid_char(c) ) {
				_data[_write_pos] = toupper(c);
				++_write_pos;
			} else {
				// not acceptable
				return -2;
			}
			break;
		case 1:	// parse url
			if ( _url == 0 ) {
				if ( _is_space(c) ) {
					// trim front space
					break;
				} else {
					_url = _data + _parse_pos;
				}
			}
			_raw_url.push_back(c);
			if ( _is_space(c) ) {
				// end of url
				_data[_write_pos] = 0;
				++_write_pos;
				_parse_pos = _write_pos;
				// parse protocol
				_parse_status = 2;
			} else if ( c == '?' ) {
				// has query string
				_data[_write_pos] = 0;
				++_write_pos;

				_query = _alloc_value_pair();
				if ( _query == 0 ) {
					// out of memory
					return -1;
				}
				_parse_pos = _write_pos;
				// parse query string
				_parse_status = 3;
			} else if ( _write_pos - _parse_pos == 2 && _data[_parse_pos] == '%' && _hex_value(c) >= 0 && _hex_value(_data[_parse_pos+1]) >= 0 ) {
				// unescape character
				int lo = _hex_value(c);
				int hi = _hex_value(_data[_parse_pos+1]);
				_data[_parse_pos] = (hi<<4)+lo;
				++_parse_pos;
				_write_pos = _parse_pos;
			} else if ( _is_valid_char(c) ) {
				_data[_write_pos] = c;
				if ( c == '%' ) {
					_parse_pos = _write_pos;
				}
				++_write_pos;
			} else {
				// not acceptable
				return -3;
			}
			break;
		case 2:	// parse protocol
			if ( _protocol == 0 ) {
				if ( _is_space(c) ) {
					// trim front spaces
					break;
				} else {
					_protocol = _data + _parse_pos;
				}
			}
			if ( _is_space(c) && !_is_cr_lf(_data[_parse_pos]) ) {
				// trim back spaces;
				break;
			}
			if ( _is_cr_lf(c) ) {
				if ( _parse_pos != _write_pos && _is_cr_lf(_data[_parse_pos]) ) {
					if ( _data[_parse_pos] != c ) {
						// end of protocol with '\r\n' or '\n\r'
						_data[_parse_pos] = 0;
						_parse_pos = _write_pos;
						// parse parameters
						_parse_status = 4;
						break;
					} else {
						// end of protocol with '\r' or '\n'
						_data[_parse_pos] = 0;
						_parse_pos = _write_pos;
						// parse parameters
						_parse_status = 4;
						// current 'c' not accepted, parse again
						continue;
					}
				} else {
					_data[_write_pos] = c;
					_parse_pos = _write_pos;
					++_write_pos;
				}
			} else if ( _is_valid_char(c) ) {
				_data[_write_pos] = c;
				++_write_pos;
			} else {
				// not acceptable
				return -4;
			}
			break;
		case 3:	// parse query string
			if ( _is_space(c) ) {
				// end of query string
				if ( _query->_name == _data + _write_pos ) {
					// empty name
					_query->_name = 0;
				} else if ( _query->_name != 0 ) {
					if ( _query->_value == 0 ) {
						_query->_value = _data + _parse_pos;
					}
					_data[_write_pos] = 0;
					++_write_pos;
					_parse_pos = _write_pos;
				}
				// parse protocol
				_parse_status = 2;
				break;
			}
			_raw_url.push_back(c);
			if ( _query->_name == 0 ) {
				_query->_name = _data + _parse_pos;
			}
			if ( _write_pos - _parse_pos == 2 && _data[_parse_pos] == '%' && _hex_value(c) >= 0 && _hex_value(_data[_parse_pos+1]) >= 0 ) {
				// unescape character
				int lo = _hex_value(c);
				int hi = _hex_value(_data[_parse_pos+1]);
				_data[_parse_pos] = (hi<<4)+lo;
				++_parse_pos;
				_write_pos = _parse_pos;
			} else if ( _query->_value == 0 && c == '=' ) {
				_data[_write_pos] = 0;
				++_write_pos;
				_parse_pos = _write_pos;
				_query->_value = _data + _parse_pos;
			} else if ( c == '&' ) {
				// end of value pair
				if ( _query->_name == _data + _write_pos ) {
					_query->_name = 0;
					break;
				}
				_data[_write_pos] = 0;
				++_write_pos;
				_parse_pos = _write_pos;

				if ( _write_pos >= _max_len && !_enlarge_buffer(_default_buffer_size/2) ) {
					// failed enlarge buffer
					return -5;
				}

				if ( _query->_value == 0 ) {
					_query->_value = _data + _parse_pos;
					_data[_write_pos] = 0;
					++_write_pos;
					_parse_pos = _write_pos;
				}

				_value_pair_t *obj = _alloc_value_pair();
				obj->_next = _query;
				_query = obj;
			} else if ( _is_valid_char(c) ) {
				_data[_write_pos] = c;
				if ( c == '%' ) {
					// prepare decode escaped string
					_parse_pos = _write_pos;
				}
				++_write_pos;
			} else {
				// not acceptable
				return -6;
			}
			break;
		case 4:	// parse parameters
			if ( _params == 0 ) {
				_params = _alloc_value_pair();
				if ( _params == 0 ) {
					// out of memory
					return -7;
				}
			}
			if ( _params->_name == 0 ) {
				if ( _is_space(c) ) {
					// trim
					break;
				} else if ( _is_cr_lf(c) ) {
					// parse empty line
					_parse_status = 5;
					_parse_pos = _write_pos;
					// parse current c again
					continue;
				} else {
					_params->_name = _data + _parse_pos;
				}
			}
			if ( _params->_value == 0 ) {
				if ( c == ':' ) {
					// end of parameter name
					_data[_write_pos] = 0;
					++_write_pos;
					_parse_pos = _write_pos;
					_params->_value = _data + _parse_pos;
				} else if ( _is_valid_char(c) ) {
					_data[_write_pos] = c;
					++_write_pos;
				} else {
					// not acceptable
					_parse_status = STATE_PARSE_FINISHED;
					return -8;
				}
			} else {
				// parse value
				if ( _data + _write_pos == _params->_value && _is_space(c) ) {
					// trim front spaces
					break;
				}
				if ( _is_cr_lf(c) ) {
					if ( _parse_pos != _write_pos && _is_cr_lf(_data[_parse_pos]) ) {
						if ( _data[_parse_pos] != c ) {
							// end of value with '\r\n' or '\n\r'
							_data[_parse_pos] = 0;
							_parse_pos = _write_pos;

							_value_pair_t *obj = _alloc_value_pair();
							obj->_next = _params;
							_params = obj;
						} else {
							// end of value with '\r' or '\n'
							_data[_parse_pos] = 0;
							_parse_pos = _write_pos;

							_value_pair_t *obj = _alloc_value_pair();
							obj->_next = _params;
							_params = obj;

							// current 'c' not accepted, parse again
							continue;
						}
					} else {
						_data[_write_pos] = c;
						_parse_pos = _write_pos;
						++_write_pos;
					}
				} else if ( _is_valid_char(c) ) {
					_data[_write_pos] = c;
					++_write_pos;
				} else {
					// not acceptable
					return -9;
				}
			}
			break;
		case 5:	// parse empty line
			if ( _is_cr_lf(c) ) {
				if ( _parse_pos != _write_pos && _is_cr_lf(_data[_parse_pos]) ) {
					_reverse_list(_query);
					_reverse_list(_params);
					// parse end
					_parse_status = STATE_PARSE_FINISHED;
					if ( _data[_parse_pos] != c ) {
						// end of protocol with '\r\n' or '\n\r'
						break;
					} else {
						// end of protocol with '\r' or '\n'
						// current 'c' not accepted, parse again
						continue;
					}
				} else {
					_data[_write_pos] = c;
					_parse_pos = _write_pos;
					++_write_pos;
				}
			} else {
				// not acceptable
				return -10;
			}
			break;
		case 6:	// parse response code
			if ( _is_space(c) || _is_cr_lf(c) ) {
				_data[_write_pos] = 0;
				++_write_pos;
				unsigned int code = 0;
				while( _data[_parse_pos] && _parse_pos < _write_pos ) {
					code = code*10 + _data[_parse_pos] - '0';
					++_parse_pos;
				}
				_code = code;

				_parse_pos = _write_pos;
				_msg = _data + _parse_pos;
				// parse response msg
				_parse_status = 7;
				if ( _is_cr_lf(c) ) {
					continue;
				}
			} else if ( _is_number(c) ) {
				_data[_write_pos] = c;
				++_write_pos;
			} else {
				// not acceptable
				return -11;
			}
			break;
		case 7:	// parse response msg
			if ( _is_cr_lf(c) ) {
				if ( _parse_pos != _write_pos && _is_cr_lf(_data[_parse_pos]) ) {
					if ( _data[_parse_pos] != c ) {
						// end of protocol with '\r\n' or '\n\r'
						_data[_parse_pos] = 0;
						_parse_pos = _write_pos;
						// parse parameters
						_parse_status = 4;
						break;
					} else {
						// end of protocol with '\r' or '\n'
						_data[_parse_pos] = 0;
						_parse_pos = _write_pos;
						// parse parameters
						_parse_status = 4;
						// current 'c' not accepted, parse again
						continue;
					}
				} else {
					_data[_write_pos] = c;
					_parse_pos = _write_pos;
					++_write_pos;
				}
			} else {
				_data[_write_pos] = c;
				++_write_pos;
			}
			break;
		default:
			// error status
			return -12;
		}
		++read_len;
	}
	return read_len;
}
void http_head::reset() {
	_raw_url.clear();
	_parse_pos = _write_pos = _parse_status = 0;
	_method = _url = _protocol = _msg = 0;
	_code = -1;
	_query = _params = 0;
}
const _value_pair_t *http_head::find_param( const char *param, const _value_pair_t *begin ) const {
	return _find( _params, param, begin );
}
int http_head::find_param_int( const char *param, int defval ) {
	return _find_int( _params, param, defval );
}
const char * http_head::find_param_string( const char *param, const char * defval ) {
	return _find_string( _params, param, defval );
}
const _value_pair_t *http_head::find_query( const char *name, const _value_pair_t *begin ) const {
	return _find( _query, name, begin );
}
int http_head::find_query_int( const char *name, int defval ) {
	return _find_int( _query, name, defval );
}
const char * http_head::find_query_string( const char *name, const char * defval ) {
	return _find_string( _query, name, defval );
}

_value_pair_t *http_head::_alloc_value_pair() {
	if ( _write_pos + sizeof(_value_pair_t) >= _max_len && !_enlarge_buffer(_default_buffer_size/2) ) {
		// failed enlarge buffer
		return 0;
	}
#if __arm__
	// must allocate object on 4 bytes boundary
	// assume that _data always allocated on 4 bytes boundary
	_write_pos = (_write_pos+3)&~0x03u;
#endif
	_value_pair_t *obj =(_value_pair_t *)(_data+_write_pos);
	_write_pos += sizeof(_value_pair_t);
	_parse_pos = _write_pos;
	memset( obj, 0, sizeof(_value_pair_t) );
	return obj;
}
bool http_head::_enlarge_buffer( int size ) {
	char *new_base = NULL;//(char *)realloc( _data, _max_len+size );
	if ( new_base == 0 ) {
		return false;
	}
	_max_len += size;
	if ( new_base != _data ) {
		_rebase_ptr( _method, _data, new_base );
		_rebase_ptr( _url, _data, new_base );
		_rebase_ptr( _protocol, _data, new_base );
		_rebase_ptr( _query, _data, new_base );
		_rebase_ptr( _msg, _data, new_base );
		_rebase_ptr( _params, _data, new_base );
		_data = new_base;
	}
	return true;
}

