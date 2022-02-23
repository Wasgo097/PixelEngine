#include "Settings\EngineSettings.h"
std::string Settings::EngineSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
