#pragma once
#include "smart_ptr.h"

PTR( Game );

class Game {
public:
	static GamePtr GetInstance();
	virtual ~Game();

	void Init();
	void Run();
private:
	Game();

private:
	static GamePtr _instance;
};

#define sGame Game::GetInstance()