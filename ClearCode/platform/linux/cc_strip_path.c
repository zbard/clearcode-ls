/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Pvt. Ltd. All rights reserved.
*
*  File Name   :  cc_strip_path.c
*
*  Description :  
*
*  Author      : Akshat K
***************************************************************************/

#include "cc_data_types.h"
#include "xdebug_header.h"

void linux_strip_path(UCHAR **filename, UCHAR *pathname)
{
    INT32 i=0;
    *filename = pathname;
    
    debug(LOG_LEVEL,"Initally name of file %s", *filename); 
    for(i=0;pathname[i]!=0;i++)
    {
        if(pathname[i]=='/' && pathname[i+1]!=0)
            {
                *filename = &(pathname[i+1]);
                debug(LOG_LEVEL,"Encountered / :: now  %s", *filename); 
            }
    }
}
