/*
*
*
*/
#include <asf.h>
#include <samd21g18a.h>
#include <stdlib.h>
#include "user_gpio.h"
#include "user_spi.h"
#include "user_clock.h"
#include "def.h"
#include "ft8xx.h"

#include <math.h>





#define CHAPTER_8B 0
#define CHAPTER_10A 1
#define CHAPTER_11B 0

#if CHAPTER_8B

#define SIZE_OF_FLOG_16BIT_96X96 (96*2*96)
extern const unsigned char flog_16bit_96x96[];


#define SIZE_OF_GEAR (0x11370)
extern const unsigned char gear2_jpg_480_272[];
#endif


unsigned int cmdOffset = 0x0000;

GPIO_INIT_TABLE test[]=
{
	{ GPIO_PA20, USE_GPIO_FUNC, USE_GPIO_OUTPUT, PA20_USE_SERCOM3_PAD_2 },//nCS
	{ GPIO_PA21, USE_GPIO_FUNC, USE_GPIO_INPUT , PA21_USE_SERCOM3_PAD_3 },//MISO
	{ GPIO_PA22, USE_GPIO_FUNC, USE_GPIO_OUTPUT, PA22_USE_SERCOM3_PAD_0 },//MOSI
	{ GPIO_PA23, USE_GPIO_FUNC, USE_GPIO_OUTPUT, PA23_USE_SERCOM3_PAD_1 },//SCK

	{ GPIO_ENDMARK,0,0,0},
};



GPIO_INIT_TABLE test2[]=
{
	{ GPIO_PA12, USE_GPIO_FUNC, USE_GPIO_OUTPUT,PA12_USE_SERCOM2_PAD_0 },
	{ GPIO_PA13, USE_GPIO_FUNC, USE_GPIO_OUTPUT,PA13_USE_SERCOM2_PAD_1 },
	{ GPIO_PA14, USE_GPIO_PORT, USE_GPIO_OUTPUT,0 },
	{ GPIO_PA15, USE_GPIO_FUNC, USE_GPIO_INPUT ,PA15_USE_SERCOM2_PAD_3 },
	{ GPIO_ENDMARK,0,0,0},
};


volatile UserWait( unsigned long time )
{
	while( time-- )
	{
		
	};
}


void configure_dfll_open_loop(void)
{
    struct system_clock_source_dfll_config config_dfll;
    system_clock_source_dfll_get_config_defaults(&config_dfll);
    system_clock_source_dfll_set_config(&config_dfll);
}

void ClockInitTest(void)
{
	/* Enable the external 32KHz oscillator */
	enum status_code osc32k_status = system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);

	if (osc32k_status != STATUS_OK)
	{
	/* Error enabling the clock source */
	}

	/* Configure the DFLL in open loop mode using default values */
	configure_dfll_open_loop();
	/* Enable the DFLL oscillator */

	enum status_code dfll_status = system_clock_source_enable(SYSTEM_CLOCK_SOURCE_DFLL);
	if(dfll_status != STATUS_OK)
	{
	/* Error enabling the clock source */
	}
	/* Configure flash wait states before switching to high frequency clock */
	system_flash_set_waitstates(2);
	/* Change system clock to DFLL */

	struct system_gclk_gen_config config_gclock_gen;

	system_gclk_gen_get_config_defaults(&config_gclock_gen);
	config_gclock_gen.source_clock    = SYSTEM_CLOCK_SOURCE_DFLL;
	config_gclock_gen.division_factor = 1;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &config_gclock_gen);
}






#if CHAPTER_10A


#define CHARCTOR_SIZE_X 32
#define CHARCTOR_SIZE_Y 32
#define IMAGE_SIZE_X 256
#define IMAGE_SIZE_Y 256
#define SCREEN_WX 480
#define SCREEN_WY 272
#define COLOR_DPTH 2
#define GRID_X ((SCREEN_WX/CHARCTOR_SIZE_X)/2*2+1)
#define GRID_Y ((SCREEN_WY/CHARCTOR_SIZE_Y)/2*2+1)

