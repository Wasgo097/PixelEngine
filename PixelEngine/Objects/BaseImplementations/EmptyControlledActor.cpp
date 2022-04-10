#include "EmptyControlledActor.h"

Core::EmptyControlledActor::EmptyControlledActor(WorldBase* world, const Settings::ActorSettings& actorsettings, const Settings::TextureSettings& texturesettings, const Settings::AnimationSettings& animationsettings, Controller::ControllerBase* controller):ControlledActor(world,actorsettings,texturesettings,animationsettings,controller)
{
}
