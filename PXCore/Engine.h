#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>
#include "PXArgumentParser/ArgumentParser.h"
#include "PXSound/MusicManager.h"
#include "PXSound/SoundsManager.h"
#include "PXSettings/EngineSettings.h"
#include "PXSettings/WindowSettings.h"
#include "PXSettings/WorldSettings.h"
#include "PXSettings/MusicSettings.h"
#include "World/WorldBase.h"
#include "Controller/InputManager.h"
namespace Core {
	class Engine {
	public:
		Engine(std::optional<std::reference_wrapper<const ArgumentParser>> parser = {});
		virtual ~Engine();
		void PushWorldToQueue(std::unique_ptr<World::WorldBase>&& new_world);
		void PushNewMusicToPlay(std::unique_ptr<sf::Music>&& new_music)const;
		bool PushNewSoundEffect(const std::shared_ptr<Sound::SoundEffect>& new_sound_effect);
		int Run();
		void ServiceInput();
		sf::RenderWindow* GetWindow();
		std::optional<std::reference_wrapper<const ArgumentParser>> GetParser()const;
		void SetViewCenter(const sf::Vector2f& position);
	private:
		void Close();
		void Render();
		void Update();
	protected:
		virtual void InitEngine();
		std::unique_ptr<World::WorldBase> _current_world;
		std::queue<std::unique_ptr<World::WorldBase>> _worlds;
		std::unique_ptr<sf::RenderWindow> _main_window;
		std::unique_ptr<Sound::MusicManager> _music_manager;
		std::unique_ptr<Sound::SoundsManager> _sound_effect_manager;
		Controller::InputManager _input_manager;
		sf::Clock _clock;
		sf::View _view;
		std::optional<std::reference_wrapper<const ArgumentParser>> _parser;
		Settings::EngineSettings _engine_settings;
		Settings::WindowSettings _window_settings;
		Settings::MusicSettings _music_settings;
	};
}