const unsigned long offset_list[]=
{
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(0*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(1*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(2*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(3*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(4*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(5*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(6*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),

	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((0*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((1*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((2*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((3*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((4*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((5*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((6*CHARCTOR_SIZE_X)*2),
	(7*CHARCTOR_SIZE_Y)*(IMAGE_SIZE_X*2)+((7*CHARCTOR_SIZE_X)*2),
};



const unsigned char demo_mapchip[]=
{
	#include "pipo-map001_256x256b.binh"
};
//#define SIZE_OF_DEMO_MAPCHIP (0x6270)
#define SIZE_OF_DEMO_MAPCHIP (0x99A0)


unsigned char map[GRID_Y][GRID_X];

const unsigned char FieldMap[64*64]=
{
	#include "test3.map"
};


#endif










#if CHAPTER_11B



#define GRID_X (15)
#define GRID_Y (9)

#define SIZE_OF_SPRITE 0x5BA0

const unsigned char SampleSprite[]=
{
	#include "sprite.binh"
};


struct AnimeTimeTable
{
	unsigned long ImageOffset;
	unsigned short Time;
	struct AnimeTimeTable *next;
};


struct AnimeTimeTable Player1_N[]=
{
	{ 0 * 256*2 + 32*2, 10,&Player1_N[1] },
	{ 0 * 256*2 + 64*2, 10,&Player1_N[2] },
	{ 0 * 256*2 + 32*2, 10,&Player1_N[3] },
	{ 0 * 256*2 +  0*2, 10,&Player1_N[0] },
};

struct AnimeTimeTable Player1_E[]=
{
	{ 32 * 256*2 + 32*2, 10,&Player1_E[1] },
	{ 32 * 256*2 + 64*2, 10,&Player1_E[2] },
	{ 32 * 256*2 + 32*2, 10,&Player1_E[3] },
	{ 32 * 256*2 +  0*2, 10,&Player1_E[0] },
};

struct AnimeTimeTable Player1_S[]=
{
	{ 64 * 256*2 + 32*2, 10,&Player1_S[1] },
	{ 64 * 256*2 + 64*2, 10,&Player1_S[2] },
	{ 64 * 256*2 + 32*2, 10,&Player1_S[3] },
	{ 64 * 256*2 +  0*2, 10,&Player1_S[0] },
};

struct AnimeTimeTable Player1_W[]=
{
	{ 96 * 256*2 + 32*2, 10,&Player1_W[1] },
	{ 96 * 256*2 + 64*2, 10,&Player1_W[2] },
	{ 96 * 256*2 + 32*2, 10,&Player1_W[3] },
	{ 96 * 256*2 +  0*2, 10,&Player1_W[0] },
};


struct AnimeTimeTable Player2_N[]=
{
	{ 128 * 256*2 + 32*2, 10,&Player2_N[1] },
	{ 128 * 256*2 + 64*2, 10,&Player2_N[2] },
	{ 128 * 256*2 + 32*2, 10,&Player2_N[3] },
	{ 128 * 256*2 +  0*2, 10,&Player2_N[0] },
};

struct AnimeTimeTable Player2_E[]=
{
	{ 160 * 256*2 + 32*2, 10,&Player2_E[1] },
	{ 160 * 256*2 + 64*2, 10,&Player2_E[2] },
	{ 160 * 256*2 + 32*2, 10,&Player2_E[3] },
	{ 160 * 256*2 +  0*2, 10,&Player2_E[0] },
};

struct AnimeTimeTable Player2_S[]=
{
	{ 192 * 256*2 + 32*2, 10,&Player2_S[1] },
	{ 192 * 256*2 + 64*2, 10,&Player2_S[2] },
	{ 192 * 256*2 + 32*2, 10,&Player2_S[3] },
	{ 192 * 256*2 +  0*2, 10,&Player2_S[0] },
};

struct AnimeTimeTable Player2_W[]=
{
	{ 224 * 256*2 + 32*2, 10,&Player2_W[1] },
	{ 224 * 256*2 + 64*2, 10,&Player2_W[2] },
	{ 224 * 256*2 + 32*2, 10,&Player2_W[3] },
	{ 224 * 256*2 +  0*2, 10,&Player2_W[0] },
};


struct AnimeTimeTable Player3_N[]=
{
	{ 0 * 256*2 + 128*2, 10,&Player3_N[1] },
	{ 0 * 256*2 + 160*2, 10,&Player3_N[2] },
	{ 0 * 256*2 + 128*2, 10,&Player3_N[3] },
	{ 0 * 256*2 +  96*2, 10,&Player3_N[0] },
};

struct AnimeTimeTable Player3_E[]=
{
	{ 32 * 256*2 + 128*2, 10,&Player3_E[1] },
	{ 32 * 256*2 + 160*2, 10,&Player3_E[2] },
	{ 32 * 256*2 + 128*2, 10,&Player3_E[3] },
	{ 32 * 256*2 + 96*2, 10,&Player3_E[0] },
};

struct AnimeTimeTable Player3_S[]=
{
	{ 64 * 256*2 + 128*2, 10,&Player3_S[1] },
	{ 64 * 256*2 + 160*2, 10,&Player3_S[2] },
	{ 64 * 256*2 + 128*2, 10,&Player3_S[3] },
	{ 64 * 256*2 + 96*2, 10,&Player3_S[0] },
};

struct AnimeTimeTable Player3_W[]=
{
	{ 96 * 256*2 + 128*2, 10,&Player3_W[1] },
	{ 96 * 256*2 + 160*2, 10,&Player3_W[2] },
	{ 96 * 256*2 + 128*2, 10,&Player3_W[3] },
	{ 96 * 256*2 + 96*2, 10,&Player3_W[0] },
};


struct AnimeTimeTable Player4_N[]=
{
	{ 128 * 256*2 + 128*2, 10,&Player4_N[1] },
	{ 128 * 256*2 + 160*2, 10,&Player4_N[2] },
	{ 128 * 256*2 + 128*2, 10,&Player4_N[3] },
	{ 128 * 256*2 + 96*2, 10,&Player4_N[0] },
};

struct AnimeTimeTable Player4_E[]=
{
	{ 160 * 256*2 + 128*2, 10,&Player4_E[1] },
	{ 160 * 256*2 + 160*2, 10,&Player4_E[2] },
	{ 160 * 256*2 + 128*2, 10,&Player4_E[3] },
	{ 160 * 256*2 + 96*2, 10,&Player4_E[0] },
};

struct AnimeTimeTable Player4_S[]=
{
	{ 192 * 256*2 + 128*2, 10,&Player4_S[1] },
	{ 192 * 256*2 + 160*2, 10,&Player4_S[2] },
	{ 192 * 256*2 + 128*2, 10,&Player4_S[3] },
	{ 192 * 256*2 + 96*2, 10,&Player4_S[0] },
};

struct AnimeTimeTable Player4_W[]=
{
	{ 224 * 256*2 + 128*2, 10,&Player4_W[1] },
	{ 224 * 256*2 + 160*2, 10,&Player4_W[2] },
	{ 224 * 256*2 + 128*2, 10,&Player4_W[3] },
	{ 224 * 256*2 + 96*2, 10,&Player4_W[0] },
};


#endif
















#if CHAPTER_11B

struct AnimeEntry
{
	unsigned short CHARACTOR_SIZE_X;
	unsigned short CHARACTOR_SIZE_Y;  
	struct AnimeTimeTable *table;//offset,time,next
};

struct AnimeWork
{
	unsigned short CHARACTOR_SIZE_X;
	unsigned short CHARACTOR_SIZE_Y;  
	struct AnimeTimeTable *table;
	struct AnimeTimeTable Now;
};

struct AnimeImage
{
	unsigned long ImageBase;
//---
	unsigned short IMAGE_SIZE_X;
	unsigned short IMAGE_SIZE_Y;
	unsigned short COLOR_DPTH;
//---
	struct AnimeWork Entry[32];
};

enum{
	ANIME_CMD_START,
	ANIME_CMD_SET_SIZE,
	ANIME_CMD_SET_IMAGE,
	ANIME_CMD_POSITION,
	ANIME_CMD_END,
};

const struct AnimeEntry PL1S=
{
	32,32,
	&Player1_S[0],
};
const struct AnimeEntry PL1N=
{
	32,32,
	&Player1_N[0],
};
const struct AnimeEntry PL1W=
{
	32,32,
	&Player1_W[0],
};
const struct AnimeEntry PL1E=
{
	32,32,
	&Player1_E[0],
};


const struct AnimeEntry PL2S=
{
	32,32,
	&Player2_S[0],
};
const struct AnimeEntry PL2N=
{
	32,32,
	&Player2_N[0],
};
const struct AnimeEntry PL2W=
{
	32,32,
	&Player2_W[0],
};
const struct AnimeEntry PL2E=
{
	32,32,
	&Player2_E[0],
};


const struct AnimeEntry PL3S=
{
	32,32,
	&Player3_S[0],
};
const struct AnimeEntry PL3N=
{
	32,32,
	&Player3_N[0],
};
const struct AnimeEntry PL3W=
{
	32,32,
	&Player3_W[0],
};
const struct AnimeEntry PL3E=
{
	32,32,
	&Player3_E[0],
};

const struct AnimeEntry PL4S=
{
	32,32,
	&Player4_S[0],
};
const struct AnimeEntry PL4N=
{
	32,32,
	&Player4_N[0],
};
const struct AnimeEntry PL4W=
{
	32,32,
	&Player4_W[0],
};
const struct AnimeEntry PL4E=
{
	32,32,
	&Player4_E[0],
};



void AnimetionImageinit( struct AnimeImage *img, unsigned long image_offset, unsigned short wx, unsigned short wy, unsigned short depth )
{
	if( img != NULL )
	{
		img->ImageBase = image_offset;
		img->IMAGE_SIZE_X = wx;
		img->IMAGE_SIZE_Y = wy;
		img->COLOR_DPTH = depth;
		for( int i=0;i<32;i++ )
		{
			img->Entry[i].CHARACTOR_SIZE_X = 0;
			img->Entry[i].CHARACTOR_SIZE_Y = 0;
			img->Entry[i].table = NULL;
			img->Entry[i].Now.ImageOffset = 0;
			img->Entry[i].Now.Time = 0;
			img->Entry[i].Now.next = NULL;
		}
	}
}

int AnimetionAlloc( struct AnimeImage *img, struct AnimeEntry *entry )
{
	int i,flag,id;

	i = 0;
	flag = 1;
	id = 0;

	while( flag == 1 && i < 32 )
	{
		if( img->Entry[i].table == NULL )
		{
			img->Entry[i].CHARACTOR_SIZE_X = entry->CHARACTOR_SIZE_X;
			img->Entry[i].CHARACTOR_SIZE_Y = entry->CHARACTOR_SIZE_Y;
			img->Entry[i].table = entry->table;
			img->Entry[i].Now = *entry->table;
			id = i;
			flag = 0;
			continue;
		}
		i++;
	};

	if( flag == 0 )
	{
		return id;
	}
	return -1;
}

int AnimetionFree( struct AnimeImage *img, int id )
{
	if( img->Entry[id].table != NULL )
	{
		img->Entry[id].CHARACTOR_SIZE_X = 0;
		img->Entry[id].CHARACTOR_SIZE_Y = 0;
		img->Entry[id].table = NULL;
		img->Entry[id].Now.ImageOffset = 0;
		img->Entry[id].Now.Time = 0;
		img->Entry[id].Now.next = NULL;
	}
	return 0;
}

int AnimetionTaskDriver( struct AnimeImage *img )
{
	int i;

	for( i=0;i<32;i++ )
	{
		if( img->Entry[i].table != NULL )
		{
			if( img->Entry[i].Now.Time == 0 )
			{
				if( img->Entry[i].Now.next != NULL )
				{
					img->Entry[i].Now = *img->Entry[i].Now.next;
				}
			}
			if( img->Entry[i].Now.Time )img->Entry[i].Now.Time--;
		}
	};
	return 0;
}



int AnimetionTrans( unsigned short cmd, unsigned short handle, struct AnimeImage *img, unsigned short x, unsigned short y, int id )
{
	switch( cmd )
	{
		case ANIME_CMD_START:
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_HANDLE(handle) );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_LAYOUT(ARGB1555, img->IMAGE_SIZE_X * img->COLOR_DPTH, img->IMAGE_SIZE_Y) );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			break;
		case ANIME_CMD_SET_SIZE:
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SIZE(NEAREST, 0, 0, img->Entry[id].CHARACTOR_SIZE_X, img->Entry[id].CHARACTOR_SIZE_Y) );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			break;
		case ANIME_CMD_SET_IMAGE:
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BEGIN_BITMAPS );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SOURCE( RAM_G + img->ImageBase + img->Entry[id].Now.ImageOffset ) );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			break;
		case ANIME_CMD_POSITION:
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,VERTEX2F( x ,y) );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			break;
		case ANIME_CMD_END:
			HostMemWriteDoubleWord( RAM_CMD + cmdOffset,DL_END );
			cmdOffset = incCMDOffset(cmdOffset, 4);
			break;
	}
	return 0;
}







#define COUNT_OF_MAN 50

#define DIR_S 0
#define DIR_W 1
#define DIR_N 2
#define DIR_E 3


struct sprite
{
	short x;
	short y;
	int id_set;
	int dir;
	short delta_x;
	short delta_y; 
	int timer;
	int speed;
};



struct sprite man[COUNT_OF_MAN];







void sprite_move( struct sprite *move )
{
	unsigned short rnd_dir = 0;

	if( move->timer == 0 )
	{
		rnd_dir = rand();
		rnd_dir = rand();
		rnd_dir = rand();

		switch( rnd_dir & 0x0003 )
		{
			case DIR_S:
				move->delta_x = 0;
				move->delta_y = 1;
				break;
			case DIR_W:
				move->delta_x = -1;
				move->delta_y = 0;
				break;
			case DIR_N:
				move->delta_x = 0;
				move->delta_y = -1;
				break;
			case DIR_E:
				move->delta_x = 1;
				move->delta_y = 0;
				break;
		}
		rnd_dir = rand();
		move->timer = rnd_dir & 0x3f;
		rnd_dir = rand();
		move->speed = 1 * (rnd_dir & 0x0007)+1;

	}
	move->timer--;
	move->x = move->x + move->delta_x * move->speed;
	move->y = move->y + move->delta_y * move->speed;

	if( move->x > 512 )move->x = -16;
	if( move->y > 304 )move->y = -16;
	if( move->x < -32 )move->x = 496;
	if( move->y < -32 )move->y = 288;

	if( move->delta_x > 0 )move->dir = DIR_E;
	if( move->delta_x < 0 )move->dir = DIR_W;
	if( move->delta_y > 0 )move->dir = DIR_S;
	if( move->delta_y < 0 )move->dir = DIR_N;
}


#endif














int main (void)
{
//	unsigned int cmdOffset = 0x0000;
	unsigned int cmdBufferRd = 0x0000;
	unsigned int cmdBufferWr = 0x0000;
	
	int i,j,k;





	system_clock_init();
	system_gclk_init();

	ClockInitTest();

	UserClockInit();

	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, 1 <<  (2 + PM_APBCMASK_SERCOM0_Pos));
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, 1 <<  (3 + PM_APBCMASK_SERCOM0_Pos));

	GpioPortInit( &test2[0] );
	GpioPortInit( &test2[1] );
	GpioPortInit( &test2[2] );
	GpioPortInit( &test2[3] );

	SercomSPI_Init( SERCOM2, (SPI_CTRLA_MODE00|SPI_CTRLA_PINMODE00|SPI_CTRLA_MSB_FIRST|SPI_CTRLA_FORM_SPI), (SPI_CTRLB_CHSIZE8BIT|SPI_CTRLB_RXEN),0 );
	SercomSPI_Enable( SERCOM2 );



	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);

	HostCommand(HOST_CLKINT,0,0);//send command to "CLKEXT" to FT81X 
	HostCommand(HOST_ACTIVE,0,0);//send host command "ACTIVE" to FT81X 

	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);
	UserWait(100000);

	HostMemWriteByte(REG_CPURESET, 0x01);
	HostMemWriteWord(REG_CMD_READ, 0x0000);
	HostMemWriteWord(REG_CMD_WRITE, 0x0000);
	HostMemWriteByte(REG_CPURESET, 0x00); 

/* Configure display registers - demonstration for WQVGA resolution */ 
	HostMemWriteWord(REG_HSIZE, 480); 
	HostMemWriteWord(REG_HCYCLE, 548); 
	HostMemWriteWord(REG_HOFFSET, 43); 
	HostMemWriteWord(REG_HSYNC0, 0); 
	HostMemWriteWord(REG_HSYNC1, 41); 
	HostMemWriteWord(REG_VSIZE, 272); 
	HostMemWriteWord(REG_VCYCLE, 292); 
	HostMemWriteWord(REG_VOFFSET, 12); 
	HostMemWriteWord(REG_VSYNC0, 0); 
	HostMemWriteWord(REG_VSYNC1, 10); 
	HostMemWriteByte(REG_SWIZZLE, 0); 
	HostMemWriteByte(REG_PCLK_POL, 1); 

	/* write first display list */ 
	HostMemWriteDoubleWord( RAM_DL+0,DL_CLEAR_RGB );
	HostMemWriteDoubleWord( RAM_DL+4,DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG );
	HostMemWriteDoubleWord( RAM_DL+8,DL_DISPLAY );

	HostMemWriteByte(REG_DLSWAP, DLSWAP_FRAME);

	HostMemWriteByte(REG_GPIO_DIR, 0x80); 
	HostMemWriteByte(REG_GPIO, 0x80); 
	HostMemWriteByte(REG_PWM_DUTY, 128); 

	HostMemWriteByte(REG_PCLK, 7);
	HostMemWriteByte(REG_PWM_DUTY, 64);

	do
	{
		cmdBufferRd = HostMemReadWord(REG_CMD_READ);
		cmdBufferWr = HostMemReadWord(REG_CMD_WRITE);
	}while (cmdBufferWr != cmdBufferRd);
	cmdOffset = cmdBufferWr;
//--------------------------------------








#if CHAPTER_11B



	int x,y;
	struct AnimeImage SpriteImage;
	int id[20];
	unsigned short rnd_dir = 0;

	InflateLoad( &SampleSprite[0], RAM_G+0x00000000, (SIZE_OF_SPRITE+3)/4*4 );
//Entry
	AnimetionImageinit( &SpriteImage, 0x00000000, 256, 256, 2 );


	id[0] = AnimetionAlloc( &SpriteImage, &PL1S );
	id[1] = AnimetionAlloc( &SpriteImage, &PL1W );
	id[2] = AnimetionAlloc( &SpriteImage, &PL1N );
	id[3] = AnimetionAlloc( &SpriteImage, &PL1E );

	id[4] = AnimetionAlloc( &SpriteImage, &PL2S );
	id[5] = AnimetionAlloc( &SpriteImage, &PL2W );
	id[6] = AnimetionAlloc( &SpriteImage, &PL2N );
	id[7] = AnimetionAlloc( &SpriteImage, &PL2E );

	id[8] = AnimetionAlloc( &SpriteImage, &PL3S );
	id[9] = AnimetionAlloc( &SpriteImage, &PL3W );
	id[10] = AnimetionAlloc( &SpriteImage, &PL3N );
	id[11] = AnimetionAlloc( &SpriteImage, &PL3E );

	id[12] = AnimetionAlloc( &SpriteImage, &PL4S );
	id[13] = AnimetionAlloc( &SpriteImage, &PL4W );
	id[14] = AnimetionAlloc( &SpriteImage, &PL4N );
	id[15] = AnimetionAlloc( &SpriteImage, &PL4E );

	for( i=0;i<COUNT_OF_MAN;i++ )
	{
		man[i].x = 240;
		man[i].y = 135;

		rnd_dir = rand();
		man[i].id_set = (rnd_dir & 0x03)*4;

		man[i].dir = DIR_E;
		man[i].delta_x = 0;
		man[i].delta_y = 0; 
		man[i].timer = 16;

		rnd_dir = rand();
		man[i].speed = 1;// * (rnd_dir & 0x0007)+1;
	}


	do
	{
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_DLSTART) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR_RGB | BLACK) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset, VERTEX_FORMAT(0) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

//-------------------------
		AnimetionTaskDriver( &SpriteImage );

		AnimetionTrans( ANIME_CMD_START, 7, &SpriteImage, 0, 0, 0 );
		for( i=0;i<COUNT_OF_MAN;i++ )
		{
			sprite_move( &man[i] );
			AnimetionTrans( ANIME_CMD_SET_SIZE, 7, &SpriteImage, 0, 0, id[man[i].id_set + man[i].dir] );
			AnimetionTrans( ANIME_CMD_SET_IMAGE, 7, &SpriteImage, 0, 0, id[man[i].id_set + man[i].dir] );
			AnimetionTrans( ANIME_CMD_POSITION, 7, &SpriteImage, man[i].x , man[i].y, id[man[i].id_set + man[i].dir] );
		}

		AnimetionTrans( ANIME_CMD_END, 7, &SpriteImage, 0, 0, 0 );
//-------------------------
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_DISPLAY) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_SWAP) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteWord(REG_CMD_WRITE, cmdOffset);

		do
		{
			cmdBufferRd = HostMemReadWord(REG_CMD_READ);
			cmdBufferWr = HostMemReadWord(REG_CMD_WRITE);
		}while (cmdBufferWr != cmdBufferRd);
		cmdOffset = cmdBufferWr;

	}while(1);







#endif


#if CHAPTER_10A

	int x,y;
	int pos_x,pos_y,view_x,view_y;
	char char_num;
	int moving_state = 0;

	InflateLoad( &demo_mapchip[0], RAM_G+0x00000000, (SIZE_OF_DEMO_MAPCHIP+3)/4*4 );
//	JpegLoad( 1, &gear2_jpg_480_272[0], RAM_G+0x00000000, SIZE_OF_GEAR );

	pos_x = pos_y = 31;



	do
	{
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_DLSTART) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR_RGB | BLUE) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset, VERTEX_FORMAT(0) );
		cmdOffset = incCMDOffset(cmdOffset, 4);


//15,9


	view_x = pos_x - (GRID_X/2);
	view_y = pos_y - (GRID_Y/2);

	if( view_x <= 0 )
	{
		view_x = 0;
		pos_x = view_x + (GRID_X/2);
	}
	if( view_y <= 0 )
	{
		view_y = 0;
		pos_y = view_y + (GRID_Y/2);
	}

	for( y=0;y<GRID_Y;y++ )
	{
		for( x=0; x<GRID_X; x++ )
		{
			char_num = FieldMap[(view_y + y) * 64 + (view_x + x)];
			map[y][x] = char_num;
		}
	}

//-------------------------
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_HANDLE(7) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_LAYOUT(RGB565, IMAGE_SIZE_X * COLOR_DPTH, IMAGE_SIZE_Y) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SIZE(NEAREST, 0, 0, CHARCTOR_SIZE_X, CHARCTOR_SIZE_Y) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
//-------------------------

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BEGIN_BITMAPS );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		for( y=0;y<GRID_Y;y++ )
		{
			for( x=0; x<GRID_X; x++ )
			{
				char_num = map[y][x];
				HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SOURCE( RAM_G + offset_list[char_num] ) );
				cmdOffset = incCMDOffset(cmdOffset, 4);

				HostMemWriteDoubleWord( RAM_CMD + cmdOffset,VERTEX2F( x * CHARCTOR_SIZE_X ,-16+y * CHARCTOR_SIZE_Y ) );
				cmdOffset = incCMDOffset(cmdOffset, 4);
			}
		}
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,DL_END );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_DISPLAY) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_SWAP) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteWord(REG_CMD_WRITE, cmdOffset);

		do
		{
			cmdBufferRd = HostMemReadWord(REG_CMD_READ);
			cmdBufferWr = HostMemReadWord(REG_CMD_WRITE);
		}while (cmdBufferWr != cmdBufferRd);
		cmdOffset = cmdBufferWr;


		switch( moving_state )
		{
			case 0:
				pos_x = pos_x + 1;
				if( pos_x + (GRID_X/2) > 63 )
				{
					pos_x = 63-(GRID_X/2);
					moving_state++;
				}
				break;
			case 1:
				pos_y = pos_y + 1;
				if( pos_y + (GRID_Y/2) > 63 )
				{
					pos_y = 63-(GRID_Y/2);
					moving_state++;
				}
				break;
			case 2:
				pos_x = pos_x - 1;
				if( pos_x - (GRID_X/2) < 0 )
				{
					pos_x = 0+(GRID_X/2);
					moving_state++;
				}
				break;
			case 3:
				pos_y = pos_y - 1;
				if( pos_y - (GRID_Y/2) < 0 )
				{
					pos_y = 0+(GRID_Y/2);
					moving_state =0;
				}
				break;
			default:
				moving_state =0;
		}

	}while(1);


