#pragma once

#include "resource.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 


typedef struct pc_status {
	int atk;
	int def;
	int hp;
	int hp_max;
} STATUS_PC;

typedef struct mob_status {
	int level;
	int atk;
	int def;
	int hp;
	int hp_max;
}STATUS_MOB;

typedef struct damagefont {
	POINT StartPos;
	POINT CurPos;
	POINT EndPos;
}DAMAGE_FONT;


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
	menuQuit,
	menuAttack,
	menuDefense
};

enum actor_direction {
	FacingDown = 0,
	FacingLeft,
	FacingRight,
	FacingUp
};

enum actor_state {
	Idle = 0,
	Moving,
	Event,

};

enum Battle_State {
	Ready = 0,
	Attacking = 1,
	Win = 2,
	Dead = 3,
	Hit = 4,
	AttackStart = 100,
	PrepareAttack,
	AttackEnd = 200,	
	FinishAttack,
	WaitForMessage = 300
	
};

#define TARGET_FPS 60
#define CHARACTER_SIZE 48
#define CHARACTER_SIZE_BATTLE 64
#define CHARACTER_FRAME_MAX 4
#define MAP_ROW 14
#define MAP_COL 17

#define SCREEN_WIDTH 816
#define SCREEN_HEIGHT 624
#define MAPCHIP_SIZE 48

#define FX_WPN_WIDTH 96
#define FX_WPN_HEIGHT 64
#define FX_WPN_MOD_LEFT 32
#define FX_WPN_MOD_UP 10 
#define FX_VFX_SIZE 128
#define BATTLE_MENU_SIZE 64

#define PORTRAIT_SIZE 144

#define UI_FONT_SIZE 32
#define UI_HPBAR_WIDTH_BIG 144
#define UI_HPBAR_HEIGHT_BIG 10

#define UI_HPBAR_WIDTH_SMALL 64
#define UI_HPBAR_HEIGHT_SMALL 6
