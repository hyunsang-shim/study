#pragma once

#include "resource.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 



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
	Church = 100, 
	Blacksmith = 200, 
	Gym = 300,	
	Guild = 400,
	Myhouse = 500,
	Exit = 600
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
	Player_WaitAttackMessage = 500,

	//battle state - monster
	Monster_Attack_Move = 1000,
	Monster_Attacking = 1001,
	Monster_Dying = 1002,
	Monster_Return_Move = 1100,
	Monster_Hit = 1004,
	Monster_Ready = 1200,
	Monster_Wait = 1300,	
	Monster_WaitAttackMessage = 1400,
	Monster_Dead = 1999
};

enum BattleStep {
	NotInBattle = 0,
	ShowBattleMenu,
	PC_Move,
	PC_Action,
	PC_Action_Result,
	Check_Mob_Die,
	Kill_Mob,
	Loot,
	Return_To_Town,
	PC_Return,
	MOB_Move,	// 10
	MOB_Action,
	MOB_Action_Result,
	Check_PC_Die,
	Kill_PC,
	Goto_Gameover,
	MOB_Return

};

typedef struct pc_status {
	TCHAR NAME[32] = _T("무명 검투사");
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
	int battlestate = Player_Ready;
	int movestate = Idle;
	int speed = 4;
	int Exp = 0;
	int Gold = 0;
	int Fame = 0;

} STATUS_PC;

typedef struct mob_status {
	TCHAR NAME[32] = _T("거대 시궁쥐");
	int level = 1;
	int atk = 1;
	int def = 1;
	int hp = 1;
	int hp_max = 1;
	int pos_x = 96;
	int pos_y = 280;
	int coord_x = 0;
	int coord_y = 0;
	int coord_next_x = 0;
	int coord_next_y = 0;
	int battlestate = Monster_Ready;
	int movestate = Idle;

}STATUS_MOB;

typedef struct battle_message {
	TCHAR AttackMessage[128];
	TCHAR AttackResultMessage[128];
	TCHAR BattleResultMessage[128];
	int damage;
}BATTLE_MSG;

typedef struct loot_message {
	TCHAR Exp[128];
	TCHAR Gold[128];
	TCHAR Fame[128];
	int damage;
}LOOT_MSG;
typedef struct result_message {
	TCHAR Result[128];
	TCHAR Move[128];
}RESULT_MSG;



typedef struct history {
	int monster_killed;
	int exp_earned;
	int exp_spent;
	int fame_earned;
	int church_visited;
	int gym_visited;
	int guild_visited;
}HISTORY;

#define TARGET_FPS 30
#define CHARACTER_SIZE 48
#define CHARACTER_SIZE_BATTLE 64
#define CHARACTER_FRAME_MAX 4
#define MAP_ROW 14
#define MAP_COL 17

#define SCREEN_WIDTH 816
#define SCREEN_HEIGHT 624
#define MAPCHIP_SIZE 48

#define WPN_WIDTH 96
#define WPN_HEIGHT 64
#define WPN_MOD_LEFT 32
#define WPN_MOD_UP 10 
#define WPN_VFX_SIZE 128
#define BATTLE_MENU_SIZE 64

#define PORTRAIT_SIZE 144

#define UI_FONT_SIZE 32
#define UI_MSG_MARKER_SIZE 16

#define BATTLE_POS_PC_DEFAULT_X 13
#define BATTLE_POS_PC_DEFAULT_Y 7
#define BATTLE_POS_MOB_DEFAULT_X 3
#define BATTLE_POS_MOB_DEFAULT_Y 5

#define BATTLE_POS_PC_ATTACK_X 12
#define BATTLE_POS_PC_ATTACK_Y 7
#define BATTLE_POS_MOB_ATTACK_X 4
#define BATTLE_POS_MOB_ATTACK_Y 5

#define BATTLE_POS_MSG_BOX_X 42
#define BATTLE_POS_MSG_BOX_Y 460
#define BATTLE_MSG_BOX_WIDTH 723
#define BATTLE_MSG_BOX_HEIGHT 147
#define BATTLE_MSG_BOX_FRAMES 5

#define FONT_SIZE_NORMAL 26
#define FONT_SIZE_BIG 32
#define FONT_SIZE_SMALL 18
