#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include "ATMconfig.h"
#include <ATMlib.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_PLAY              2
#define STATE_MENU_INFO              3
#define STATE_MENU_SOUNDFX           4

//define game states (on main menu)
#define STATE_GAME_NEXT_STAGE        5
#define STATE_GAME_PLAYING           6
#define STATE_GAME_PAUSE             7
#define STATE_GAME_OVER              8
#define STATE_GAME_ENDED             9
#define STATE_MENU_JBOX             10      // jukebox (opened from the main menu)

#define GAME_TOP                     0
#define GAME_BOTTOM                  64
#define GAME_LEFT                    0
#define GAME_RIGHT                   128

#define STAGE_TO_START_WITH          1
#define PLAYER_CAN_DIE               1

#define SCORE_SMALL_FONT             0
#define SCORE_BIG_FONT               1

#define MAX_ONSCREEN_ENEMIES         9
#define MAX_ENEMY_BULLETS            3
#define MAX_BOSS_BULLETS             6

Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;    // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
byte globalCounter = 0;
byte stage = STAGE_TO_START_WITH -1;
unsigned long scorePlayer; 
byte backgroundIsVisible;
byte gameOverAndStageFase;
byte currentWave;
byte previousWave;
int leftX;
byte rightX;
byte powerUpSelectorY = 0;

#include "music.h"

#endif
