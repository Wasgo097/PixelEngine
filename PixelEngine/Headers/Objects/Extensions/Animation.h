#pragma once
#include "CommonHeaders.h"
#include "Settings/TextureSettings.h"
namespace Core{
	namespace Animation{
		class Animation{
		public:
			Animation(sf::Texture & animatedtexture, sf::Sprite & animatedsprite, const Settings::AnimationTextureSettings & animationsettings):_animatedtexture(animatedtexture),_animatedsprite(animatedsprite),_settings(animationsettings){}
			Animation() = default;
		protected:
			sf::Texture & _animatedtexture;
			sf::Sprite & _animatedsprite;
			Settings::AnimationTextureSettings _settings;
		};
	}
}