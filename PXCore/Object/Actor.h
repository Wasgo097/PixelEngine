#pragma once
#include "Object.h"
#include "PXSettings/ActorSettings.h"
#include "PXSettings/TextureSettings.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <list>
#include <concepts>
namespace Core::World {
	class WorldBase;
}
namespace Core::Object {
	namespace Components {
		class ActorComponentBase;
	}
	class Actor :public Object {
	public:
		Actor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings);
		Actor(const Actor&) = delete;
		Actor& operator=(const Actor&) = delete;
		Actor(Actor&&) = delete;;
		Actor& operator=(Actor&&) = delete;;
		virtual ~Actor();

		bool TickFlag()const;
		void SetTickFlag(bool flag);
		bool CanCollide()const;
		std::optional<sf::RectangleShape> GetCollider();
		void SetWorld(World::WorldBase* world_ptr);

		virtual void Tick(float delta_time);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void ConstPush(const sf::Vector2f& const_velocity);
		virtual void Draw(sf::RenderWindow& window);
		virtual void Init()override;

		virtual std::string ToString()const override;
	private:
		bool _tick = false;
	protected:
		template<typename T>
			requires std::derived_from<T, Core::Object::Components::ActorComponentBase>
		std::shared_ptr<T> GetTComponent() {
			for (auto& component : _components) {
				if (auto casted_component = std::dynamic_pointer_cast<T>(component); casted_component)
					return casted_component;
			}
			return {};
		}
		World::WorldBase* _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::optional<sf::RectangleShape> _collider;
		std::list<std::shared_ptr<Components::ActorComponentBase>> _components;
		Settings::ActorSettings _actor_settings;
		Settings::TextureSettings _texture_settings;
		sf::Vector2f _velocity;
		bool _pushed = false;
	};
}