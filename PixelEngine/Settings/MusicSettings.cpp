#include "MusicSettings.h"
std::string Settings::MusicSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
