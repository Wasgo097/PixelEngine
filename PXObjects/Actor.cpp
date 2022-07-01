#include "Utility/CommonHeaders.h"
#include "Actor.h"
#include "Core/World/WorldBase.h"
namespace Core {
	Actor::Actor(WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings) :
		_world(world), _actor_settings(actor_settings), _texture_settings(texture_settings), _velocity(_actor_settings.velocity), _tick(_actor_settings.tick) {
		//collision
		if (static_cast<int>(_actor_settings.collision) > 1) {
			_collider = sf::RectangleShape(_actor_settings.collider_size);
			sf::Vector2f temp_origin = _collider->getSize();
			temp_origin.x /= 2.0f;
			//bottom center
			_collider->setOrigin(temp_origin);
			_collider->setPosition(_actor_settings.position);
		}
		//texture and sprite
		if (!_texture_settings.texture_path.empty()) {
			_texture = std::make_unique<sf::Texture>();
			if (_texture->loadFromFile(_texture_settings.texture_path)) {
				_texture->setSmooth(texture_settings.smooth);
				_texture->setRepeated(texture_settings.repeatable);
				_sprite = std::make_unique<sf::Sprite>();
				_sprite->setTexture(*_texture);
				sf::Vector2f temp_origin(_texture->getSize().x, _texture->getSize().y);
				temp_origin.x /= 2.0f;
				_sprite->setOrigin(temp_origin);
				_sprite->setPosition(_actor_settings.position);
			}
			else {
				throw std::invalid_argument("Wrong path in actor constructor: " + _texture_settings.texture_path + " in " + ToString() + " " + _actor_settings.ToStdString());
			}

		}
	}
	bool Actor::TickFlag()const {
		return _tick;
	}
	void Actor::SetTickFlag(bool flag)
	{
		_tick = flag;
	}
	void Actor::Tick(float delta_time) {
		if (_actor_settings.type == ActorsEnums::ActorType::Dynamic&&_velocity!=sf::Vector2f()) {
			auto move_vector = _velocity ;
			if (_sprite)
				_sprite->move(move_vector);
			if (_collider)
				_collider->move(move_vector);
			if (!_pushed)
				_velocity = sf::Vector2f(0, 0);
		}
	}
	bool Actor::CanCollide() const {
		return static_cast<int>(_actor_settings.collision) > 0;
	}
	const sf::RectangleShape& Actor::GetCollider() const {
		return *_collider;
	}
	void Actor::SetWorld(WorldBase* world_ptr) {
		_world = world_ptr;
	}
	void Actor::Draw(sf::RenderWindow& window) {
		if (_collider&&_actor_settings.drawable_collision_box)
			window.draw(*_collider);
		if (_sprite)
			window.draw(*_sprite);
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