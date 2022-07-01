#include "AnimationSettings.h"
#include "Utility/Serialization.h"

std::string Settings::AnimationSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
