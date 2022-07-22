#include "Actor.h"
#include <iostream>
#include "Components/ActorComponentBase.h"
#include "World/WorldBase.h"
namespace Core::Object {
	Actor::Actor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings) :
		_world(world), _actor_settings(actor_settings), _texture_settings(texture_settings), _velocity(_actor_settings.velocity), _tick(_actor_settings.tick) {
		//collision
		if (static_cast<int>(_actor_settings.collision) > 1) {
			_components.emplace_back(std::make_shared<Components::Collider>(this, actor_settings));
		}
		//texture and sprite
		if (!_texture_settings.texture_path.empty()) {
			_texture = std::make_unique<sf::Texture>();
			if (_texture->loadFromFile(_texture_settings.texture_path)) {
				_texture->setSmooth(texture_settings.smooth);
				_texture->setRepeated(texture_settings.repeatable);
				_sprite = std::make_unique<sf::Sprite>();
				_sprite->setTexture(*_texture);
				sf::Vector2f temp_origin(static_cast<float>(_texture->getSize().x), static_cast<float>(_texture->getSize().y));
				temp_origin.x /= 2.0f;
				_sprite->setOrigin(temp_origin);
				_sprite->setPosition(_actor_settings.position);
			}
			else {
				throw std::invalid_argument("Wrong path in actor constructor: " + _texture_settings.texture_path + " in " + ToString());
			}

		}
	}
	Actor::~Actor() {
		for (const auto& component : _components)
			component->EndComponent();
	}
	bool Actor::TickFlag()const {
		return _tick;
	}
	void Actor::SetTickFlag(bool flag) {
		_tick = flag;
	}
	void Actor::Tick(float delta_time) {
		if (_actor_settings.type == ActorsEnums::ActorType::Dynamic && _velocity != sf::Vector2f()) {
			if (_sprite)
				_sprite->move(_velocity);
			if (auto collider = GetCollider(); collider)
				collider->Move(_velocity);
			if (!_pushed)
				_velocity = sf::Vector2f(0, 0);
		}
		for (const auto& component : _components)
			if (component->TickFlag())
				component->Tick(delta_time);
	}
	bool Actor::CanCollide() const {
		return static_cast<int>(_actor_settings.collision) > 0;
	}
	sf::Vector2f Actor::GetVelocity() const {
		return sf::Vector2f();
	}
	std::shared_ptr<Components::Collider> Actor::GetCollider()const {
		if (auto collider = GetTComponent<Components::Collider>(); collider)
			return collider;
		return {};
	}
	void Actor::Draw(sf::RenderWindow& window) {
		if (_sprite)
			window.draw(*_sprite);
		if (_actor_settings.drawable_collision_box) {
			if (auto collider = GetTComponent<Components::Collider>(); collider) {
				window.draw(collider->GetCollider());
				sf::CircleShape circle(1.0);
				circle.setPosition(collider->GetCollider().getPosition());
				circle.setFillColor(sf::Color::Black);
				window.draw(circle);
			}
		}
	}
	void Actor::Init() {
		SetTickFlag(_actor_settings.tick);
		for (const auto& component : _components)
			component->InitComponent();
	}
	std::string Actor::ToString() const { return "Default Actor ToString"; }
	void Actor::Move(const sf::Vector2f& velocity) {
		_velocity = velocity;
		_pushed = false;
	}
	void Actor::ConstPush(const sf::Vector2f& const_velocity) {
		_velocity = const_velocity;
		_pushed = true;
	}
}