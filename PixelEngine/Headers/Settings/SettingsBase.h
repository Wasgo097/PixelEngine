#pragma once
#include "CommonHeaders.h"
namespace Settings{
	class SettingsBase{
	public:
		virtual std::string ToStdString() = 0;
	};
}