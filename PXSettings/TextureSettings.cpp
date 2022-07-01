#include "TextureSettings.h"
#include "Utility/Serialization.h"

std::string Settings::TextureSettings::ToStdString() const {
	json jobj = *this;
	return jobj.dump();
}
