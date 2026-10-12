/*
  SIRÈNE: https://t-arg.github.io/ID-42-Sirene/

  Arduboy version 2.0.0:  https://github.com/T-arg/ID-42-Sirene

  MADE by TEAM a.r.g. : https://t-arg.github.io/

  2016 - JO3RI - JUSTIN_CYR

  2026 - MUSIC and SOUND EFFECTS - JO3RI

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 42

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "stages.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGameNextStage,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
  stateGameEnded,
  stateMenuJbox,
};


void setup() {
  arduboy.boot();
  arduboy.audio.begin();                                    // read the saved sound on/off setting (boot() does not do it)
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  musicUpdate();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

