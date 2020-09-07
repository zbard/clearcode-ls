/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   : xdebug.c 
*
*  Description : Holds functions for debugging.
*
*  Author      : Akshat K
***************************************************************************/

# include <stdarg.h>
# include "xdebug_header.h"


int _debug_call( int msglev, const char *msgfmt, ... )
{
    va_list arg_list;
    /* Exit if msglev is lower than defined Debug Level */
    if(msglev < EFFECTIVE_LEVEL)
    {
        return 0; 
    }

    /* And if msglev has some special actions : eg : ASSERT 
     * pit it here */

    va_start(arg_list, msgfmt);
    /* OUTPUT redirects to FILE* where messages have to be logged */
    switch(msglev)
    {
        case LOG_LEVEL:   
            fprintf(OUTPUT," LOG : ");
            break;
        case WARNING_LEVEL:
            fprintf(OUTPUT," WARNING : ");
            break;
        case ERROR_LEVEL:
            fprintf(OUTPUT," ERROR : ");
            break;
    }        
    vfprintf(OUTPUT, msgfmt , arg_list);
    putc('\n', OUTPUT);

    /* Should be replaced by error message */
    return 1;
}
