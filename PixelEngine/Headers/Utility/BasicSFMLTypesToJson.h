#pragma once
#include "json.hpp"
#include <sfml/System.hpp>
#include <SFML/Window/VideoMode.hpp>
namespace sf {
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2f, x,y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2i, x,y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2u, x,y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(VideoMode, height,width, bitsPerPixel)
}