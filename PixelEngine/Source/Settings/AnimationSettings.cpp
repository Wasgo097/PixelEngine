#include "Settings\AnimationSettings.h"
std::string Settings::AnimationSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
