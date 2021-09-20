#pragma once
#include "SettingsBase.h"
namespace Settings{
	class WorldSettings :public SettingsBase{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel,int cycletomove) :
			_buffer_size(buffer_size),_gcfrequentlevel(gcfrequentlevel),_cycletomove(cycletomove){};
		WorldSettings() = default;
		// Inherited via SettingsBase
		virtual std::string ToStdString() override{
			return "Buffer Size: " + std::to_string(_buffer_size) + " GCFrequentLevel: " + std::to_string(_gcfrequentlevel) + " Cycle To Move: " + std::to_string(_cycletomove);
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
		size_t _buffer_size;
		int _gcfrequentlevel;
		int _cycletomove;
	};
}