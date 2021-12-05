
/*  ###############################################################
    ##
    ##     C Tree Builder
    ##
    ##     File:         globals.h
    ##
    ##     Programmer:   Shawn Flisakowski
    ##     Date:         Dec 16, 1994
    ##
    ##
    ###############################################################  */

#ifndef     GLOBALS_H
#define     GLOBALS_H

#include    <stdio.h>
#include    <string.h>

#include "config.h"

/*  ###############################################################  */

BEGIN_HEADER

#ifdef    DEFINE_GLOBALS

#define   EXT_DEF
#define   EXT_INIT(VarDef,Init)    VarDef = Init

#else

#define   EXT_DEF                  extern
#define   EXT_INIT(VarDef,Init)    extern VarDef

#endif

/*  ###############################################################  */

#define MAX_FILES	256

/*  ###############################################################  */

#include    "ctree.h"
#include    "heap.h"
#include    "treestk.h"

/*  ###############################################################  */

	/* Flags */
EXT_INIT(int all, 0);	    /* Check for all errors (set of flags) */
EXT_INIT(int align, 0);	    /* Check for alignment independance */
EXT_INIT(int bounds, 1);    /* Do array bounds checking */
EXT_INIT(int help, 0);    	/* Show ctree options */
EXT_INIT(int leak, 1);    	/* Watch for memory leaks */
EXT_INIT(int modify, 0);	/* Allow self-modifying code */
EXT_INIT(int relax, 0);    	/* Relax errors somewhat (set of flags) */
EXT_INIT(int prompt, 1);	/* Show a prompt (interactive) */
EXT_INIT(int warn, 1);    	/* Warnings for questionable things */
EXT_INIT(int version, 0);	/* Show version */
EXT_INIT(int verbose, 1);	/* Be very verbose */

EXT_INIT(char *inputf, NULL);  /* The input file to use */
EXT_INIT(char *output, NULL);  /* The output file */
EXT_INIT(char *dribble, NULL); /* A "dribble" file for the whole session */
EXT_INIT(char *emulate, NULL); /* A processor/compiler to emulate */

/*  ###############################################################  */

	/* A level of indirection for input/output */
EXT_DEF FILE *infp;
EXT_DEF FILE *outfp;
EXT_DEF FILE *dupfp;	/* For dribble output */

/*  ###############################################################  */


	/* To hold the files/directories requested at startup */
EXT_DEF char *file_list[MAX_FILES];

    /* The stack and top of the stack */
EXT_INIT(TreeStack *ParseStack, NULL);
EXT_INIT(Stk_Item *Parse_TOS, NULL);

    /* Parse trees for included files are put here */
EXT_INIT(TreeStack *DoneStack, NULL);

END_HEADER

/*  ###############################################################  */

#endif  /* GLOBALS_H */
