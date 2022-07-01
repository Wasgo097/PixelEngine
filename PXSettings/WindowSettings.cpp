#include "WindowSettings.h"
#include "Utility/Serialization.h"

std::string Settings::WindowSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
