/* Pragma related interfaces.
   Copyright (C) 1995, 1998, 1999, 2000 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef _C_PRAGMA_H
#define _C_PRAGMA_H

#ifdef HANDLE_SYSV_PRAGMA
/* Support #pragma weak iff ASM_WEAKEN_LABEL and ASM_OUTPUT_DEF are
   defined.  */
#if defined (ASM_WEAKEN_LABEL) && defined (ASM_OUTPUT_DEF)
#define HANDLE_PRAGMA_WEAK SUPPORTS_WEAK
#endif

/* We always support #pragma pack for SYSV pragmas.  */
#ifndef HANDLE_PRAGMA_PACK
#define HANDLE_PRAGMA_PACK 1
#endif
#endif /* HANDLE_SYSV_PRAGMA */


#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
/* If we are supporting #pragma pack(push... then we automatically
   support #pragma pack(<n>)  */
#define HANDLE_PRAGMA_PACK 1
#endif /* HANDLE_PRAGMA_PACK_PUSH_POP */


#ifdef HANDLE_PRAGMA_WEAK
/* This structure contains any weak symbol declarations waiting to be emitted.  */
struct weak_syms
{
  struct weak_syms * next;
  const char * name;
  const char * value;
};

/* Declared in varasm.c */
extern struct weak_syms * weak_decls;

extern int add_weak PARAMS ((const char *, const char *));
#endif /* HANDLE_PRAGMA_WEAK */


/* Define HANDLE_GENERIC_PRAGMAS if any kind of front-end pragma
   parsing is to be done.  The code in GCC's generic C source files
   will only look for the definition of this constant.  They will
   ignore definitions of HANDLE_PRAGMA_PACK and so on.  */
#if defined HANDLE_PRAGMA_PACK || defined HANDLE_PRAGMA_WEAK \
    || defined REGISTER_TARGET_PRAGMAS
#define HANDLE_GENERIC_PRAGMAS
#endif

#ifdef HANDLE_GENERIC_PRAGMAS
extern void init_pragma PARAMS ((void));

# if !USE_CPPLIB
extern void dispatch_pragma PARAMS ((void));
# endif

#else
# define init_pragma()
#endif

/* Duplicate prototypes for the register_pragma stuff and the typedef for
   cpp_reader, to avoid dragging cpplib.h in almost everywhere... */
#ifndef __GCC_CPPLIB__
typedef struct cpp_reader cpp_reader;

extern void cpp_register_pragma PARAMS ((cpp_reader *,
					 const char *, const char *,
					 void (*) PARAMS ((cpp_reader *))));
extern void cpp_register_pragma_space PARAMS ((cpp_reader *, const char *));
#endif

#endif /* _C_PRAGMA_H */
