#include "ActorSettings.h"
std::string Settings::ActorSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
