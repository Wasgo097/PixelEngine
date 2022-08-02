#pragma once
#include <string>
#include <optional>
#include <SFML/System/Vector2.hpp>
namespace Core::Object {
	class Actor;
	class Object {
	public:
		virtual ~Object() = default;
		virtual std::string ToString()const { return "Default Object ToString"; }
		virtual void Init() {}
		virtual void OnSpawn() {}
		virtual void OnDelete() {}
		virtual void OnOverlap(const Actor* other, std::optional<sf::Vector2f> diference) {}
		virtual void OnCollide(const Actor* other, std::optional<sf::Vector2f> diference) {}
		void Destroy() { _to_destroy = true; }
		bool ToDestroy()const { return _to_destroy; }
	protected:
		bool _initialized = false;
	private:
		bool _to_destroy = false;
	};
}