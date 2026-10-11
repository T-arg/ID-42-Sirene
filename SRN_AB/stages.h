#ifndef STAGES_H
#define STAGES_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define TOTAL_AMOUNT_OF_STAGES  9
#define TOTAL_AMOUNT_OF_WAVES   25

boolean checkStartWave()
{
  if (currentWave != previousWave)
  {
    previousWave = currentWave;
    return true;
  }
  return false;
}

void checkEndWave()
{
  byte test = 0;
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    test += bitRead(enemy[i].characteristics, 7);
  }
  if (test < 1) currentWave++;
}

void wait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    if (gameState == STATE_GAME_PLAYING) currentWave++;
    else gameOverAndStageFase++;
    globalCounter = 0;
  }
}

// ENEMY WAVES AS DATA /////////////////////////////////////////////////////////////////////
// A wave is a list of groups of enemies (the groups use the enemy slots 0, 1, 2 ... one after the other):
//   GROUP(enemy type, movement, shoots (0/1), how many, x, y, spacing x, spacing y, speed)
//   x, y: position of the first enemy of the group. x and spacing x must be even, y is 0 to 256
//   enemy n of the group starts at x + n * spacing x, y + n * spacing y (a bigger spacing x = comes later)
// To make a new wave: add an array here, add it to enemyWaves[] and use its number (1 = first) in stages[].
#define PATTERN_SWIM_RIGHT_LEFT   0   // straight to the left
#define PATTERN_SWIM_TO_MIDDLE    1   // to the left, from x < 72 on it moves to the middle of the screen
#define PATTERN_SWIM_SINE         2   // to the left, in a wave
#define PATTERN_DOWN_UP           3   // only up, the jellyfish pulse (speed = up speed)
#define PATTERN_DOWN_UP_AND_LEFT  4   // up (jellyfish pulse) and to the left (speed = left speed)

#define GROUP(type, pattern, shoots, count, x, y, spacingX, spacingY, speed) \
  (((pattern) << 4) | (type)), ((count) | ((shoots) << 4) | ((((y) >> 8) & 1) << 5)), ((x) / 2), ((y) & 255), ((spacingX) / 2), ((uint8_t)(spacingY)), (speed)

const uint8_t PROGMEM enemyWave01[] = { 3,
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 12, 192, 0, 3),
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 2, 256, 32, 192, 0, 3),
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 4, 192, 48, 192, 0, 3) };
const uint8_t PROGMEM enemyWave02[] = { 2,
    GROUP(ENEMY_FISHY, PATTERN_SWIM_TO_MIDDLE, 0, 4, 128, 12, 96, 0, 3),
    GROUP(ENEMY_FISHY, PATTERN_SWIM_TO_MIDDLE, 0, 4, 176, 52, 96, 0, 3) };
const uint8_t PROGMEM enemyWave03[] = { 1,
    GROUP(ENEMY_FISHY, PATTERN_SWIM_SINE, 0, 9, 128, 32, 36, 0, 3) };
const uint8_t PROGMEM enemyWave04[] = { 1,
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 8, 128, 12, 40, 6, 3) };
const uint8_t PROGMEM enemyWave05[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 12, 24, 0, 1),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 30, 24, 0, 1),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 48, 24, 0, 1) };
const uint8_t PROGMEM enemyWave06[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 12, 288, 0, 3),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 320, 32, 288, 0, 3),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 224, 48, 288, 0, 3) };
const uint8_t PROGMEM enemyWave07[] = { 3,
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 12, 192, 0, 2),
    GROUP(ENEMY_FISHY, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 48, 192, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 192, 26, 256, 0, 3) };
const uint8_t PROGMEM enemyWave08[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_TO_MIDDLE, 0, 3, 128, 12, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_TO_MIDDLE, 0, 3, 256, 48, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_TO_MIDDLE, 0, 3, 192, 31, 256, 0, 2) };
const uint8_t PROGMEM enemyWave09[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 2, 128, 12, 144, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 4, 128, 30, 72, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 2, 200, 48, 144, 0, 2) };
const uint8_t PROGMEM enemyWave10[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 16, 144, 0, 1),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 128, 44, 144, 0, 1),
    GROUP(ENEMY_FISH, PATTERN_SWIM_SINE, 0, 3, 200, 30, 144, 0, 1) };
