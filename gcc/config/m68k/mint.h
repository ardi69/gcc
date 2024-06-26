/* Definitions of target machine for GNU compiler.
   Atari ST TOS/MiNT.
   Copyright (C) 1994, 1995, 2007, 2008, 2009, 2010, 2011
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http:/www.gnu.org/licenses/>.  */

/* Here are four prefixes that are used by asm_fprintf to
   facilitate customization for alternate assembler syntaxes.
   Machines with no likelihood of an alternate syntax need not
   define these and need not use asm_fprintf.  */

/* The prefix for register names.  Note that REGISTER_NAMES
   is supposed to include this prefix. Also note that this is NOT an
   fprintf format string, it is a literal string */

#undef REGISTER_PREFIX
#define REGISTER_PREFIX "%"

/* The prefix for local (compiler generated) labels.
   These labels will not appear in the symbol table.  */

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."

/* The prefix to add to user-visible assembler symbols.  */

#undef USER_LABEL_PREFIX
#define USER_LABEL_PREFIX "_"

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "|"

#undef WCHAR_TYPE
#define WCHAR_TYPE "short unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE SHORT_TYPE_SIZE

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()		\
  do						\
    {						\
      builtin_define ("__MINT__");		\
      builtin_define_std ("atarist");		\
      builtin_assert ("machine=atari");		\
      builtin_assert ("system=mint");		\
    }						\
  while (0)

#undef TARGET_OBJFMT_CPP_BUILTINS
#define TARGET_OBJFMT_CPP_BUILTINS() do { builtin_define ("__ELF__"); } while (0)
/* The following defines are nonstandard
   and are kept only for compatibility
   with older versions of GCC for MiNT.  */

#define TOOL_INCLUDE_DIR_EXTRA_BOFORE TOOL_INCLUDE_DIR "/libcmini"
#define TOOL_INCLUDE_DIR_EXTRA_BOFORE_ENABLED (fuse_libcmini)
#undef CPP_SPEC
#define CPP_SPEC			\
  "%{mshort:%{!fno-use-libcmini: -fuse-libcmini}} "		\
  "%{m68000:-D__M68000__} "		\
  "%{mc68020:-D__M68020__} "		\
  "%{m68020:-D__M68020__} "		\
  "%{m68030:-D__M68020__} "		\
  "%{m68040:-D__M68020__} "		\
  "%{m68060:-D__M68020__} "		\
  "%{m68020-40:-D__M68020__} "		\
  "%{m68020-60:-D__M68020__} "		\
  "%{!m680*:%{!mc680*:-D__M68000__}} " \
  "%{mthreads:-D_REENTRANT} "

#define STARTFILE_SPEC	"%{mshared:%{pg|p|profile:%eprofiling of shared libraries is not supported;:crt0.slb.o%s};:%{pg|p|profile:gcrt0.o%s;:crt0.o%s}}"
#define LIB_SPEC	"%{mshort:%{fno-use-libcmini:-lc;:-lcmini};fuse-libcmini:-lcmini;:-lc} %{mthreads:-lpthread} "

/* Every structure or union's size must be a multiple of 2 bytes.  */
#define STRUCTURE_SIZE_BOUNDARY 16

/* The -g option generates stabs debug information.  */
#define DBX_DEBUGGING_INFO 1

/* This is the assembler directive to equate two values.  */
#undef SET_ASM_OP
#define SET_ASM_OP		"\t.set\t"

/* This is how we tell the assembler that a symbol is weak.  */
#undef ASM_WEAKEN_LABEL
#define ASM_WEAKEN_LABEL(FILE,NAME) \
  do { fputs ("\t.weak\t", FILE); assemble_name (FILE, NAME); \
       fputc ('\n', FILE); } while (0)

#undef ASM_PREFERRED_EH_DATA_FORMAT
#define ASM_PREFERRED_EH_DATA_FORMAT(CODE, GLOBAL)	DW_EH_PE_pcrel


/* Don't default to pcc-struct-return, because gcc is the only compiler, and
   we want to retain compatibility with older gcc versions.  */
#define DEFAULT_PCC_STRUCT_RETURN 0

/* The system headers are C++-aware.  */
#define NO_IMPLICIT_EXTERN_C

/* By default, the vtable entries are void pointers, the so the alignment
   is the same as pointer alignment.  The value of this macro specifies
   the alignment of the vtable entry in bits.  It should be defined only
   when special alignment is necessary.

   MiNT: The default value of 32 is too much and unsupported by a.out-mintprg.
*/
#define TARGET_VTABLE_ENTRY_ALIGN 16

