#pragma once
#include "CommonHeaders.h"
namespace Utility{
	class ISerializableFromDisk{
	public:
		virtual void SerializeFromDisk(const std::string & path) = 0;
		virtual void DeserializeFromDisk(const std::string& path) = 0;
	};
	class IStringSerializable{
	public:
		virtual std::string Serialize() = 0;
		virtual void Deserialize(std::string) = 0;
	};
	class IStringsArraySerializable{
		virtual std::vector<std::string> ArrSerialize() = 0;
		virtual void ArrDeserialize(std::vector<std::string>) = 0;
	};
}