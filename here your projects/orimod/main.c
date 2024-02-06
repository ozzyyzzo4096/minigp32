
/*

   AFM v1.2 for Gamepark 32 (Arm920t/GCC)
   (w) 2001-2002 by Silpheed/Hitmen, Groepaz/Hitmen
   www.hitmen-console.org

   Example Code for GCC...

   for more info look in afm.h

 */

/* afm header */
#include "afm.h"

/* modfile data */
extern unsigned long _binary_test_mod_start;

int main(void) {

    /* 44100,2 for default speed */
    /* 44100,8 for 99mhz */
    afm_install(44100,2);

    /* initialize module */
    afm_init((unsigned char*)&_binary_test_mod_start);

    /* start playing */
    afm_start();

    while(1) {
        /* forever */
    }

    /* deinstall player, stop playing any sound */
    afm_deinit();

    return(0);

}
