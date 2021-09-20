#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class WorldSettings{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel,int cycletomove) :_buffer_size(buffer_size),
			_gcfrequentlevel(gcfrequentlevel),_cycletomove(cycletomove){};
		const size_t& BufferSize()const{
			return _buffer_size;
		}
		const int & GcFrequentLevel()const{
			return _gcfrequentlevel;
		}
		const int & CycleToMove()const{
			return _cycletomove;
		}
	protected:
		size_t _buffer_size;
		int _gcfrequentlevel;
		int _cycletomove;
	};
}