const uint8_t PROGMEM enemyWave11[] = { 4,
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 2, 128, 31, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_TO_MIDDLE, 0, 2, 192, 10, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_TO_MIDDLE, 0, 2, 320, 48, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_SINE, 0, 2, 256, 31, 256, 0, 2) };
const uint8_t PROGMEM enemyWave12[] = { 3,
    GROUP(ENEMY_FISH, PATTERN_SWIM_SINE, 0, 3, 128, 30, 96, 0, 1),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 256, 12, 256, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 256, 48, 256, 0, 2) };
const uint8_t PROGMEM enemyWave13[] = { 3,
    GROUP(ENEMY_JELLYFISH, PATTERN_DOWN_UP, 0, 3, 16, 64, 40, 16, 1),
    GROUP(ENEMY_JELLYFISH, PATTERN_DOWN_UP, 0, 2, 32, 172, 48, 0, 1),
    GROUP(ENEMY_JELLYFISH, PATTERN_DOWN_UP, 0, 3, 16, 256, 40, -16, 1) };
const uint8_t PROGMEM enemyWave14[] = { 1,
    GROUP(ENEMY_JELLYFISH, PATTERN_DOWN_UP_AND_LEFT, 0, 9, 128, 64, 40, 16, 2) };
const uint8_t PROGMEM enemyWave15[] = { 2,
    GROUP(ENEMY_JELLYFISH, PATTERN_DOWN_UP_AND_LEFT, 0, 6, 128, 64, 80, 32, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_SINE, 0, 3, 288, 12, 96, 0, 2) };
const uint8_t PROGMEM enemyWave16[] = { 2,
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_SINE, 0, 4, 128, 12, 128, 0, 1),
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_SINE, 0, 4, 176, 36, 128, 0, 1) };
const uint8_t PROGMEM enemyWave17[] = { 2,
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_RIGHT_LEFT, 1, 4, 128, 10, 192, 0, 2),
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_RIGHT_LEFT, 1, 4, 192, 48, 192, 0, 2) };
const uint8_t PROGMEM enemyWave18[] = { 3,
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_RIGHT_LEFT, 1, 3, 128, 10, 192, 0, 2),
    GROUP(ENEMY_OCTOPUS, PATTERN_SWIM_RIGHT_LEFT, 1, 3, 128, 48, 192, 0, 2),
    GROUP(ENEMY_FISH, PATTERN_SWIM_RIGHT_LEFT, 0, 3, 288, 29, 192, 0, 3) };

const uint8_t* const PROGMEM enemyWaves[] = { enemyWave01, enemyWave02, enemyWave03, enemyWave04, enemyWave05, enemyWave06, enemyWave07, enemyWave08, enemyWave09, enemyWave10, enemyWave11, enemyWave12, enemyWave13, enemyWave14, enemyWave15, enemyWave16, enemyWave17, enemyWave18 };

byte nextWaveByte(const uint8_t *&wave)
{
  byte value = pgm_read_byte(wave);
  wave++;
  return value;
}

void runEnemyWave(byte waveNumber)
{
  const uint8_t *wave = (const uint8_t *)pgm_read_word(&enemyWaves[waveNumber - 1]);
  boolean startWave = checkStartWave();
  byte groups = nextWaveByte(wave);
  byte first = 0;
  while (groups > 0)
  {
    groups--;
    byte typeAndPattern = nextWaveByte(wave);
    byte countAndFlags = nextWaveByte(wave);
    int x = nextWaveByte(wave) * 2;
    int y = nextWaveByte(wave) + ((countAndFlags & 0x20) << 3);
    int spacingX = nextWaveByte(wave) * 2;
    int spacingY = (int8_t)nextWaveByte(wave);
    byte speed = nextWaveByte(wave);
    byte last = first + (countAndFlags & 15);
    if (startWave) enemySetInLine(typeAndPattern & 15, first, last, x, y, spacingX, spacingY);
    switch (typeAndPattern >> 4)
    {
      case PATTERN_SWIM_RIGHT_LEFT:
        enemySwimRightLeft(first, last, speed);
        break;
      case PATTERN_SWIM_TO_MIDDLE:
        enemySwimToMiddle(first, last, speed);
        break;
      case PATTERN_SWIM_SINE:
        enemySwimSine(first, last, speed);
        break;
      case PATTERN_DOWN_UP:
        enemySwimDownUp(first, last, speed);
        break;
      case PATTERN_DOWN_UP_AND_LEFT:
        enemySwimDownUp(first, last, 1);
        enemySwimRightLeft(first, last, speed);
        break;
    }
    if (countAndFlags & 0x10) enemyShoot(first, last);
    first = last;
  }
  checkEndWave();
}

