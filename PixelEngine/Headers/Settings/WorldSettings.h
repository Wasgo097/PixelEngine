#pragma once
#include "SettingsBase.h"
#include "Utility/ISerializable.h"
using nlohmann::json;
namespace Settings{
	class WorldSettings :public SettingsBase, Utility::IJsonSerializable{
	public:
		WorldSettings(size_t buffer_size, int gcfrequentlevel,int cycletomove) :
			_buffer_size(buffer_size),_gcfrequentlevel(gcfrequentlevel),_cycletomove(cycletomove){};
		WorldSettings() = default;
	public:
		// Inherited via SettingsBase
		virtual std::string ToStdString()const override;
		// Inherited via IJsonSerializable
		virtual json JSerialize() const override;
		virtual bool JDeserialize(json json) override;
	public:
		size_t BufferSize()const;
		int GcFrequentLevel()const;
		int CycleToMove()const;
	protected:
		size_t _buffer_size=200;
		int _gcfrequentlevel=5;
		int _cycletomove=10;
	};
}