#include "ActorSettings.h"
#include "Utility/Serialization.h"
std::string Settings::ActorSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
