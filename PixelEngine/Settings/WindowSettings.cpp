#include "WindowSettings.h"
std::string Settings::WindowSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