/* If we have a definition of INCOMING_RETURN_ADDR_RTX, assume that
   the rest of the DWARF 2 frame unwind support is also provided.
   
   MiNT: DWARF 2 frame unwind is not supported by a.out-mint.
*/
#define DWARF2_UNWIND_INFO 1

/* All ELF targets can support DWARF-2.  */

#define DWARF2_DEBUGGING_INFO 1

/* The GNU tools operate better with dwarf2, and it is required by some
   psABI's.  Since we don't have any native tools to be compatible with,
   default to dwarf2.  */

#ifndef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG
#endif

/* All SVR4 targets use the ELF object file format.  */
#define OBJECT_FORMAT_ELF

/* Switch into a generic section.  */
#undef  TARGET_ASM_NAMED_SECTION
#define TARGET_ASM_NAMED_SECTION default_elf_asm_named_section
#undef  TARGET_ASM_SELECT_RTX_SECTION
#define TARGET_ASM_SELECT_RTX_SECTION default_elf_select_rtx_section
#undef	TARGET_ASM_SELECT_SECTION
#define TARGET_ASM_SELECT_SECTION default_elf_select_section

#define JUMP_TABLES_IN_TEXT_SECTION 1
#undef LINK_SPEC
#define LINK_SPEC "%{mshared:-m m68kslb -mbest-fit} -q %{mfastload}%{mno-fastload} %{maltram}%{mno-altram} %{mfastram}%{mno-mfastram} %{maltalloc}%{mno-maltalloc} %{mfastalloc}%{mno-mfastalloc} %{mbest-fit}%{mno-mbest-fit} %{msharable-text}%{mno-msharable-text} %{mshared-text}%{mno-mshared-text} %{mbasrel}%{mno-mbasrel}" \
                  "%{mprivate-memory:%{mglobal-memory|msuper-memory|mreadonly-memory|mreadable-memory:%e-m*-memory options are exclusive;:-mprivate-memory}}" \
                  "%{mglobal-memory:%{msuper-memory|mreadonly-memory|mreadable-memory:%e-m*-memory options are exclusive;:-mglobal-memory}}" \
                  "%{msuper-memory:%{mreadonly-memory|mreadable-memory:%e-m*-memory options are exclusive;:-msuper-memory}}" \
                  "%{mreadonly-memory} %{mreadable-memory}"

/* config/m68k.md has an explicit reference to the program counter,
   prefix this by the register prefix.  */

#define ASM_RETURN_CASE_JUMP				\
  do {							\
    if (TARGET_COLDFIRE)				\
      {							\
	if (ADDRESS_REG_P (operands[0]))		\
	  return "jmp %%pc@(2,%0:l)";			\
	else						\
	  return "ext%.l %0\n\tjmp %%pc@(2,%0:l)";	\
      }							\
    else						\
      return "jmp %%pc@(2,%0:w)";			\
  } while (0)

/* The ADDR_DIFF_VEC must exactly follow the previous instruction.  */

#undef ADDR_VEC_ALIGN
#define ADDR_VEC_ALIGN(ADDR_VEC) 0

/* If defined, a C expression whose value is a string containing the
   assembler operation to identify the following data as uninitialized global
   data.  */

#define BSS_SECTION_ASM_OP "\t.bss"

/* A C statement (sans semicolon) to output to the stdio stream
   FILE the assembler definition of uninitialized global DECL named
   NAME whose size is SIZE bytes and alignment is ALIGN bytes.
   Try to use asm_output_aligned_bss to implement this macro.  */

#define ASM_OUTPUT_ALIGNED_BSS(FILE, DECL, NAME, SIZE, ALIGN) \
  asm_output_aligned_bss (FILE, DECL, NAME, SIZE, ALIGN)

/* Support a read-only data section.  */
#define READONLY_DATA_SECTION_ASM_OP	"\t.section\t.rodata"


/* Disable -fpic and -fPIC since bsr.l _label@PLTPC
   is unsupported by the assembler.  */

#undef  SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS					\
do {									\
  if (flag_pic && !TARGET_PCREL)					\
      error ("-f%s is not supported on this target",			\
	       (flag_pic > 1) ? "PIC" : "pic");				\
} while (0)

/* Workaround for GCC bug #35067 about multiple thunks.  */

#undef MAKE_DECL_ONE_ONLY
#define MAKE_DECL_ONE_ONLY(DECL) (DECL_WEAK (DECL) = 1)

/* Avoid requiring -static with -fmudflap like in config/bfin/uclinux.h */
#define MFWRAP_SPEC " %{fmudflap|fmudflapth: \
 --wrap=malloc --wrap=free --wrap=calloc --wrap=realloc\
 --wrap=mmap --wrap=munmap --wrap=alloca\
 %{fmudflapth: --wrap=pthread_create\
}} %{fmudflap|fmudflapth: --wrap=main}"


