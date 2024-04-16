/* More subroutines needed by GCC output code on some machines.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1989-2018 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#include "tconfig.h"
#include "tsystem.h"
#include "coretypes.h"
#include "tm.h"
#include "libgcc_tm.h"

#ifdef HAVE_GAS_HIDDEN
#define ATTRIBUTE_HIDDEN  __attribute__ ((__visibility__ ("hidden")))
#else
#define ATTRIBUTE_HIDDEN
#endif

/* Work out the largest "word" size that we can deal with on this target.  */
#if MIN_UNITS_PER_WORD > 4
# define LIBGCC2_MAX_UNITS_PER_WORD 8
#elif (MIN_UNITS_PER_WORD > 2 \
       || (MIN_UNITS_PER_WORD > 1 && __SIZEOF_LONG_LONG__ > 4))
# define LIBGCC2_MAX_UNITS_PER_WORD 4
#else
# define LIBGCC2_MAX_UNITS_PER_WORD MIN_UNITS_PER_WORD
#endif

/* Work out what word size we are using for this compilation.
   The value can be set on the command line.  */
#ifndef LIBGCC2_UNITS_PER_WORD
#define LIBGCC2_UNITS_PER_WORD LIBGCC2_MAX_UNITS_PER_WORD
#endif

#if LIBGCC2_UNITS_PER_WORD <= LIBGCC2_MAX_UNITS_PER_WORD

#include "libgcc2.h"

#ifdef DECLARE_LIBRARY_RENAMES
  DECLARE_LIBRARY_RENAMES
#endif

#define SItype bogus_type
#define USItype bogus_type
#define DItype bogus_type
#define UDItype bogus_type
#define SFtype bogus_type
#define DFtype bogus_type
#undef Wtype
#undef UWtype
#undef HWtype
#undef UHWtype
#undef DWtype
#undef UDWtype

#undef char
#undef short
#undef int
#undef long
#undef unsigned
#undef float
#undef double

#include "gbl-ctors.h"

/* Some systems use __main in a way incompatible with its use in gcc, in these
   cases use the macros NAME__MAIN to give a quoted symbol and SYMBOL__MAIN to
   give the same symbol without quotes for an alternative entry point.  You
   must define both, or neither.  */
#ifndef NAME__MAIN
#define NAME__MAIN "__main"
#define SYMBOL__MAIN __main
#endif

#if defined (__LIBGCC_INIT_SECTION_ASM_OP__) \
    || defined (__LIBGCC_INIT_ARRAY_SECTION_ASM_OP__)
#undef HAS_INIT_SECTION
#define HAS_INIT_SECTION
#endif

#if !defined (HAS_INIT_SECTION) || !defined (OBJECT_FORMAT_ELF)

/* Some ELF crosses use crtstuff.c to provide __CTOR_LIST__, but use this
   code to run constructors.  In that case, we need to handle EH here, too.
   But MINGW32 is special because it handles CRTSTUFF and EH on its own.  */

#ifdef __MINGW32__
#undef __LIBGCC_EH_FRAME_SECTION_NAME__
#endif

#ifdef __LIBGCC_EH_FRAME_SECTION_NAME__
#include "unwind-dw2-fde.h"
extern unsigned char __EH_FRAME_BEGIN__[];
#endif

/* Run all the global destructors on exit from the program.  */

void
__do_global_dtors (void)
{
#ifdef DO_GLOBAL_DTORS_BODY
  DO_GLOBAL_DTORS_BODY;
#else
  static func_ptr *p = __DTOR_LIST__ + 1;
  while (*p)
    {
      p++;
      (*(p-1)) ();
    }
#endif
#if defined (__LIBGCC_EH_FRAME_SECTION_NAME__) && !defined (HAS_INIT_SECTION)
  {
    static int completed = 0;
    if (! completed)
      {
	completed = 1;
	__deregister_frame_info (__EH_FRAME_BEGIN__);
      }
  }
#endif
}
#endif

#ifndef HAS_INIT_SECTION
/* Run all the global constructors on entry to the program.  */

void
__do_global_ctors (void)
{
#ifdef __LIBGCC_EH_FRAME_SECTION_NAME__
  {
    static struct object object;
    __register_frame_info (__EH_FRAME_BEGIN__, &object);
  }
#endif
  DO_GLOBAL_CTORS_BODY;
  atexit (__do_global_dtors);
}
#endif /* no HAS_INIT_SECTION */

#if !defined (HAS_INIT_SECTION) || defined (INVOKE__main)
/* Subroutine called automatically by `main'.
   Compiling a global function named `main'
   produces an automatic call to this function at the beginning.

   For many systems, this routine calls __do_global_ctors.
   For systems which support a .init section we use the .init section
   to run __do_global_ctors, so we need not do anything here.  */

extern long __tls_main[], __TLS_DATA__[];
extern char __TLS_DATA_SIZE__[];
extern void SYMBOL__MAIN (void);
void
SYMBOL__MAIN (void)
{
  /* Support recursive calls to `main': run initializers just once.  */
  static int initialized;
  if (! initialized)
    {
      initialized = 1;
      /* initialize main tls allocated in the bss section */
      long *src = __TLS_DATA__;
      long *src_end = (long*)(((char*)__TLS_DATA__) + (long)(__TLS_DATA_SIZE__));
      long *dst = __tls_main;
      while (src < src_end) *dst++ = *src++;
      __do_global_ctors ();
    }
}
#endif /* no HAS_INIT_SECTION or INVOKE__main */

#endif /* LIBGCC2_UNITS_PER_WORD <= MIN_UNITS_PER_WORD */

