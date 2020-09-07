/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :xdebug_header.h 
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/
# ifndef __XDEBUG_HEADER_H_
# define __XDEBUG_HEADER_H_


# include <stdio.h>


/* Define Priority levels*/
# define LOG_LEVEL           0x0001
# define WARNING_LEVEL       0x0002
# define MEM_LEVEL           0x0003
# define ERROR_LEVEL         0x0004

/* Default priority level */
# define EFFECTIVE_LEVEL LOG_LEVEL

/* Select effective priority level */
# ifdef LOG
# undef EFFECTIVE_LEVEL
# define EFFECTIVE_LEVEL LOG_LEVEL
# endif

# ifdef WARNING
# undef EFFECTIVE_LEVEL
# define EFFECTIVE_LEVEL WARNING_LEVEL
# endif

/* Note macro to select memory checker and set log level */
# ifdef MEM_CHECK
# undef EFFECTIVE_LEVEL
# define EFFECTIVE_LEVEL MEM_LEVEL
# endif

# ifdef ERROR
# undef EFFECTIVE_LEVEL
# define EFFECTIVE_LEVEL ERROR_LEVEL
# endif

/* Define where to log output*/
# define OUTPUT stderr

/* Define DEBUG macro */
# ifdef DEBUG
# define debug                   _debug_call
# else
# define debug                   1?0:
# endif

int _debug_call( int msglev, const char *msgfmt, ... );

# endif /*__XDEBUG_HEADER_H_*/
