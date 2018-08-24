#pragma once

#include "resource.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 


typedef struct pc_status {
	int atk = 0;
	int def = 0;
	int hp = 0;
	int hp_max = 0;
	int pos_x = 0;
	int pos_y = 0;
	int pos_shadow_x = 0;
	int pos_shadow_y = 0;
	int coord_x = 0;
	int coord_y = 0;
	int coord_next_x = 0;
	int coord_next_y = 0;
	int facing = 0;
	int battlestate = 0;
	int movestate = 0;
	int speed = 4;

} STATUS_PC;

typedef struct mob_status {
	int level = 1;
	int atk = 1;
	int def = 1;
	int hp = 1;
	int hp_max = 1;
	int pos_x = 96;
	int pos_y = 280;
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
	menuAttack = 100,
	menuDefense,
	menuYes = 1000,
	menuNo
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
	//battle State
	Battle_Ready = 0,
	Battle_On,
	Battle_Wait,
	Battle_End,


	// battle state - player
	Player_Attack_Move = 100,
	Player_Attacking = 101,
	Player_Win = 102,
	Player_Lose = 103,
	Player_Hit = 104, 
	Player_Return_Move = 200,	
	Player_Ready = 300,
	Player_Wait = 400,

	//battle state - monster
	Monster_Attack_Move = 1000,
	Monster_Attacking = 1001,
	Monster_Return_Move = 1100,
	Monster_Hit = 1004,
	Monster_Ready = 1200,
	Monster_Wait = 1300,	
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