#endif


#if CHAPTER_8B
	signed short move_x,move_y;
	unsigned long offset = 0;
	float f_sin,f_cos,rad;
	float f_deg;

	JpegLoad( 1, &gear2_jpg_480_272[0], RAM_G+0x00000000, SIZE_OF_GEAR );

	do
	{
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_DLSTART) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR_RGB | BLUE) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset, VERTEX_FORMAT(0) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		f_deg += 5;
		rad = f_deg * 3.14159265359 / 180;
		
		f_sin = sin(rad);
		f_cos = cos(rad);

		move_x = f_sin * 120 + (240-48);
		move_y = f_cos * 80 + (136-48);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BEGIN_BITMAPS );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SOURCE( RAM_G + (move_y)*(480*2)+(move_x*2) ) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_LAYOUT(RGB565, 480*2, 272) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,BITMAP_SIZE(NEAREST, 0, 0, 96, 96) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,VERTEX2F( move_x-8 ,move_y-8 ) );
		cmdOffset = incCMDOffset(cmdOffset, 4);

		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,DL_END );
		cmdOffset = incCMDOffset(cmdOffset, 4);


		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(DL_DISPLAY) );
		cmdOffset = incCMDOffset(cmdOffset, 4);
		HostMemWriteDoubleWord( RAM_CMD + cmdOffset,(CMD_SWAP) );
		cmdOffset = incCMDOffset(cmdOffset, 4);


		HostMemWriteWord(REG_CMD_WRITE, cmdOffset);

		do
		{
			cmdBufferRd = HostMemReadWord(REG_CMD_READ);
			cmdBufferWr = HostMemReadWord(REG_CMD_WRITE);
		}while (cmdBufferWr != cmdBufferRd);
		cmdOffset = cmdBufferWr;
	}while(1);

#endif



}
