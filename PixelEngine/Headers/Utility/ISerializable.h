#pragma once
#include "CommonHeaders.h"
namespace Utility{
	class ISerializable{
	public:
		virtual void Serialize(const std::string & path) = 0;
		virtual void Deserialize(const std::string& path) = 0;
		virtual std::vector<std::string> StrSerialize() = 0;
		virtual void StrDeserialize(std::vector<std::string>) = 0;
	};
}