// BOSS ATTACKS
///////////////
void wave250()
{
  //Shark attack
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&sharkAttackFases[endBoss.attackFase]))();
  if (!bitRead(endBoss.characteristics, 7)) currentWave++;
}

void wave251()
{
  //seahorse attack
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&seahorseAttackFases[endBoss.attackFase]))();
  if (!bitRead(endBoss.characteristics, 7)) currentWave++;
}

void wave252()
{
  //pirateShip attack
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&pirateShipAttackFases[endBoss.attackFase]))();
  if (!bitRead(endBoss.characteristics, 7)) currentWave++;
}

void wave253()
{
  //Explosions
  checkExplosions();
}


// END WAVES
///////////////
void wave254()
{
  gameState = STATE_GAME_NEXT_STAGE;
}

void wave255()
{
  mermaid.x = 16;
  mermaid.y = 32;
  gameState = STATE_GAME_ENDED;
}


// 250 - 255: boss attacks, explosions, next stage, end of the game
typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM specialWaves[] = { wave250, wave251, wave252, wave253, wave254, wave255 };

void runWave(byte waveNumber)
{
  if (waveNumber == 0) wait();
  else if (waveNumber < 100) runEnemyWave(waveNumber);
  else if (waveNumber < 200)
  {
    powerUPSet(waveNumber - 100);
    currentWave++;
  }
  else ((FunctionPointer) pgm_read_word (&specialWaves[waveNumber - 250]))();
}

// wave numbers: 0 = wait, 1 - 18 = enemy waves (enemyWaves[]), 100 - 106 = power ups (100 + POWER_UP_...),
// 250 - 255 = special waves (specialWaves[])
const byte PROGMEM stages[TOTAL_AMOUNT_OF_STAGES][TOTAL_AMOUNT_OF_WAVES] =
{
  //PART 1
  { //STAGE 1
    1,
    1,
    2,
    101, //POWER_UP_SHIELD
    3,
    5,
    5,
    106, //POWER_UP_STAR
    1,
    2,
    1,
    103, //POWER_UP_BUBBLE
    2,
    3,
    4,
    106, //POWER_UP_STAR
    4,
    1,
    5,
    100, //POWER_UP_HEART
    1,
    5,
    7,
    0,
    254,
  },
  { //STAGE 2
    1,
    1,
    2,
    104, //POWER_UP_SEASHELL
    2,
    3,
    1,
    106, //POWER_UP_STAR
    2,
    2,
    3,
    101, //POWER_UP_SHIELD
    3,
    4,
    7,
    106, //POWER_UP_STAR
    7,
    5,
    6,
    100, //POWER_UP_HEART
    5,
    6,
    7,
    0,
    254,
  },
  { //STAGE 3
    10,
    9,
    8,
    101, //POWER_UP_SHIELD
    6,
    5,
    11,
    106, //POWER_UP_STAR
    11,
    5,
    6,
    100, //POWER_UP_HEART
    8,
    9,
    10,
    106, //POWER_UP_STAR
    9,
    6,
    5,
    103, //POWER_UP_BUBBLE
    5,
    11,
    250,
    253,
    254,
  },

  //PART 2
  { //STAGE 4
    12,
    1,
    12,
    100, //POWER_UP_HEART
    1,
    13,
    2,
    106, //POWER_UP_STAR
    13,
    1,
    12,
    105, //POWER_UP_MAGIC
    1,
    13,
    7,
    106, //POWER_UP_STAR
    11,
    10,
    13,
    102, //POWER_UP_TRIDENT
    7,
    12,
    1,
    0,
    254,
  },
  { //STAGE 5
    15,
    15,
    14,
    104, //POWER_UP_SEASHELL
    13,
    6,
    5,
    106, //POWER_UP_STAR
    6,
    10,
    15,
    101, //POWER_UP_SHIELD
    14,
    13,
    13,
    106, //POWER_UP_STAR
    9,
    8,
    6,
    100, //POWER_UP_HEART
    15,
    14,
    13,
    0,
    254,
  },
  { //STAGE 6
    1,
    2,
    3,
    100, //POWER_UP_HEART
    4,
    5,
    6,
    106, //POWER_UP_STAR
    7,
    8,
    9,
    103, //POWER_UP_BUBBLE
    10,
    11,
    12,
    106, //POWER_UP_STAR
    13,
    14,
    15,
    102, //POWER_UP_TRIDENT
    14,
    13,
    251,
    253,
    254,
  },

  //PART 3
  { //STAGE 7
    12,
    13,
    12,
    100, //POWER_UP_HEART
    10,
    16,
    13,
    106, //POWER_UP_STAR
    12,
    10,
    11,
    105, //POWER_UP_MAGIC
    11,
    7,
    16,
    106, //POWER_UP_STAR
    11,
    10,
    13,
    101, //POWER_UP_SHIELD
    7,
    12,
    1,
    0,
    254,
  },
  { //STAGE 8
    7,
    14,
    17,
    104, //POWER_UP_SEASHELL
    16,
    3,
    1,
    106, //POWER_UP_STAR
    13,
    12,
    3,
    100, //POWER_UP_HEART
    16,
    17,
    16,
    106, //POWER_UP_STAR
    7,
    5,
    10,
    105, //POWER_UP_MAGIC
    9,
    6,
    7,
    0,
    254,
  },
  { //STAGE 9
    16,
    17,
    18,
    102, //POWER_UP_TRIDENT
    4,
    5,
    6,
    106, //POWER_UP_STAR
    7,
    8,
    16,
    100, //POWER_UP_HEART
    17,
    18,
    12,
    106, //POWER_UP_STAR
    14,
    15,
    16,
    100, //POWER_UP_HEART
    17,
    18,
    252,
    253,
    255,
  },
};

