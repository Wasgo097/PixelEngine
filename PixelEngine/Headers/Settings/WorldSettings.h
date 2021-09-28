#pragma once
#include "SettingsBase.h"
namespace Settings{
	class WorldSettings :public SettingsBase{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel,int cycletomove) :
			_buffer_size(buffer_size),_gcfrequentlevel(gcfrequentlevel),_cycletomove(cycletomove){};
		WorldSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override{
			std::stringstream stream;
			stream<< "Buffer Size: " <<_buffer_size<< " GCFrequentLevel: " <<_gcfrequentlevel<< " Cycle To Move: " <<_cycletomove;
			return stream.str();
		}
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
		size_t _buffer_size=200;
		int _gcfrequentlevel=5;
		int _cycletomove=10;
	};
}