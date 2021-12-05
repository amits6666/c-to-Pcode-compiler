
/*  ###############################################################
    ##
    ##     C Tree Builder
    ##
    ##     File:         nmetab.h
    ##
    ##     Programmer:   Shawn Flisakowski
    ##     Date:         Jan 11, 1995
    ##
    ##
    ###############################################################  */

#ifndef     NMETAB_H
#define     NMETAB_H

#include "config.h"

BEGIN_HEADER

#define MAX_HASH_BCKTS	511

/*  ###############################################################  */

typedef struct string_str {
    unsigned int   hash;
    char          *str;
} str_t;

/*  ###############################################################  */

typedef struct hi {

    str_t      sym;
    struct hi *next;

} HashItem;

#define HASH_ITEM_SZE	(sizeof(HashItem))

/*  ###############################################################  */

extern HashItem  *NmeTab[MAX_HASH_BCKTS];

/*  ###############################################################  */

void   init_nmetab ARGS((void));
void   free_nmetab ARGS((void));
int    nme_equal   ARGS(( str_t *This, str_t *that ));
str_t *nmelook     ARGS(( char *sym, int len ));
int    nmehash     ARGS(( str_t *sym ));
void   nmeshow     ARGS((void));
char  *nmestr      ARGS(( str_t *sym ));

/*  ###############################################################  */

END_HEADER

#endif    /* NMETAB_H */
