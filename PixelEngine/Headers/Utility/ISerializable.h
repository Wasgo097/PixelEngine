#pragma once
#include <vector>
#include <string>
#include "json.hpp"
namespace Utility{
	using nlohmann::json;
	class IDiskSerializable{
	public:
		virtual void DiskSerialize(const std::string & path)const = 0;
		virtual bool DiskDeserialize(const std::string& path) = 0;
	};
	class IStringSerializable{
	public:
		virtual std::string StrSerialize()const = 0;
		virtual bool StrDeserialize(std::string) = 0;
	};
	class IStringsArraySerializable{
	public:
		virtual std::vector<std::string> ArrSerialize()const = 0;
		virtual bool ArrDeserialize(std::vector<std::string>) = 0;
	};
}