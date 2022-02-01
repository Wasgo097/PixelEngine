#include "Settings/AnimationSettings.h"
int main(){
	Settings::AnimationSettings settings;
	auto json = settings.JSerialize();
	return 0;
}