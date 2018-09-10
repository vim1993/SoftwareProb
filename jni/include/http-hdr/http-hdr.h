/*
 * http_hdr.h
 *
 *  Created on: 2012-6-14
 *      Author: hy
 */

#ifndef HTTP_HDR_H_
#define HTTP_HDR_H_

struct http_head {
	static const int _default_buffer_size = 8192;
	static const unsigned int STATE_PARSE_FINISHED = 0xFFFFFFFF;
	struct _value_pair_t {
		_value_pair_t *_next;
		char *_name;
		char *_value;
	};
	enum {REQUEST,RESPONSE} _type;
	char *_method;
	char *_url;
	char *_protocol;
	char *_msg;
	unsigned int _code;
	_value_pair_t *_query;
	_value_pair_t *_params;
	std::string _raw_url;

	http_head();
	~http_head();
	// return value
	// -1 error
	// >= 0 number of bytes parsed
	int parse( const char*buf, int len );
	int parse( char c ) {
		return this->parse( &c, sizeof(c) );
	}
	void reset();
	inline bool empty() const {
		return _write_pos == 0;
	}
	inline bool finished() const {
		return _parse_status == STATE_PARSE_FINISHED;
	}
	const _value_pair_t *find_param( const char *param, const _value_pair_t *begin = 0 ) const;
	int find_param_int( const char *param, int defval = int() );
	const char * find_param_string( const char *param, const char * defval = 0 );
	const _value_pair_t *find_query( const char *name, const _value_pair_t *begin = 0 ) const;
	int find_query_int( const char *name, int defval = int() );
	const char * find_query_string( const char *name, const char * defval = 0 );
private:
	_value_pair_t *_alloc_value_pair();
	bool _enlarge_buffer( int size ) ;
	unsigned int _max_len;
	char *_data;
	unsigned int _parse_status;
	unsigned int _parse_pos;
	unsigned int _write_pos;
};

#endif /* HTTP_HDR_H_ */
