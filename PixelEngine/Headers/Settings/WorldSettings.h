#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class WorldSettings{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel) :_buffer_size(buffer_size),
			_gcfrequentlevel(gcfrequentlevel){};
		const size_t& BufferSize()const{
			return _buffer_size;
		}
		const int & GcFrequentLevel()const{
			return _gcfrequentlevel;
		}
	protected:
		size_t _buffer_size;
		int _gcfrequentlevel;
	};
}