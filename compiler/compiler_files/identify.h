/*********************************************************************
/     Identify.h                                                     
/
/     Including this file will define HPUX, SUN, MIPS, or OTHER. 
/     (should probably contain VMS, SOLAR, and some others)
/
/ ********************************************************************/

#ifndef    IDENTIFY_H
#define    IDENTIFY_H

#include <sys/types.h>

#include "config.h"

BEGIN_HEADER

/* HPUX -  */

#ifdef    _HPUX_SOURCE
#    define    HPUX
#endif

/*********************************************************************/

/* SUN  */

#ifdef    sun
#    define    SUN
#endif

/*********************************************************************/

/* MIPS -  */

#ifdef    __MIPSEL
#    define    MIPS
#endif

/*********************************************************************/

/* LINUX -  */

#ifdef    __linux
#    define    LINUX
#endif

/*********************************************************************/
/* DJGPP -  */

#ifdef __dj_include_sys_types_h_
#    define    DJGPP
#endif

/*********************************************************************/

/* Catch all for others */

#if !defined(HPUX) && !defined(SUN) && !defined(MIPS)
#    if !defined(LINUX) && !defined(DJGPP)
#        define    OTHER
#    endif 
#endif 

/*********************************************************************/

END_HEADER

#endif     /* IDENTIFY_H */
