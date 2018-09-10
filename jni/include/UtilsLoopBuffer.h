#ifndef __LOOPBUFFER_T_H_2018_03_30__
#define __LOOPBUFFER_T_H_2018_03_30__

#include "UtilsMemoryPool.h"

using namespace std;

class loopbuffer_t {
	char *_data_buf;
	const size_t _buf_len;
	volatile size_t _write_pos;
	volatile size_t _read_pos;

	size_t _free_space() const {
		size_t wpos = _write_pos;
		size_t rpos = _read_pos;

		if (wpos == rpos) {
			return _buf_len - 1;
		}
		if (wpos > rpos) {
			return _buf_len - (wpos - rpos) - 1;
		}
		return rpos - wpos - 1;
	}

	size_t _data_len() const {
		size_t wpos = _write_pos;
		size_t rpos = _read_pos;

		if (wpos == rpos) {
			return 0;
		}
		if (wpos > rpos) {
			return wpos - rpos;
		}
		return wpos + _buf_len - rpos;
	}

	void _internal_push_back(const void *data, size_t len) {
		size_t wpos = _write_pos;
		size_t rpos = _read_pos;
		if (wpos >= rpos) {
			size_t free_space_part1 = _buf_len - wpos;
			if (free_space_part1 >= len) {
				memcpy(_data_buf + wpos, data, len);
				_write_pos = (wpos + len) % _buf_len;
			} else {
				memcpy(_data_buf + wpos, data, free_space_part1);
				size_t new_wpos = len - free_space_part1;
				memcpy(_data_buf, (char*)data + free_space_part1, new_wpos);
				_write_pos = new_wpos;
			}
		} else {
			memcpy(_data_buf + wpos, data, len);
			_write_pos = wpos + len;
		}
	}

	size_t _internal_pop_front(size_t drop_len, void *buf, size_t len, bool peek = false) {
		size_t data_len = _data_len();
		if (drop_len + len > data_len) {
			return data_len;
		}
		size_t wpos = _write_pos;
		size_t rpos = _read_pos;
		size_t new_rpos = (rpos + drop_len) % _buf_len;
		if (wpos > new_rpos) {
			memcpy(buf, _data_buf + new_rpos, len);
		} else {
			size_t data_len_part1 = _buf_len - new_rpos;
			if (data_len_part1 < len) {
				memcpy(buf, _data_buf + new_rpos, data_len_part1);
				memcpy((char*)buf + data_len_part1, _data_buf, len - data_len_part1);
			} else {
				memcpy(buf, _data_buf + new_rpos, len);
			}
		}
		if (!peek) {
			_read_pos = (rpos + drop_len + len) % _buf_len;
		}
		return len;
	}
public:
	static const size_t INVALID_SIZE = (size_t)-1;
	loopbuffer_t(size_t buf_size)
		: _data_buf((char*)sdk_mem_malloc(buf_size))
		, _buf_len(buf_size)
		, _write_pos(0), _read_pos(0) {}

	~loopbuffer_t() {
		char *buf = _data_buf;
		_data_buf = 0;
		if (buf) {
			sdk_mem_free(buf);
		}
	}

	bool push_back(const void *data, size_t len) {
		if (len + sizeof(len) > _free_space()) {
			return false;
		}
		_internal_push_back(&len, sizeof(len));
		_internal_push_back(data, len);
		return true;
	}

	size_t pop_front(void *buf, size_t buf_len) {
		size_t pack_len = 0;
		size_t data_len = _internal_pop_front(0, &pack_len, sizeof(pack_len), true);
		if (data_len < sizeof(pack_len)) {
			return 0;
		}

		if (buf_len < pack_len) {
			return pack_len;
		}

		data_len = _internal_pop_front(sizeof(pack_len), buf, pack_len, false);
		if (data_len == sizeof(pack_len)) {
			// only header has been wrote
			return 0;
		}

		if (data_len != pack_len) {
			return INVALID_SIZE;
		}
		return pack_len;
	}
	size_t clear() {
		_write_pos = _read_pos = 0;
	}

	size_t peek_front(void *buf, size_t buf_len) {
		size_t pack_len = 0;
		size_t data_len = _internal_pop_front(0, &pack_len, sizeof(pack_len), true);
		if (data_len < sizeof(pack_len)) {
			return 0;
		}

		if (buf_len < pack_len) {
			return pack_len;
		}

		data_len = _internal_pop_front(sizeof(pack_len), buf, pack_len, true);
		if (data_len != pack_len) {
			return -1;
		}
		return pack_len;
	}

	template<typename _Type, int _BufLen>
	bool push_back_ex(_Type(*buf)[_BufLen]) {
		return push_back(*buf, sizeof(_Type)*_BufLen);
	}

	template<typename _Type, int _BufLen>
	size_t pop_front_ex(_Type(*buf)[_BufLen]) {
		return pop_front(*buf, sizeof(_Type)*_BufLen);
	}
};


#endif // __LOOPBUFFER_T_H_2018_03_30__