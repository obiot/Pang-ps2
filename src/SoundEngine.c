#include "SDL.h"
#include "SDL_mixer.h"

#ifdef USE_ROMFS
#include "romfs.h"
#include "romfs_io.h"
#endif


Mix_Chunk *sound0 = NULL;
Mix_Chunk *sound1 = NULL;
Mix_Chunk *sound2 = NULL;
Mix_Chunk *sound3 = NULL;
Mix_Chunk *sound4 = NULL;
Mix_Chunk *sound5 = NULL;
Mix_Chunk *sound6 = NULL;
Mix_Chunk *sound7 = NULL;
Mix_Chunk *sound8 = NULL;
Mix_Chunk *sound9 = NULL;
Mix_Chunk *sound10 = NULL;


int soundUsed0 = 0;
int soundUsed1 = 0;
int soundUsed2 = 0;
int soundUsed3 = 0;
int soundUsed4 = 0;
int soundUsed5 = 0;
int soundUsed6 = 0;
int soundUsed7 = 0;
int soundUsed8 = 0;
int soundUsed9 = 0;
int soundUsed10 = 0;


#ifdef _EE
static void print_format()
{
	int audio_channels;
	int audio_rate;
	Uint16 audio_format;

	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
		(audio_format & 0xFF),
		(audio_channels > 2) ? "surround" : (audio_channels > 1) ? "stereo" : "mono");
}
#endif

void initSoundEngine()
{
     	//int tmp=0;
 	int audio_rate = 22050;
 	Uint16 audio_format = AUDIO_S16;
 	int audio_channels = 1;

#ifdef _EE 	
 	int audio_buffers = 1024;
#else
 	int audio_buffers = 4096;
#endif
	

 	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
 	{
	 	fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
	  	exit(1);
  	}
#ifdef _EE
	print_format();
#endif
}


void loadSound(char *filenamePC,char *filenameDreamcast,int soundNumber)
{
#ifdef USE_ROMFS
 	
 	SDL_RWops *context;
 	
 	char *ptr; //ptr on datastruc file 
 	int fd;
 	
 	
 	fd = rfs_open(filenamePC);
	
	ptr = malloc(sizeof(char)*(rfs_size()+1));
	
	rfs_read(ptr,rfs_size());
	
	context = SDL_RWFromMem(ptr,rfs_size());
  	
 	  if (soundNumber==0)  sound0 = Mix_LoadWAV_RW(context, 1);
     else if (soundNumber==1)  sound1 = Mix_LoadWAV_RW(context, 1);
     else if (soundNumber==2)  sound2 = Mix_LoadWAV_RW(context, 1);
     else if (soundNumber==3)  sound3 = Mix_LoadWAV_RW(context, 1);
     else if (soundNumber==4)  sound4 = Mix_LoadWAV_RW(context, 1);
#else
  
     if (soundNumber==0)  sound0 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==1)  sound1 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==2)  sound2 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==3)  sound3 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==4)  sound4 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==5)  sound5 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==6)  sound6 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==7)  sound7 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==8)  sound8 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==9)  sound9 = Mix_LoadWAV(filenamePC);
     else if (soundNumber==10)  sound10 = Mix_LoadWAV(filenamePC);
#endif

}
//#endif

void playSound(int soundNumber,int numberLoop)
{
 int channel=0;
 
 printf ("");
 
 switch (soundNumber)
 { 
    case 0 : if (Mix_Playing(soundNumber) == 0)
    	    	    channel = Mix_PlayChannel(0, sound0, -1);
    	     break;
    case 1 : if (Mix_Playing(soundNumber) == 0)
    	     	    channel = Mix_PlayChannel(1, sound1, numberLoop);
    	     break;	
    	
    case 2 : if (Mix_Playing(soundNumber) == 0)
    	     	   channel = Mix_PlayChannel(2, sound2, numberLoop);
    	     break;
    	
    case 3 : channel = Mix_PlayChannel(3, sound3, numberLoop);
    	     break;
    	
    case 4 : channel = Mix_PlayChannel(4, sound4, numberLoop);
    	     break;
    	
    default : printf("unknow sound %d",soundNumber);
    	      channel= -1;
    	      break;
   
 }
 
 printf ("");
 
 if(channel == -1)
   fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());

}

/*
  0 - pas clear
  1 - clear
*/
int clearSound(int soundNumber)
{

   Mix_HaltChannel(soundNumber);
   printf("");
     
   return 1;
}
 
void forceClearSound (int soundNumber)
{
    Mix_HaltChannel(soundNumber);
    printf("");
}

void quitSoundEngine()
{
     Mix_CloseAudio();
}
