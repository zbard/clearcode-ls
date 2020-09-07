/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : xunit_header.h
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/

# ifndef _XUNIT_HEADER_H_
# define _XUNIT_HEADER_H_

# define xu_assert(message, test) do { tests_run++; \
                if (!(test)) return message; } while (0)
# define xu_run_test(test) do { char *message = test();  \
                if (message) return message; } while (0)

extern int tests_run;
void xunit_display_init(void);
void xunit_display_result(char *descr, char * str);
void xunit_display_end(void);


# endif /*_XUNIT_HEADER_H_*/
