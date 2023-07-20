#include <stdio.h>
#include <stdlib.h>

#include "GfxEngine.h"
#include "SoundEngine.h"


#ifdef _EE
#include <string.h>
#endif

#ifdef USE_ROMFS
#include "romfs.h"
#include "romfs_io.h"
#endif

#ifdef EMBEDDED_FILES

// BMP files
#include "res/fond1.xpm"
#include "res/fond2.xpm"
#include "res/fond3.xpm"
#include "res/fond4.xpm"
#include "res/fond5.xpm"
#include "res/fond6.xpm"
#include "res/fond7.xpm"
#include "res/fond8.xpm"
#include "res/fond9.xpm"
#include "res/fond10.xpm"
#include "res/fond11.xpm"
#include "res/fond12.xpm"
#include "res/fond13.xpm"
#include "res/nextlevel1.xpm"
#include "res/nextlevel2.xpm"
#include "res/sprite1.xpm"
#ifdef _EE
#include "res/title_froggies.xpm"
#else
#include "res/title.xpm"
#endif


// sound files
extern unsigned char ingame_wav_start[];
extern int ingame_wav_size;
extern unsigned char nextlevel_wav_start[];
extern int nextlevel_wav_size;
extern unsigned char gameover_wav_start[];
extern int gameover_wav_size;
extern unsigned char shoot_sound_wav_start[];
extern int shoot_sound_wav_size;
extern unsigned char ball_explode_wav_start[];
extern int ball_explode_wav_size;
#endif

int fond_loaded=0;

void showScore(char *string,unsigned int x,unsigned int y)

{

	unsigned char i,temp;
	int positionxduzero=148;
	int positionyduzero=226;
	
	temp=strlen(string);
	for(i=0;i<temp;i++)
		{       
          if ( ((*string-48)*13) == 0 )
          {
                    blitImageToScreen(1,((*string-48)*14)+positionxduzero,positionyduzero,13,13,x+(i*8),y,13,13,320,240);
          }
          else
          {
                    blitImageToScreen(1,((*string-48)*14)+positionxduzero+1,positionyduzero,13,13,x+(i*8),y,13,13,320,240);             
          }
          
          string++;
		}
}

void showFond(int level)
{
	#ifdef EMBEDDED_FILES
	if ((level==1) && (fond_loaded!=1)) {loadXpm(fond1_xpm,0);fond_loaded=1;}
	else if ((level==4) && (fond_loaded!=4)) {loadXpm(fond2_xpm,0);fond_loaded=4;}
	else if ((level==7) && (fond_loaded!=7)) {loadXpm(fond3_xpm,0);fond_loaded=7;}
	else if ((level==10) && (fond_loaded!=10)) {loadXpm(fond4_xpm,0);fond_loaded=10;}
	else if ((level==13) && (fond_loaded!=13)) {loadXpm(fond5_xpm,0);fond_loaded=13;}
	else if ((level==16) && (fond_loaded!=16)) {loadXpm(fond6_xpm,0);fond_loaded=16;}
	else if ((level==19) && (fond_loaded!=19)) {loadXpm(fond7_xpm,0);fond_loaded=19;}
	else if ((level==22) && (fond_loaded!=22)) {loadXpm(fond8_xpm,0);fond_loaded=22;}
	else if ((level==25) && (fond_loaded!=25)) {loadXpm(fond9_xpm,0);fond_loaded=25;}
	else if ((level==28) && (fond_loaded!=28)) {loadXpm(fond10_xpm,0);fond_loaded=28;}
	else if ((level==31) && (fond_loaded!=31)) {loadXpm(fond11_xpm,0);fond_loaded=31;}
	else if ((level==34) && (fond_loaded!=34)) {loadXpm(fond12_xpm,0);fond_loaded=34;}
	else if ((level==37) && (fond_loaded!=37)) {loadXpm(fond13_xpm,0);fond_loaded=37;}
	#else
	if ((level==1) && (fond_loaded!=1)) {loadBmp("","","rd/fond1.bmp","/rd/fond1.bmp",0);fond_loaded=1;}
	else if ((level==4) && (fond_loaded!=4)) {loadBmp("","","rd/fond2.bmp","/rd/fond2.bmp",0);fond_loaded=4;}
	else if ((level==7) && (fond_loaded!=7)) {loadBmp("","","rd/fond3.bmp","/rd/fond3.bmp",0);fond_loaded=7;}
	else if ((level==10) && (fond_loaded!=10)) {loadBmp("","","rd/fond4.bmp","/rd/fond4.bmp",0);fond_loaded=10;}
	else if ((level==13) && (fond_loaded!=13)) {loadBmp("","","rd/fond5.bmp","/rd/fond5.bmp",0);fond_loaded=13;}
	else if ((level==16) && (fond_loaded!=16)) {loadBmp("","","rd/fond6.bmp","/rd/fond6.bmp",0);fond_loaded=16;}
	else if ((level==19) && (fond_loaded!=19)) {loadBmp("","","rd/fond7.bmp","/rd/fond7.bmp",0);fond_loaded=19;}
	else if ((level==22) && (fond_loaded!=22)) {loadBmp("","","rd/fond8.bmp","/rd/fond8.bmp",0);fond_loaded=22;}
	else if ((level==25) && (fond_loaded!=25)) {loadBmp("","","rd/fond9.bmp","/rd/fond9.bmp",0);fond_loaded=25;}
	else if ((level==28) && (fond_loaded!=28)) {loadBmp("","","rd/fond10.bmp","/rd/fond10.bmp",0);fond_loaded=28;}
	else if ((level==31) && (fond_loaded!=31)) {loadBmp("","","rd/fond11.bmp","/rd/fond11.bmp",0);fond_loaded=31;}
	else if ((level==34) && (fond_loaded!=34)) {loadBmp("","","rd/fond12.bmp","/rd/fond12.bmp",0);fond_loaded=34;}
	else if ((level==37) && (fond_loaded!=37)) {loadBmp("","","rd/fond13.bmp","/rd/fond13.bmp",0);fond_loaded=37;}
	#endif
    	blitImageToScreen(0,0,0,320,240,0,0,320,240,320,240);

}


