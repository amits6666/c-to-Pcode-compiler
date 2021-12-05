#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <assert.h>

#include    "globals.h"
#include    "lexer.h"
#include    "nmetab.h"

HashItem  *NmeTab[MAX_HASH_BCKTS];

/*  ###############################################################  */
int  nmehash( str_t *sym )
{
    if (sym)
      return sym->hash;
    else
      return 0;
}

/*  ###############################################################  */
char *nmestr( str_t *sym )
{
    if (sym)
      return sym->str;
    else
      return NULL;
}

/*  ###############################################################  */
unsigned int calc_hash( char *str )
{
  unsigned int hsh = 0, c;

  while(*str)
    {
    c = *str++;
    hsh = (hsh << 1) ^ (hsh >> 20) ^ c;
    }

  return(hsh);
}

/*  ###############################################################  */
void init_nmetab(void)
{
  int j;

  for (j=0; j < MAX_HASH_BCKTS; j++)
      NmeTab[j] = (HashItem *) NULL;
}

/*  ###############################################################  */
void  free_nmetab(void)
{
int j;
HashItem  *hptr, *hfree;

    for (j=0; j < MAX_HASH_BCKTS; j++){

        hfree = (HashItem *) NULL;

        for (hptr=NmeTab[j]; hptr; hptr=hptr->next){
            if (hptr->sym.str)
                free(hptr->sym.str);
            if (hfree)
                free(hfree);
            hfree = hptr;
        }

        if (hfree)
            free(hfree);
    }
}

/*  ###############################################################  */
int    nme_equal( str_t *This, str_t *that )
{
    if (!This || !that)
      return 0;

    return (This->str == that->str);
}

/*  ###############################################################  */
str_t *nmelook( char *sym, int len )
{
unsigned int  hsh;
int bckt;
HashItem *hptr;

    hsh  = calc_hash(sym);
    bckt = hsh % MAX_HASH_BCKTS;

    for (hptr=NmeTab[bckt]; hptr; hptr=hptr->next)
      {

      if ((hptr->sym.hash == hsh) && (strcmp(sym,hptr->sym.str) == 0))
        return(&(hptr->sym));
      } 

    if ((hptr = (HashItem *) malloc( HASH_ITEM_SZE )) == NULL)
      return((str_t *) NULL);

    if (!len)
      len = strlen(sym);

    if ((hptr->sym.str = malloc(len+1)) == NULL)
      {
      free(hptr);
      return((str_t *) NULL);
      }

    hptr->sym.hash = hsh;
    strncpy(hptr->sym.str, sym, len);

    hptr->next = NmeTab[bckt];
    NmeTab[bckt] = hptr;

    return(&(hptr->sym));
}

/*  ###############################################################  */
void nmeshow(void)
{
int  j;
HashItem *hptr;

    fprintf(stdout,"        Name Table\n");
    fprintf(stdout,"       ------------\n\n");

    for (j=0; j < MAX_HASH_BCKTS; j++){
    fprintf(stdout,"Examining bucket: %d\n", j);
        for (hptr=NmeTab[j]; hptr; hptr=hptr->next){
            fprintf(stdout,"Name: %s\n",hptr->sym.str);
        } 
    } 

    fputs("\n\n",stdout);
}

/*  ###############################################################  */
