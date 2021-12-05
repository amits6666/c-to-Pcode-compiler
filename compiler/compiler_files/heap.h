/*  ###############################################################
    ##
    ##     File:         heap.h
    ##
    ##     Programmer:   Shawn Flisakowski
    ##     Date:         Apr 27, 1994
    ## 
    ##     Multi-Heap Manager
    ##
    ###############################################################  */

#ifndef    HEAP_H
#define    HEAP_H

#include "config.h"
#include "utype.h"

BEGIN_HEADER

/*  ###############################################################  */

#define    MIN_HUNK_ARRY        8
#define    DEFLT_RATIO        256

/*  ###############################################################  */

#define    min(X, Y)        ( ((X) < (Y)) ? (X) : (Y) )
#define    max(X, Y)        ( ((X) > (Y)) ? (X) : (Y) )

/*  ###############################################################  */

 /*  The following macros are machine-dependent.
     On many machines, a pointer is 4 bytes long,
     and 4-byte alignment suffices for most things.
     However, this is NOT true on an Alpha, where
     pointers are 8 bytes, and 8 byte alignment is
     the useful minimum.  Now that there are 64-bit
     MIPS, PowerPC, and SPARC systems as well as
     Alphas, we can no longer tolerate all-the-world's-a-VAX.
     We DO assume that all pointers are the same size;
     which is KNOWN to be false in several C systems.
    8 byte alignment will do no harm on 32-bit machines.
*/
#define PNTR_SZE (sizeof (void *))
#define ALGN_SZE (sizeof (double))
#define MIN_SZE  max(PNTR_SZE,ALGN_SZE)

/*  ###############################################################  */

typedef    struct  hp_strt {

    uint    chnk_sze;
    uint    ch_ratio;

    uint    num_alloc;
    uint    num_free;
    uint    num_hunks;

    uint    hunk_array_sze;
    uint    next_chunk;

    void   *free_list;
    void  **hunks;

} Heap;

#define    HEAP_SZE    sizeof(Heap)

/*  ###############################################################  */

Heap *CreateHeap    ARGS(( uint chunk_size, uint chnk_hunk_ratio ));

void  HeapInfo      ARGS(( Heap*, uint *allocd, uint *freed, uint *hunks ));

void  DestroyHeap   ARGS(( Heap* ));
void  FreeHeap      ARGS(( Heap* ));
void *HeapErr       ARGS(( int fail ));

void *HeapAlloc_Gen ARGS(( Heap*, int fail ));
void *HeapAlloc2    ARGS(( Heap* ));
void *HeapAlloc     ARGS(( Heap* ));

void  HeapFree      ARGS(( Heap*, void *chunk ));

END_HEADER

/*  ###############################################################  */

#endif    /* HEAP_H  */
