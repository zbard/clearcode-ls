/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :  
*
*  Description : Routine for printing in color on ansi compiant linux color 
*                desktops.
*
*  Author      : Akshat K
***************************************************************************/


# include <stdarg.h>
# include <stdio.h>

# include "cc_data_types.h"
# include "cc_color.h"

void linux_color_print(UINT32 color_code,const char *msgfmt, ... )
{
    
    va_list arg_list;
    va_start(arg_list, msgfmt);
    
    switch(color_code)
    {
        case GREEN:
            printf("\033[32m");
            break;
        case BLUE :
            printf("\033[34m");
            break;
        default   :
            printf("\033[0m");
            break;
    }
   
    vprintf(msgfmt, arg_list);
    printf("\033[0m");
    fflush(stdout);
}


