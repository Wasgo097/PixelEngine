#pragma once
#include "SettingsBase.h"
namespace Settings{
	struct WorldSettings :public SettingsBase{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel,int cycletomove) :
			_buffersize(buffer_size),_gcfrequentlevel(gcfrequentlevel),_cycletomove(cycletomove){};
		WorldSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
	public:
		size_t _buffersize=200;
		int _gcfrequentlevel=5;
		int _cycletomove=10;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WorldSettings, _buffersize, _gcfrequentlevel, _cycletomove)
}