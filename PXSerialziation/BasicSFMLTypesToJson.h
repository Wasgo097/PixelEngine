#pragma once
#include "json.hpp"
#include <SFML/System.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
namespace sf {
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2f, x, y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2i, x, y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2u, x, y)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(VideoMode, height, width, bitsPerPixel)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Color, r, g, b, a)
}