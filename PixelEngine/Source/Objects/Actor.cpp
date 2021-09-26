#include "Objects/Actor.h"
#include "Core/World.h"
namespace Core{
	Actor::Actor(World * world, const Settings::ActorSettings & settings) :
		_world(world), _settings(settings), _velocity(_settings.GetVelocity()){
		//collision
		if(static_cast<int>(_settings.GetCollision()) > 1){
			_collider = sf::RectangleShape(_settings.GetColliderSize());
			sf::Vector2f temporigin = _collider->getSize();
			temporigin.x /= 2.0f;
			//bottom center
			_collider->setOrigin(temporigin);
			_collider->setPosition(_settings.GetPosition());
		}
		//texture and sprite
		const Settings::TextureSettings& texturesettings = _settings.GetTextureSettings();
		if(texturesettings.TexturePath()){
			const std::string&  texturepath = *texturesettings.TexturePath();
			if(!texturepath.empty()){
				_texture = std::make_unique<sf::Texture>();
				if(_texture->loadFromFile(texturepath)){
					_texture->setSmooth(texturesettings.Smooth());
					_texture->setRepeated(texturesettings.Repeatable());
					_sprite = std::make_unique<sf::Sprite>();
					_sprite->setTexture(*_texture);
					sf::Vector2f temporigin(_texture->getSize().x, _texture->getSize().y);
					temporigin.x /= 2.0f;
					_sprite->setOrigin(temporigin);
					_sprite->setPosition(_settings.GetPosition());
				}
				else
					throw std::invalid_argument("Wrong path in actor constructor: " + texturepath);
			}
		}
	}
	Actor::~Actor() = default;
	bool & Actor::TickFlag(){
		return _tickon;
	}
	void Actor::Draw(sf::RenderWindow & window){
		if(_sprite)
			window.draw(*_sprite);
	}
	void Actor::Tick(float deltatime){
		if(_settings.GetActorType() == Settings::ActorType::Dynamic){
			auto movevec = _velocity * deltatime;
			_sprite->move(movevec);
			_collider->move(movevec);
			_velocity = sf::Vector2f(0, 0);
		}
	}
	inline bool Actor::CanCollide() const{
		return static_cast<int>(_settings.GetCollision()) > 0;
	}
	inline const sf::RectangleShape & Actor::GetCollider() const{
		return *_collider;
	}
	inline void Actor::Move(const sf::Vector2f & velocity){
		_velocity = velocity;
	}
}