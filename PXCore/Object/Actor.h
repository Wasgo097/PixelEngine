#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <concepts>
#include "PXSettings/ActorSettings.h"
#include "PXSettings/TextureSettings.h"
#include "Components/Collider.h"
namespace Core::World {
	class WorldBase;
}
namespace Core::Object {
	namespace Components {
		class ActorComponentBase;
		class Collider;
	}
	class Actor :public Object {
	public:
		Actor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings);
		Actor(const Actor&) = delete;
		Actor& operator=(const Actor&) = delete;
		Actor(Actor&&) = delete;;
		Actor& operator=(Actor&&) = delete;;
		virtual ~Actor()=default;

		bool TickFlag()const;
		void SetTickFlag(bool flag);
		bool CanCollide()const;
		std::shared_ptr<Components::Collider> GetColliderComponent()const;
		sf::Vector2f GetVelocity()const;
		std::optional<sf::Vector2f> GetPosition()const;
		ActorsEnums::CollisionType GetCollisionType()const;
		bool Collide(std::shared_ptr<Actor> other, sf::FloatRect& out_rect)const;

		virtual void Tick(float delta_time);
		virtual void Move(const sf::Vector2f& velocity);
		virtual void ConstPush(const sf::Vector2f& const_velocity);
		virtual void Draw(sf::RenderWindow& window);

		virtual void Init()override;
		virtual void OnDelete()override;
		virtual std::string ToString()const override;
		virtual void OnOverlap(const Actor* other, std::optional<sf::Vector2f> diference)override;
		virtual void OnCollide(const Actor* other, std::optional<sf::Vector2f> diference)override;
	protected:
		template<typename T>
			requires std::derived_from<T, Core::Object::Components::ActorComponentBase>
		std::shared_ptr<T> GetTComponent()const {
			for (const auto& component : _components) {
				if (auto casted_component = std::dynamic_pointer_cast<T>(component); casted_component)
					return casted_component;
			}
			return {};
		}
		virtual void CreateActorsComponents();
		void InitActorsComponents();
		void ChangePosition(const sf::Vector2f& vector,std::optional<float> speed=std::nullopt);
		World::WorldBase* _world;
		std::unique_ptr<sf::Texture> _texture;
		std::unique_ptr<sf::Sprite> _sprite;
		std::list<std::shared_ptr<Components::ActorComponentBase>> _components;
		Settings::ActorSettings _actor_settings;
		Settings::TextureSettings _texture_settings;
		sf::Vector2f _velocity;
		bool _pushed = false;
	private:
		bool _tick = false;
	};
}