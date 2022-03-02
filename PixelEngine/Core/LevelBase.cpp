#include "LevelBase.h"
namespace Core {

	LevelBase::LevelBase() {
		InitLevel();
	}
	LevelBase::~LevelBase() {
		EndLevel();
	}

	void LevelBase::Update(float delta){
		CheckQuit();
	}

	bool LevelBase::ToQuit() const {
		return _quit;
	}
}
