#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
byte hairFrame = 0;
byte eyesFrame = 0;
byte eyesSequence[] = {0, 1, 2, 3, 3, 3, 1};

void drawTitleScreen()
{
  byte eyesFrame2;
  if (arduboy.everyXFrames(10)) hairFrame++;
  if (arduboy.everyXFrames(2)) eyesFrame++;
  if (eyesFrame > 60)eyesFrame = 0;
  eyesFrame2 = eyesFrame;
  if (eyesFrame2 > 6) eyesFrame2 = 0;
  if (hairFrame > 3) hairFrame = 0;
  sprites.drawSelfMasked(36, 1, mermaidTitle, 0);
  sprites.drawSelfMasked(59, 21, mermaidTrident, 0);
  sprites.drawSelfMasked(62, 48, mermaidFin, 0);
  sprites.drawSelfMasked(4, 46, mermaidBody, 0);
  sprites.drawSelfMasked(3, 14, mermaidHair, hairFrame);
  sprites.drawSelfMasked(10, 24, mermaidBlink, eyesSequence[eyesFrame2]);
}

void stateMenuIntro()
{
  globalCounter++;
  if (globalCounter < 90) sprites.drawSelfMasked(36, 28, arduboyWord, 0);   // ARDUBOY for 1.5 seconds, then the logo
  else sprites.drawSelfMasked(49, 20, T_arg, 0);
  if (globalCounter > 240)
  {
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  drawTitleScreen();
  for (byte i = 0; i < 4; i++)
  {
    sprites.drawSelfMasked(108, 32 +(i*8), menuText, i < 3 ? i : 6);   // PLAY INFO CONF JBOX
  }
  sprites.drawSelfMasked(92, 32 + 8*(menuSelection-2), trident, 0);
  if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < 5)) { menuSelection++; sfx(sfxMove, 1); }
  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 2)) { menuSelection--; sfx(sfxMove, 1); }
  if (arduboy.justPressed(B_BUTTON)) { gameState = menuSelection < 5 ? menuSelection : STATE_MENU_JBOX; sfx(sfxSelect, 1); }
}

void stateMenuInfo()
{
  sprites.drawSelfMasked(33, 10, mermaidTitle, 0);
  sprites.drawSelfMasked(36, 31, madeBy, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  for (byte i = 0; i < 3; i++)
  {
    sprites.drawSelfMasked(108, 40 +(i*8), menuText, i+3);
  }
  sprites.drawSelfMasked(92, 48 + 8*arduboy.audio.enabled(), trident, 0);
  if (arduboy.justPressed(DOWN_BUTTON)) arduboy.audio.on();
  if (arduboy.justPressed(UP_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}

// JUKEBOX: UP/DOWN = MUSIC/SNDFX, LEFT = next number, RIGHT = previous number, B = play, A = stop (A again = back to the menu)
byte jbRow = 0;
byte jbNr[2];                                  // MUSIC 0..12, SNDFX 0..21

// little arrows left and right of the number (2 x 3 pixels, frame 0 points left, frame 1 right)
const unsigned char PROGMEM jbArrow[] = { 2, 8, 0x02, 0x07, 0x07, 0x02 };

void stateMenuJbox()
{
  sprites.drawSelfMasked(33, 6, mermaidTitle, 0);
  for (byte i = 0; i < 2; i++)
  {
    sprites.drawSelfMasked(40, 32 + 12*i, jboxText, i);
    sprites.drawSelfMasked(71, 35 + 12*i, jbArrow, 0);
    sprites.drawSelfMasked(88, 35 + 12*i, jbArrow, 1);
    if (jbRow != i || (arduboy.frameCount & 16))              // the selected number blinks
    {
      sprites.drawSelfMasked(74, 32 + 12*i, numbersBig, (jbNr[i] + 1) / 10);
      sprites.drawSelfMasked(81, 32 + 12*i, numbersBig, (jbNr[i] + 1) % 10);
    }
  }
  byte n = jbRow ? JBOX_SFX : JBOX_MUSIC;
  if (arduboy.justPressed(UP_BUTTON)) jbRow = 0;
  if (arduboy.justPressed(DOWN_BUTTON)) jbRow = 1;
  if (arduboy.justPressed(RIGHT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + 1) % n;
  if (arduboy.justPressed(LEFT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + n - 1) % n;
  if (arduboy.justPressed(B_BUTTON) && arduboy.audio.enabled())
  {
    if (jbRow) sfx((const uint8_t *)pgm_read_word(&sfxList[jbNr[1]]), jbNr[1] > 17 ? 3 : 1);
    else musicPlay(jbNr[0]);
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    if (musicId == MUSIC_OFF) gameState = STATE_MENU_MAIN;    // nothing playing: leave, the title tune restarts
    else musicPlay(MUSIC_OFF);
  }
}

#endif
