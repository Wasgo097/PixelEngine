#pragma once
namespace Settings {
	struct WorldSettings{
	public:
		WorldSettings(size_t buffer_size, unsigned gc_frequent_level) :
			buffer_size{ buffer_size }, gc_delay{ gc_frequent_level }{};
		WorldSettings() = default;

		bool operator ==(const WorldSettings& obj)const {
			return buffer_size == obj.buffer_size && gc_delay == obj.gc_delay;
		}

		size_t buffer_size = 200;
		unsigned gc_delay = 5;
	};
}