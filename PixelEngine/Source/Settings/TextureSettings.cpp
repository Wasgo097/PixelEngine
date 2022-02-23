#include "Settings\TextureSettings.h"
std::string Settings::TextureSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
