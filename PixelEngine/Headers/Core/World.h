#pragma once
#include "CommonHeaders.h"
#include "Objects/Actor.h"
namespace Core{
	class World final {
	private:
		struct Impl;
		std::unique_ptr<Impl> _i;
	public:
		World(){

		}
		World(const World&) = delete;
		World(World&&) = delete;
		void operator=(const World&) = delete;
		void operator=(World&&) = delete;

	};
}