int common()
{
  int i;
  
  int nbBall = 0;
  int pause=0;
  
  gbl_evt = EVT_TITLE;

  initGfxEngine();   
  initSpriteEngine();
  initSoundEngine();
  #ifdef ENABLE_JOYSTICK
  initJoystick();
  #endif
  
  #ifdef USE_ROMFS
  extern unsigned char romdisk_start[]; 
  romdisk_mount(romdisk_start);
  rfs_init();
  #endif
 

        loadSound("rd/ingame.wav","/rd/ingame.wav",0);               
        loadSound("rd/nextlevel.wav","/rd/nextlevel.wav",1);               
        loadSound("rd/gameover.wav","/rd/gameover.wav",2);               
        loadSound("rd/shoot_sound.wav","/rd/shoot_sound.wav",3);               
        loadSound("rd/ball_explode.wav","/rd/ball_explode.wav",4);
                      
	
	#ifdef EMBEDDED_FILES  
  	loadXpm(sprite1_xpm,1);
  	#else
  	loadBmp("","","rd/sprite1.bmp","/rd/sprite1.bmp",1);
  	#endif

	getImage(ANIM_RIGHT1,70,117,31,32,1,320,240);
	getImage(ANIM_RIGHT2,118,117,31,32,1,320,240);
	getImage(ANIM_RIGHT3,164,117,31,32,1,320,240);
	getImage(ANIM_LEFT1,70,153,31,32,1,320,240);
	getImage(ANIM_LEFT2,118,153,31,32,1,320,240);
	getImage(ANIM_LEFT3,164,153,31,32,1,320,240);
	getImage(ANIM_SHOOT,67,70,31,32,1,320,240);
	getImage(ANIM_STOP,67,70,31,32,1,320,240);
	getImage(ANIM_DEAD,168,54,48,40,1,320,240);
	getImage(BIG,10,7,48,40,1,320,240);
	getImage(NORMAL,70,6,32,26,1,320,240);
	getImage(SMALL,109,20,16,14,1,320,240);
	getImage(MICRO,131,28,8,7,1,320,240);
	getImage(PF_CASSABLE,20,78,32,8,1,320,240);
	getImage(PF_INCASSABLE,20,88,32,8,1,320,240);
	getImage(PF_CASSABLEV,11,102,8,32,1,320,240);
	getImage(PF_INCASSABLEV,21,102,8,32,1,320,240);
	getImage(PF_MOYEN_INCASSABLE,38,102,16,8,1,320,240);
	getImage(PF_MOYEN_CASSABLE,38,112,16,8,1,320,240);
	getImage(PF_MICRO_INCASSABLE,45,122,8,8,1,320,240);
	getImage(PF_MICRO_CASSABLE,45,132,8,8,1,320,240);
	getImage(ANIM_LADDER1,200,191,26,32,1,320,240);
	getImage(ANIM_LADDER2,230,191,26,32,1,320,240);

  
  initBalls();
  initPlateformes();
  initPlayer();
  initLadders();
  initShoot();
  
  
  
   while(1)
  {
           
           
		if (gbl_evt == EVT_TITLE)
		{
			releaseAllSprite();
			#ifdef EMBEDDED_FILES     
      		 	loadXpm(title_froggies_xpm,2);
      		 	#else                                         
      		 	loadBmp("","","rd/title.bmp","/rd/title.bmp",2);
      		 	#endif
      		 	
      		 
			blitImageToScreen(2,0,0,320,240,0,0,320,240,320,240);			

                	flipScreen();
	    		waitInMs(100);
	    		while (keyAction1==0){checkController();printf("");/*i=rand();*/}	
	    		while (keyAction1==1){checkController();printf("");/*i=rand();*/}				
			
			
			gbl_evt=EVT_NULL;
			initPlayer();
  			initLevel(currentLevel);   						
		}
		else if (gbl_evt==EVT_NULL) 
		{
					
             	while (keyAction4==1)
                {     
                      pause=1;
                      checkController();
                }				
	    		
                while (pause==1)
                {
                      checkController();
                      if (keyAction4==1) 
                      {
                         	while (keyAction4==1)
                           {     
                                 checkController();                                       
                           }
                           pause=0;
                           
                      }
                }

                          
               playSound(0,-1);
             
			int old_score=player.score;
			showFond(currentLevel);
			if (player.bonus_protection==1) 
			{
				if (player.bonus_protection_timer==-1)
				{
                  			blitImageToScreen(1,231,123,43,43,player.posx-5,player.posy-5,43,43,320,240);
				}
				else
				{
					if (gbl_timer%2==0)
					{
                  				blitImageToScreen(1,231,123,43,43,player.posx-5,player.posy-5,43,43,320,240);
					}	
				}
			}
			for (i=0;i<MAX_PLATEFORME;i++)
			{
				showPlateforme(i);
			}
			for (i=0;i<MAX_ECHELLE;i++) showLadder(i);
			updatePlayer(); 
			for (i=0;i<MAX_SHOOT;i++)
			{
				updateShoot(i);
				showShoot(i);
			}
			nbBall=0; 
			for (i=0;i<MAX_BALL;i++)
			{
				nbBall += ball[i].utilise;
				//if ((onetwo==0) || (onetwo==2) || (onetwo==4)) // speed up the balls
				if ((onetwo==0) || (onetwo==3))
					updateBalls(i);
						

						
				if ((player.bonus_freeze>0) && (player.bonus_freeze<81))
				{
					if (gbl_timer%2==0) showBall(i);	
				}
				else
				{
					showBall(i);				
				}
			}
			for (i=0;i<MAX_BONUS;i++)
			{
				updateBonus(i);
				showBonus(i);
			}
			if (nbBall==0) 
			{
				gbl_evt=EVT_NEXT_LEVEL;
			}
			showPlayer();
			for (i=0;i<MAX_OBJETS;i++)
			{
				showObjet(i);
			}
			for (i=0;i<player.nblive;i++)
			{
				if (i<3)
				{
                  			blitImageToScreen(1,179,191,18,18,10+i*20,215,18,18,320,240);
				}
			}
			char chaine[10];
			sprintf(chaine, "%d", player.score);	
            		blitImageToScreen(1,242,65,38,11,110+20,210,38,11,320,240); // Affiche SCORE:
            		showScore(chaine,80+70+20,209);
			sprintf(chaine, "%d", currentLevel);	
            		blitImageToScreen(1,99,44,36,14,110+20,224,36,14,320,240); // Affiche LEVEL:
            		showScore(chaine,80+70+20,224);

			sprintf(chaine, "%d", chrono);	
			sprintf(debug,"%s","");
			if ((old_score<600) && (player.score>=600)) {createObjet(OBJ_1UP,player.posx,player.posy,0);player.nblive++;}
			if ((old_score<1500) && (player.score>=1500)) {createObjet(OBJ_1UP,player.posx,player.posy,0);player.nblive++;}
			if ((old_score<5000) && (player.score>=5000)) {createObjet(OBJ_1UP,player.posx,player.posy,0);player.nblive++;}
			if (gbl_timer==1) chrono--;
			if (chrono<0) chrono=0;
		}
		else if (gbl_evt==EVT_LOOSE_LIFE)
		{
			forceClearSound(0);
			forceClearSound(3);
			forceClearSound(4);
			printf("");
			/* Animation de perte de vie ! */
			int cpt = 0;
			while (cpt!=70)
			{
				printf("");
				showFond(currentLevel);
				for (i=0;i<MAX_ECHELLE;i++) showLadder(i);
				for (i=0;i<MAX_BALL;i++)
				{			
					showBall(i);				
				}
				for (i=0;i<MAX_PLATEFORME;i++)
				{
					showPlateforme(i);
				}								
				
				showPlayer();
				if (cpt>20) player.anim_courante = ANIM_DEAD;				
				if ((cpt>20) && (cpt<40)) player.posy--;
				if (cpt>40) {player.posy++;player.posx++;}		
				cpt ++;
				
                	flipScreen();
                	#ifdef PC
                	waitInMs(20);
                	#endif
			
			}
						
			releaseAllSprite();
			/* Réinitialiser d'abord le joueur avant les niveaux pour histoire de sprite ! */
			reInitPlayer();
			initLevel(currentLevel);
			gbl_evt=EVT_NULL; 		
			if (player.nblive==0) gbl_evt=EVT_GAME_OVER;            		
		}
		else if (gbl_evt==EVT_NEXT_LEVEL)
		{
            		forceClearSound(0);
            		printf("");
			releaseAllSprite();
            		playSound(1,0);
            		printf("");
			if ((currentLevel%2)==0)
			{
			 #ifdef EMBEDDED_FILES 
           		 loadXpm(nextlevel1_xpm,2);
           		 #else
           		 loadBmp("","","rd/nextlevel1.bmp","/rd/nextlevel1.bmp",2);
           		 #endif
                 	 blitImageToScreen(2,0,0,320,240,0,0,320,240,320,240);			
			}
			else
			{
			 #ifdef EMBEDDED_FILES 
           		 loadXpm(nextlevel2_xpm,2);      		 
           		 #else
           		 loadBmp("","","rd/nextlevel2.bmp","/rd/nextlevel2.bmp",2);      		 
           		 #endif
                 	 blitImageToScreen(2,0,0,320,240,0,0,320,240,320,240);			
			}
			char chaine[10];
			sprintf(chaine, "%d", player.score);	
            		blitImageToScreen(1,242,65,38,11,110,218,38,11,320,240); // Affiche le mot SCORE:
            		showScore(chaine,183,217);

                	flipScreen();
                	#ifdef PC
	    		waitInMs(250);
	    		#endif
	    		checkController();
	    		while (keyAction1==0){checkController();printf("");/*i=rand();*/}	
	    		while (keyAction1==1){checkController();printf("");/*i=rand();*/}				

			currentLevel++;
			if (currentLevel>MAX_LEVEL) currentLevel=1;
			reInitPlayer();
			initLevel(currentLevel);
			gbl_evt=EVT_NULL;
			forceClearSound(1);
		}
		else if (gbl_evt==EVT_GAME_OVER)
		{
            		forceClearSound(0);
            		playSound(2,0);
			printf("");
			releaseAllSprite();
			/* Animation de perte de gameOver ! */
			int cpt = 0;
			while (cpt<230)
			{
				printf("");
				/* reaffiche le fond */
				showFond(currentLevel);
				/* anime le game over */
               			blitImageToScreen(1,8,218,130,15,320-cpt,100,130,15,320,240);			
				cpt +=3;
				char chaine[10];
				sprintf(chaine, "%d", player.score);	
            			blitImageToScreen(1,242,65,38,11,110+20,210,38,11,320,240); // Affiche SCORE:
            			showScore(chaine,80+70+20,209);
				sprintf(chaine, "%d", currentLevel);	
            			blitImageToScreen(1,99,44,36,14,110+20,224,36,14,320,240); // Affiche LEVEL:
            			showScore(chaine,80+70+20,224);
			
                		flipScreen();
                		#ifdef PC
                		waitInMs(20);
                		#endif
			}
			
			
	    		while (keyAction1==0){checkController();printf("");/*i=rand();*/}	
	    		while (keyAction1==1){checkController();printf("");/*i=rand();*/}			
			
			forceClearSound(2);
			initPlayer();
			initLevel(1);
			gbl_evt=EVT_TITLE;
			currentLevel=1;
		}
                                                               
   	flipScreen();
   	//clearSound(3);
   	//clearSound(4);
   
        onetwo ++;
    	if (onetwo>5) onetwo=0;    
	gbl_timer ++;
	if (gbl_timer==51) gbl_timer=1;
   
    	#ifdef PC
    	waitInMs(20);
    	#endif
    
    	checkController();
    	if (keyQuit==1) return 0;   
	}    

}


int main(int argc, char *argv[])
{         
        common();
 	return 0; 
}























