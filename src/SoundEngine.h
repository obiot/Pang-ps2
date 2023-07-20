#ifndef	SOUNDENGINE_H
#define SOUNDENGINE_H 

#include "SDL.h"
#include "SDL_mixer.h"

extern Mix_Chunk *sound[10];

void initSoundEngine();
//#ifdef EMBEDDED_FILES
//void loadEmbeddedSound(unsigned char *data, int size, int soundNumber);
//#else
void loadSound(char *filenameDreamcast,char *filenamePC,int soundNumber);
//#endif

void playSound(int soundNumber,int number);
void clearSound(int soundNumber);
void forceClearSound (int soundNumber);
void quitSoundEngine();

#endif
