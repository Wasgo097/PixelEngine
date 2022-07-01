#pragma once
#include "SettingsBase.h"
namespace Settings {
	struct WorldSettings :public SettingsBase {
	public:
		WorldSettings(size_t buffer_size, int gc_frequent_level, int cycle_to_move) :
			buffer_size{ buffer_size }, gc_frequent_level{ gc_frequent_level }, cycle_to_move{ cycle_to_move }{};
		WorldSettings() = default;
		virtual std::string ToStdString()const override;
		size_t buffer_size = 200;
		int gc_frequent_level = 5;
		int cycle_to_move = 10;

		bool operator ==(const WorldSettings& obj)const {
			return buffer_size == obj.buffer_size && gc_frequent_level == obj.gc_frequent_level && cycle_to_move == obj.cycle_to_move;
		}
	};
}