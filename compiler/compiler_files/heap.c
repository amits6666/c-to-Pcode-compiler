/*  ###############################################################
    ##
    ##     File:         heap.c
    ##
    ##     Revision 0.0.0.0  1996/04/03  08:51:54  kurt
    ##     hunk array was not getting copied properly in HeapAlloc_Gen(),
    ##     resulting in segmentation violations during heap destruction.
    ##     -- Kurt Cockrum <kurt@grogatch.seaslug.org>
    ##
    ##     Programmer:   Shaun Flisakowski
    ##     Date:         Apr 27, 1994
    ##
    ##     Multi-Heap Manager
    ##
    ###############################################################  */


#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <assert.h>
#include    <errno.h>

#include    "utype.h"
#include    "heap.h"

/*  ###############################################################  */
Heap    *CreateHeap( uint chunk_size, uint chnk_hunk_ratio )
{
Heap    *heap;
uint     unit;

    if ((heap = (Heap *) malloc(HEAP_SZE)) == NULL)
        return((Heap *) NULL);

    unit  = max(chunk_size, MIN_SZE);
    if (unit % ALGN_SZE != 0)
        unit += ALGN_SZE - (unit % ALGN_SZE);
    heap->chnk_sze = unit;

    if (chnk_hunk_ratio)
        heap->ch_ratio = chnk_hunk_ratio; 
    else
        heap->ch_ratio = DEFLT_RATIO;
       
    heap->num_alloc = 0; 
    heap->num_free  = 0; 
    heap->num_hunks = 0; 

    heap->next_chunk = 0;
    heap->hunk_array_sze = MIN_HUNK_ARRY;
    heap->free_list = (void *) NULL;

    if ((heap->hunks = (void **) malloc(MIN_HUNK_ARRY * PNTR_SZE)) == NULL){
        free(heap);
        return((Heap *) NULL);
    }

    return(heap);
}

/*  ###############################################################  */
void    HeapInfo( Heap *heap, uint *allocd, uint *freed, uint *hunks )
{
    if (heap){

        if (allocd)
            *allocd = heap->num_alloc;

        if (freed)
            *freed = heap->num_free;

        if (hunks)
            *hunks = heap->num_hunks;

    } else {

        if (allocd)
            *allocd = 0;

        if (freed)
            *freed = 0;

        if (hunks)
            *hunks = 0;
    }
}

/*  ###############################################################  */
void    DestroyHeap( Heap *heap )
{
uint    j;

    if (heap) {

        for (j=0; j < heap->num_hunks; j++)
            free(heap->hunks[j]);

        free(heap->hunks);
        free(heap);
    }
}

/*  ###############################################################  */
void    FreeHeap( Heap *heap )
{
uint    j;

    if (heap){

        for (j=1; j < heap->num_hunks; j++)
            free(heap->hunks[j]);

        if (heap->num_hunks){
            heap->num_hunks = 1;
            heap->next_chunk = 0;
        }
    }
}

/*  ###############################################################  */
void    *HeapErr( int fail )
{
    if (fail) {
        fputs("Heap Manager: Out of Memory (exiting).\n", stderr);
        exit(1);
    }

    return((void *) NULL);
}

/*  ###############################################################  */
void    *HeapAlloc_Gen( Heap *heap, int fail )
{
uint     asze, chnk;
void   *avail, *pnt;

    if (!heap)
        return(HeapErr(fail));

    if ((avail = heap->free_list) != NULL) {
        memcpy( &(heap->free_list), avail, PNTR_SZE);
        (heap->num_alloc)++;
        return(avail);
    }

    if (heap->num_hunks) {
        chnk = (heap->next_chunk)++;

        if (chnk == heap->ch_ratio) {

            if (heap->num_hunks == heap->hunk_array_sze){

                    /* Double array size */
                asze = heap->hunk_array_sze * 2;
                if ((pnt = (void *) malloc(asze * PNTR_SZE)) == NULL)
                    return(HeapErr(fail));
           
                memcpy( pnt, (void *) heap->hunks,
                             (heap->hunk_array_sze * PNTR_SZE) ); 

                free(heap->hunks);
                heap->hunks = pnt;
                heap->hunk_array_sze = asze;
            }

            if ((heap->hunks[heap->num_hunks] =
                     (void *) malloc(heap->chnk_sze * heap->ch_ratio)) == NULL)
                return(HeapErr(fail));

            (heap->num_hunks)++;
            heap->next_chunk = 1;
            (heap->num_alloc)++;
            return(heap->hunks[(heap->num_hunks)-1]);

        } else {

            (heap->num_alloc)++;
            return((void *) ((char*) (heap->hunks[(heap->num_hunks)-1])
                     + (heap->chnk_sze * chnk))); 
        }

    } else {
        if ((heap->hunks[0] = (void *) malloc(heap->chnk_sze * heap->ch_ratio))
                == NULL)
            return(HeapErr(fail));

        heap->num_hunks = 1;
        heap->next_chunk = 1;
       (heap->num_alloc)++;
        return(heap->hunks[0]);
    }
}

/*  ###############################################################  */
void    *HeapAlloc2( Heap *heap )
{
    return(HeapAlloc_Gen(heap, 1));
}

/*  ###############################################################  */
void    *HeapAlloc( Heap *heap )
{
    return(HeapAlloc_Gen(heap, 0));
}

/*  ###############################################################  */
void    HeapFree( Heap *heap, void *chunk )
{
    if (heap && chunk){

        (heap->num_free)++;
        memcpy( chunk, &(heap->free_list), PNTR_SZE );
        heap->free_list = chunk;
    }
}

/*  ###############################################################  */
