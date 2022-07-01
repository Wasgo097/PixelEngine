#include "WorldSettings.h"
#include "Utility/Serialization.h"

std::string Settings::WorldSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