/* Older implementations of mcount expect the address of a counter
   variable to be loaded into some register. The name of this variable is
   prefix LP followed by a number.
   mintlib's mcount dont use or need that  */
#undef NO_PROFILE_COUNTERS
#define NO_PROFILE_COUNTERS 1
#undef M68K_FUNCTION_PROFILER
#define M68K_FUNCTION_PROFILER(FILE, LABELNO)  \
  asm_fprintf (FILE, "\tjsr mcount\n")

/* This is the library routine that is used to transfer control from the
   trampoline to the actual nested function.  It is defined for backward
   compatibility, for linking with object code that used the old trampoline
   definition.*/
/* MiNT don't needs backward compatibility */
#undef TRANSFER_FROM_TRAMPOLINE


#undef FINALIZE_TRAMPOLINE
#define FINALIZE_TRAMPOLINE(TRAMP)							\
	emit_library_call (init_one_libfunc("__clear_cache"),	\
			LCT_NORMAL, VOIDmode, TRAMP, Pmode,				\
			plus_constant (Pmode, TRAMP, TRAMPOLINE_SIZE), Pmode);

/* Clear the instruction cache from `beg' to `end'.  This makes an
   Gemdos call SSystem(S_FLUSHCACHE, ... ).  */

#define CLEAR_INSN_CACHE(BEG, END)									\
{																	\
	extern long __has_no_ssystem;									\
	if (__has_no_ssystem) return;									\
	register long _BEG __asm__("%a0") = (long) BEG;					\
	register long _END __asm__("%a1") = (long) END;					\
	__asm__ volatile												\
  	(																\
 		"subl	%0, %1\n\t"											\
 		"movl	%1,sp@-\n\t"										\
  		"movl	%0,sp@-\n\t"										\
  		"movl	#(340<<16)+16,sp@-\n\t" /* SSystem(S_FLUSHCACHE, ... ) */	\
  		"trap	#1\n\t"					/* Gemdos call */			\
  		"lea	sp@(12),sp"											\
  	: "+a"(_BEG), "+a"((_END))										\
  	:  /* inputs  */	\
  	:  "d0", "d1", "d2", "a2"    /* clobbered regs */			\
  	);																\
}

/* ColdFire and fido strongly prefer a 32-bit aligned stack.  */
/* BUG with -mshort see GCC Bugzilla BUG 88160
   --> temporary set PREFERRED_STACK_BOUNDARY to 16 for coldfire with mshort */
#undef PREFERRED_STACK_BOUNDARY
#define PREFERRED_STACK_BOUNDARY \
  (((TARGET_COLDFIRE && !TARGET_SHORT) || TARGET_FIDOA) ? 32 : 16)




/* the defines above should be in mint-stdint.h */


#define SIG_ATOMIC_TYPE (INT_TYPE_SIZE == 16 ? "long int" : "int")

#define INT8_TYPE "signed char"
#define INT16_TYPE (INT_TYPE_SIZE == 16 ? "int" : "short int")
#define INT32_TYPE (INT_TYPE_SIZE == 16 ? "long int" : "int")
#define INT64_TYPE "long long int"
#define UINT8_TYPE "unsigned char"
#define UINT16_TYPE (INT_TYPE_SIZE == 16 ? "unsigned int" : "short unsigned int")
#define UINT32_TYPE (INT_TYPE_SIZE == 16 ? "long unsigned int" : "unsigned int")
#define UINT64_TYPE "long long unsigned int"

#define INT_LEAST8_TYPE INT8_TYPE
#define INT_LEAST16_TYPE INT16_TYPE
#define INT_LEAST32_TYPE INT32_TYPE
#define INT_LEAST64_TYPE INT64_TYPE
#define UINT_LEAST8_TYPE UINT8_TYPE
#define UINT_LEAST16_TYPE UINT16_TYPE
#define UINT_LEAST32_TYPE UINT32_TYPE
#define UINT_LEAST64_TYPE UINT64_TYPE

#define INT_FAST8_TYPE INT_LEAST8_TYPE
#define INT_FAST16_TYPE "int"
#define INT_FAST32_TYPE INT_LEAST32_TYPE
#define INT_FAST64_TYPE INT_LEAST64_TYPE
#define UINT_FAST8_TYPE UINT_LEAST8_TYPE
#define UINT_FAST16_TYPE "unsigned int"
#define UINT_FAST32_TYPE UINT_LEAST32_TYPE
#define UINT_FAST64_TYPE UINT_LEAST64_TYPE

#define INTPTR_TYPE PTRDIFF_TYPE
#ifndef UINTPTR_TYPE
#define UINTPTR_TYPE SIZE_TYPE
#endif

