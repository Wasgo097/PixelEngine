#pragma once
#include "ActorComponentBase.h"
#include <SFML/Graphics/Sprite.hpp>
#include "PXUtilities/Enums/AnimationEnums.h"
#include "PXSettings/TextureSettings.h"
#include "PXSettings/AnimationSettings.h"
namespace Core::Object::Components {
	class Animation:public ActorComponentBase {
	public:
		Animation(Core::Object::Actor* parent,sf::Sprite& animated_sprite, const Settings::AnimationSettings& animation_settings);
		void SetRow(int row);
		void SetRowAndSetTexture(int row);
		virtual void Tick(float delta_time)override;
	protected:
		std::map<int, int>& _count_of_columns_in_row;
		sf::Sprite& _animated_sprite;
		Settings::AnimationSettings _animation_settings;
		sf::IntRect _frame_on_texture;
		sf::Vector2u _movable_view_on_texture;
		float _elapsed_time = .0f;
		int _row = -1;
	};
}