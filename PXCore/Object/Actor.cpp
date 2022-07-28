#include "Actor.h"
#include "Components/ActorComponentBase.h"
#include "World/WorldBase.h"
namespace Core::Object {
	Actor::Actor(World::WorldBase* world, const Settings::ActorSettings& actor_settings, const Settings::TextureSettings& texture_settings) :
		_world(world), _actor_settings(actor_settings), _texture_settings(texture_settings), _velocity(_actor_settings.velocity), _tick(_actor_settings.tick) {
		//collision
		if (static_cast<int>(_actor_settings.collision) > 0)
			_components.emplace_back(std::make_shared<Components::Collider>(this, actor_settings));
		//texture and sprite
		if (!_texture_settings.texture_path.empty()) {
			_texture = std::make_unique<sf::Texture>();
			if (_texture->loadFromFile(_texture_settings.texture_path)) {
				_texture->setSmooth(texture_settings.smooth);
				_texture->setRepeated(texture_settings.repeatable);
				_sprite = std::make_unique<sf::Sprite>();
				_sprite->setTexture(*_texture);
				_sprite->setScale({ texture_settings.scale,texture_settings.scale });
				sf::Vector2f temp_origin(static_cast<float>(_texture->getSize().x), static_cast<float>(_texture->getSize().y));
				temp_origin.x /= 2.0f;
				_sprite->setOrigin(temp_origin);
				_sprite->setPosition(_actor_settings.position);
			}
			else {
				throw std::invalid_argument("Wrong path in actor constructor: " + _texture_settings.texture_path + " in " + ToString());
			}
		}
		if (_velocity != sf::Vector2f())
			_pushed = true;
	}
	bool Actor::TickFlag()const {
		return _tick;
	}
	void Actor::SetTickFlag(bool flag) {
		_tick = flag;
	}
	void Actor::Tick(float delta_time) {
		if (_actor_settings.type == ActorsEnums::ActorType::Dynamic && _velocity != sf::Vector2f()) {
			ChangePosition(_velocity,delta_time);
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
	ActorsEnums::CollisionType Actor::GetCollisionType() const {
		return _actor_settings.collision;
	}
	bool Actor::Collide(std::shared_ptr<Actor> other, sf::FloatRect& out_rect) const {
		return GetColliderComponent()->Collide(*other->GetColliderComponent(), out_rect);
	}
	std::shared_ptr<Components::Collider> Actor::GetColliderComponent()const {
		if (auto collider = GetTComponent<Components::Collider>(); collider)
			return collider;
		return {};
	}
	void Actor::Draw(sf::RenderWindow& window) {
		if (_sprite)
			window.draw(*_sprite);
		if (_actor_settings.drawable_collision_box) {
			if (auto collider = GetColliderComponent(); collider) {
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
	void Actor::OnDelete() {
		for (const auto& component : _components)
			component->EndComponent();
	}
	std::string Actor::ToString() const { return "Default Actor ToString"; }
	void Actor::OnOverlap(const Actor* other, std::optional<sf::Vector2f> diference) {
		//std::cout << ToString() << " overlap with " << other->ToString() << std::endl;
	}
	void Actor::OnCollide(const Actor* other, std::optional<sf::Vector2f> diference) {
		if (diference and !_pushed and _actor_settings.type == ActorsEnums::ActorType::Dynamic)
			ChangePosition(*diference);
	}
	void Actor::ChangePosition(const sf::Vector2f& vector, std::optional<float> speed) {
		if (_sprite)
			if (speed)
				_sprite->move(vector * (*speed));
			else
				_sprite->move(vector);
		if (auto collider = GetColliderComponent(); collider)
			if (speed)
				collider->Move(vector*(*speed));
			else
				collider->Move(vector);
		_world->CheckCollisionAfterMove(this);
	}
	void Actor::Move(const sf::Vector2f& velocity) {
		_velocity = velocity;
		_pushed = false;
	}
	void Actor::ConstPush(const sf::Vector2f& const_velocity) {
		_velocity = const_velocity;
		_pushed = true;
	}
}