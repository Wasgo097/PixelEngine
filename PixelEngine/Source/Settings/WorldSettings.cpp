#include "Settings/WorldSettings.h"
#include <sstream>
// Inherited via SettingsBase
std::string Settings::WorldSettings::ToStdString() const{
	std::stringstream stream;
	stream << "Buffer Size: " << _buffer_size << " GCFrequentLevel: " << _gcfrequentlevel << " Cycle To Move: " << _cycletomove;
	return stream.str();
}

json Settings::WorldSettings::JSerialize() const{
	return json();
}

bool Settings::WorldSettings::JDeserialize(json json){
	return false;
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
