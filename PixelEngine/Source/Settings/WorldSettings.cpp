#include "Settings/WorldSettings.h"
#include <sstream>
// Inherited via SettingsBase
std::string Settings::WorldSettings::ToStdString() const{
	std::stringstream stream;
	stream << "Buffer Size: " << _buffer_size << " GCFrequentLevel: " << _gcfrequentlevel << " Cycle To Move: " << _cycletomove;
	return stream.str();
}

json Settings::WorldSettings::JSerialize() const{
	try{
		json output;
		output["_buffer_size"] = _buffer_size;
		output["_gcfrequentlevel"] = _gcfrequentlevel;
		output["_cycletomove"] = _cycletomove;
		return output;
	}
	catch(...){
		return json();
	}
}

bool Settings::WorldSettings::JDeserialize(json json){
	try{
		_buffer_size = json["_buffer_size"];
		_gcfrequentlevel = json["_gcfrequentlevel"];
		_cycletomove = json["_cycletomove"];
		return true;
	}
	catch(...){
		return false;
	}
}

size_t Settings::WorldSettings::BufferSize() const{
	return _buffer_size;
}

int Settings::WorldSettings::GcFrequentLevel() const{
	return _gcfrequentlevel;
}

int Settings::WorldSettings::CycleToMove() const{
	return _cycletomove;
}
