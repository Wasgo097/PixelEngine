#pragma once
#include "CommonHeaders.h"
namespace Utility{
	class ISerializable{
	public:
		virtual void Serialize(const std::string & path) = 0;
		virtual void Deserialize(const std::string& path) = 0;
	};
}