#include "Utility/CommonHeaders.h"
#include "Actor.h"
#include "Core/World/WorldBase.h"
namespace Core {
	Actor::Actor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings) :
		_world(world), _actorsettings(actorsettings), _texturesettings(texturesettings), _velocity(_actorsettings._velocity), _tickon(_actorsettings._tickflag) {
		//collision
		if (static_cast<int>(_actorsettings._collision) > 1) {
			_collider = sf::RectangleShape(_actorsettings._collidersize);
			sf::Vector2f temporigin = _collider->getSize();
			temporigin.x /= 2.0f;
			//bottom center
			_collider->setOrigin(temporigin);
			_collider->setPosition(_actorsettings._position);
		}
		//texture and sprite
		if (!_texturesettings._texturepath.empty()) {
			_texture = std::make_unique<sf::Texture>();
			if (_texture->loadFromFile(_texturesettings._texturepath)) {
				_texture->setSmooth(texturesettings._smooth);
				_texture->setRepeated(texturesettings._repeatable);
				_sprite = std::make_unique<sf::Sprite>();
				_sprite->setTexture(*_texture);
				sf::Vector2f temporigin(_texture->getSize().x, _texture->getSize().y);
				temporigin.x /= 2.0f;
				_sprite->setOrigin(temporigin);
				_sprite->setPosition(_actorsettings._position);
			}
			else {
				throw std::invalid_argument("Wrong path in actor constructor: " + _texturesettings._texturepath + " in " + ToString() + " " + _actorsettings.ToStdString());
			}

		}
	}
	bool& Actor::TickFlag() {
		return _tickon;
	}
	void Actor::Tick(float deltatime) {
		if (_actorsettings._type == ActorsEnums::ActorType::Dynamic) {
			auto movevec = _velocity ;
			if (_sprite)
				_sprite->move(movevec);
			if (_collider)
				_collider->move(movevec);
			if (!_pushed)
				_velocity = sf::Vector2f(0, 0);
		}
	}
	bool Actor::CanCollide() const {
		return static_cast<int>(_actorsettings._collision) > 0;
	}
	const sf::RectangleShape& Actor::GetCollider() const {
		return *_collider;
	}
	void Actor::SetWorld(WorldBase* worldptr) {
		_world = worldptr;
	}
	void Actor::Draw(sf::RenderWindow& window) {
		if (_sprite)
			window.draw(*_sprite);
	}
	std::string Actor::ToString() const { return "Default Actor ToString"; }
	void Actor::Move(const sf::Vector2f& velocity) {
		_velocity = velocity;
		_pushed = false;
	}
	void Actor::ConstPush(const sf::Vector2f& constvelocity) {
		_velocity = constvelocity;
		_pushed = true;
	}
}