void checkCollisions()
{
  Rect mermaidRect = {.x = mermaid.x + MERMAID_COLLISION_OFFSET, .y = mermaid.y + MERMAID_COLLISION_OFFSET, .width = MERMAID_COLLISION_SIZE, .height = MERMAID_COLLISION_SIZE};
  Rect endBossRect = {.x = endBoss.x, .y = endBoss.y + 2, .width = 32, .height = 12};

  ////// Check collision bullets with enemies and bosses /////
  ////////////////////////////////////////////////////////////
  for (byte k = 0; k < MAX_ONSCREEN_BULLETS; k++)
  {
    if (bullet[k].isVisible)
    {
      Rect bulletsRect {.x = bullet[k].x + bulletCollisionOffset[bullet[k].type], .y = bullet[k].y, .width = 8, .height = 8};
      for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
      {
        Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = enemyCollisionWidth[enemy[i].type], .height = enemyCollisionHeight[enemy[i].type]};
        if (bitRead(enemy[i].characteristics, 4) && !bitRead(enemy[i].characteristics, 5) && arduboy.collide(bulletsRect, enemyRect))
        {
          if (!bitRead(enemy[i].characteristics, 6))
          {
            sound.tone(523, 10);
            enemy[i].HP -= bullet[k].damage;
            bitSet(enemy[i].characteristics, 6);
            if (enemy[i].HP < 1) giveBonus(enemiesPoints[enemy[i].type], enemy[i].x, enemy[i].y);
          }
          if (bullet[k].type != WEAPON_TYPE_MAGIC)
          {
            bullet[k].isVisible = false;
          }
        }
      }
      if (bitRead(endBoss.characteristics, 4) && !bitRead(endBoss.characteristics, 5) && !bitRead(endBoss.characteristics, 6))
      {
        switch (endBoss.type)
        {
          case ENDBOSS_SHARK:
            endBossRect = {.x = endBoss.x, .y = endBoss.y + 2, .width = 32, .height = 12};
            break;
          case ENDBOSS_SEAHORSE:
            endBossRect = {.x = endBoss.x + 2, .y = endBoss.y + 2, .width = 6, .height = 6};
            break;
          case ENDBOSS_PIRATESHIP:
            endBossRect = {.x = endBoss.x + 38, .y = endBoss.y + 15, .width = 5, .height = 5};
            break;
        }
        if (arduboy.collide(bulletsRect, endBossRect))
        {
          sound.tone(523, 10);
          bitSet(endBoss.characteristics, 6);
          bullet[k].isVisible = false;
          endBoss.HP -= bullet[k].damage;
          giveBonus(10, endBossRect.x, endBossRect.y);
          if (endBoss.HP < 1) giveBonus(5000, endBossRect.x, endBossRect.y);
        }
      }
    }
  }


  ////// Check collision mermaid with enemies and bosses /////
  ////////////////////////////////////////////////////////////

  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = enemyCollisionWidth[enemy[i].type], .height = enemyCollisionHeight[enemy[i].type]};
    if (bitRead(enemy[i].characteristics, 4) && !bitRead(enemy[i].characteristics, 5) && arduboy.collide(mermaidRect, enemyRect))
    {
      if (!mermaid.isImune && !mermaid.hasShield)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
      if (!bitRead(enemy[i].characteristics, 6))
      {
        bitSet(enemy[i].characteristics, 5);
        sound.tone(2349, 15);
      }
    }
  }
  for (byte i = 0; i < MAX_ONSCREEN_ENEMY_BULLETS; i++)
  {
    Rect enemyBulletRect = {.x = enemyBullet[i].x + 1, .y = enemyBullet[i].y + 1, .width = 6, .height = 6};
    if (enemyBullet[i].isVisible && arduboy.collide(mermaidRect, enemyBulletRect))
    {
      if (!mermaid.isImune && !mermaid.hasShield)
      {
        sound.tone(2349, 15);
        mermaid.isImune = true;
        mermaid.HP -= BULLET_DAMAGE;
        enemyBullet[i].isVisible = false;
      }
    }
  }

  if (bitRead(endBoss.characteristics, 4) && !bitRead(endBoss.characteristics, 5))
  {
    switch (endBoss.type)
    {
      case ENDBOSS_SHARK:
        endBossRect = {.x = endBoss.x, .y = endBoss.y + 2, .width = 32, .height = 12};
        break;
      case ENDBOSS_SEAHORSE:
        endBossRect = {.x = endBoss.x + 2, .y = endBoss.y + 2, .width = 12, .height = 28};
        break;
      case ENDBOSS_PIRATESHIP:
        endBossRect = {.x = endBoss.x + 19, .y = endBoss.y + 10, .width = 46, .height = 40};
        break;
    }
    if (arduboy.collide(mermaidRect, endBossRect))
    {
      if (!bitRead(endBoss.characteristics, 6))
      {
        sound.tone(2349, 15);
        bitSet(endBoss.characteristics, 6);
        endBoss.HP--;
      }
      if (!mermaid.isImune && !mermaid.hasShield)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
    }
  }

  if (powerUP.isActive)
  {
    Rect powerUPRect = {.x = powerUP.x, .y = powerUP.y, .width = 8, .height = 8};
    if (arduboy.collide(mermaidRect, powerUPRect))
    {
      switch (powerUP.type)
      {
        case POWER_UP_HEART:
          if (mermaid.HP < MAX_HP_MERMAID) mermaid.HP++;
          else giveBonus(1000, powerUP.x, powerUP.y);
          break;
        case POWER_UP_SHIELD:
          mermaid.hasShield = true;
          break;
        case POWER_UP_TRIDENT:
          mermaid.weaponType = WEAPON_TYPE_TRIDENT;
          break;
        case POWER_UP_BUBBLE:
          mermaid.weaponType = WEAPON_TYPE_BUBBLES;
          break;
        case POWER_UP_SEASHELL:
          mermaid.weaponType = WEAPON_TYPE_SEASHELL;
          break;
        case POWER_UP_MAGIC:
          mermaid.weaponType = WEAPON_TYPE_MAGIC;
          break;
        case POWER_UP_STAR:
          giveBonus(2500, powerUP.x, powerUP.y);
          break;
      }
      powerUP.isActive = false;
      sound.tone(2093, 15);
      delay (20);
      sound.tone(4186, 30);
    }
  }
}


void drawScore(byte fontType)
{
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawSelfMasked(95 + (5 * i), 0, numbersSmall, 0);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(40 + (7 * i), 40, numbersBig, 0);
        break;
    }
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawSelfMasked(95 + (pad * 5) + (5 * i), 0, numbersSmall, digit);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(40 + (pad * 7) + (7 * i), 40, numbersBig, digit);
        break;
    }
  }
}


#endif
