#include "Controller/ActorController.h"
namespace Controller{
	ActorController::ActorController(std::map<Key, std::function<void()>> actions) :_actions(std::move(actions)){}
}
