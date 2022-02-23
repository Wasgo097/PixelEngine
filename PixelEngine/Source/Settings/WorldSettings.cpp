#include "Settings\WorldSettings.h"
std::string Settings::WorldSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
