/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :cc_platform_abstraction.h 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/

# ifndef _CC_PLATFORM_ABSTRACTION_H_
# define _CC_PLATFORM_ABSTRACTION_H_

/* Default platform */
# ifndef PLATFORM_LINUX
# define PLATFORM_LINUX
# endif

/* Other platforms */
# ifdef PLATFORM_DOS
# undef PLATFORM_LINUX
# endif


/* Abstractions layer */

/******* Linux platform ********/
# ifdef PLATFORM_LINUX

/* Replacements for abstract routines/macros*/
# define EXPAND_EXPRESSIONS linux_expand_expressions
# define FNMATCH            fnmatch
# define COLOR_PRINT        linux_color_print
# define STRIP_PATH         linux_strip_path
# define LS_FILE_DISPLAY    ls_file_display
# define LS_DIR_DISPLAY     ls_dir_display

/* Prototypes for linux routines */
# include "cc_data_types.h"
# include <fnmatch.h>

void linux_expand_expressions(INT32 , CHAR **, FILE_NAME_LIST **, DIR_NAME_LIST **);
void linux_color_print(UINT32 color_code,const char *msgfmt, ... );
void linux_strip_path(UCHAR **filename, UCHAR *pathname);
void ls_file_display(UCHAR *filename, OPTION_FLAGS options_flags);
void ls_dir_display(DIR_NAME_LIST *dir_node, OPTION_FLAGS options_flags);

# endif
/******************************/







/******* Dos platform ********/
# ifdef PLATFORM_DOS

/* Replacements for abstract routines/macros*/
# define EXPAND_EXPRESSIONS (void)
# define FNMATCH            (void)

/* Prototypes for dos routines*/

# endif
/******************************/




# endif /*_CC_PLATFORM_ABSTRACTION_H_*/
