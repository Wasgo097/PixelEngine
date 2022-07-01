#include "EngineSettings.h"
#include "Utility/Serialization.h"

std::string Settings::EngineSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
