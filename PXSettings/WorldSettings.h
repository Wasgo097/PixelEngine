#pragma once
namespace Settings {
	struct WorldSettings {
	public:
		WorldSettings(size_t buffer_size, unsigned gc_frequent_level) :
			buffer_size{ buffer_size }, gc_delay{ gc_frequent_level }{};
		WorldSettings() = default;

		bool operator ==(const WorldSettings& obj)const {
			return buffer_size == obj.buffer_size and gc_delay == obj.gc_delay and deadzone_x == obj.deadzone_x and deadzone_y == obj.deadzone_y;
		}

		size_t buffer_size = 200;
		unsigned gc_delay = 5;
		float deadzone_x = 2000;
		float deadzone_y = 2000;
	};
}