#pragma once

#include "resource.h"

//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

enum scene_names {
	TitleScene = 0,
	TownScene,
	BattleScene,
	GameOverScene,
	ShopGym = 100,
	ShopChurch,
	ShopBlacksmith,
	ShopGuild,
	House = 999
};


enum Title_menus {
	menuNew = 0,
	menuLoad,
	menuQuit
};

enum actor_direction {
	FacingDown = 0,
	FacingLeft,
	FacingRight,
	FacingUp
};

#define TARGET_FPS 60
#define CHARACTER_SIZE 50
#define CHARACTER_FRAME_MAX 4