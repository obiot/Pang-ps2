#ifndef	GFXENGINE_H
#define GFXENGINE_H 

#include "SDL.h"

#include "actions.h"
#include "ball.h"
#include "collisions.h"
#include "plateforme.h"
#include "player.h"
#include "shoot.h"
#include "levels.h"
#include "ladder.h"
#include "structures.h"
#include "objets.h"
#include "bonus.h"



#define MAX_SPRITE 500
#define MAX_IMAGE 5000
#define MAX_TILE 500
#define MAX_MAP 2
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100

extern SDL_Surface *screen;
extern SDL_Surface *images[4];
extern int mapTiles[MAX_MAP][MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
extern int currentWorldMapX[MAX_MAP];
extern int currentWorldMapY[MAX_MAP];


#ifdef ENABLE_JOYSTICK
extern SDL_Joystick *joy;
#endif

extern int posxjoy;
extern int posyjoy;

extern Uint32 sstart;
extern Uint32 ssend;

extern int keyRight;
extern int keyLeft;
extern int keyUp;
extern int keyDown;
extern int keyQuit;

extern int keyAction1;
extern int keyAction2;
extern int keyAction3;
extern int keyAction4;
extern int keyActionPause;
extern int myEvent;

typedef struct si {
	int imagex;
	int imagey;
	int imageh;
	int imagel;
	int transparentColor;
	int banque;
	int banqueHeight;
	int banqueWidth;
} simage;

typedef struct ss{
	int utilise;
	int posx;
	int posy;
	int image;

	int animation[10][20]; // 10 animations de 20 frames (-1 = on boucle )
	int animation_speed[10];   // vitesse de l'animation
	int current_animation; // animation courante -1 non animé
	int current_animation_frame;

	int intern1;
} ssprite;

typedef struct st {
	int image;
	int attr1;
	int attr2;
	int attr3;
} stile;

extern ssprite sprite[MAX_SPRITE];
extern simage imageBank[MAX_IMAGE];
extern stile tiles[MAX_TILE];

void initTileEngine();
void blitImageToScreen(int imageNo,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh,int ttw,int tth);
void createTile(int n,int imageNo,int a1,int a2,int a3);
void setTileInMap(int mapNo,int x,int y,int tileNo);
void setWorldView(int mapNo,int x,int y);
void mapDraw(int mapNo);
void initGfxEngine();
#ifdef EMBEDDED_FILES
int loadXpm(char ** xpmData, int noImage);
#else
int loadBmp(char *path,char *filename,char * pathfilename,char *pathdc,int noImage);
#endif
void flipScreen();
void waitInMs(int ms);
void synchroStart();
void synchroEnd(int ms);
int getTicks();
void checkController();
void initSpriteEngine();
void getImage(int n,int x,int y,int l,int h,int imageNo,int w,int he);
void initSprite(int n,int x,int y,int i);
int initFreeSprite(int x,int y,int i);
#ifdef ENABLE_JOYSTICK
void initJoystick(void);
#endif
void releaseSprite(int n);
void releaseAllSprite();
void animateSprite(int s,int a);
void setSpriteAnimation(int s,int a,int speed,int f0,int f1,int f2,int f3,int f4,int f5,int f6,int f7,int f8,int f9,int f10,int f11,int f12,int f13,int f14,int f15,int f16,int f17,int f18,int f19);
void moveSprite(int n,int x,int y);
void changeSpriteImage(int n,int i);
void pasteImage(int n,int x,int y);
void showSprite(int n);
void stopAnimateSprite(int s);
void showLRSprite(int n);
void showAllSprite();
unsigned int getPixel(int imageNo,int x,int y,int h);
int isSpriteCollide(int sprite1,int sprite2);

#endif
