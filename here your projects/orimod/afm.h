
/*

   AFM v1.2 for GBA (Arm7t/GCC), Gamepark 32 (Arm920t/GCC)
   (w) 2001-2002 by Silpheed/Hitmen, Groepaz/Hitmen
   www.hitmen-console.org

 */

#ifndef _AFMGP32_H_
#define _AFMGP32_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
   install player/mixer

   you must call this function before calling any other of the
   players routines.

   mixfreq: always 44100 (or closest) atm
   presc:   iis-prescaler value (2 for default cpu speed, 8 for 99mhz)

   returns actual mixfreq used (always 44100 atm)

 */
unsigned long afm_install(unsigned long mixfreq,int presc);

/*
   init modfile + soundsystem

   modfile must be a pointer to a standard 4-Channel Protracker Module

 */
extern void afm_init(unsigned char* modfile);

/*
  start playing
*/
extern void afm_start(void);

/*
   shutdown the player+stop any sound

   after having called this routine, you must call afm_install before
   calling any other routines of the player.

 */
extern void afm_deinit(void);

/*
   now some global variables which you can observe for synchronisation
   or visualisation or whatever purposes
*/

/* the mixed sample stream */
extern signed short stream[];

/* position info */
extern unsigned char mod_order;     /* track pointer */
extern   signed char mod_row;       /* pattern pointer */
extern unsigned char mod_pattern;   /* curr. pattern nr. */

/* speed info */
extern unsigned long mod_speed;     /* ticks per row */
extern unsigned long mod_tick;      /* curr. tick */
extern unsigned long mod_bpm;       /* beats per minute */

/* channel info */
typedef struct {
	int            playing;
	int            mixpos;
	unsigned short note;
	signed short   freq;
	unsigned short porta_to;
	unsigned char  porta_speed;
	signed char    vol;
        signed char    realvol;
	unsigned char  smp;
	signed char    vib_pos;
	signed char    trem_pos;
	unsigned char  vib_speed;
	unsigned char  vib_depth;
	unsigned char  trem_speed;
	unsigned char  trem_depth;
	unsigned char  wavecontrol;
	unsigned short smp_offs;
} CHANNEL;
extern CHANNEL channels[4];

/* samples info */
typedef struct {
	signed char    *addr;
	unsigned int   length;
	unsigned int   loop_start;
	unsigned int   loop_len;
	unsigned char  finetune;
	unsigned char  volume;
} SAMPLE;
extern SAMPLE samples[31];

#ifdef __cplusplus
}
#endif

#endif /* _AFMGP32_H_ */
