/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :cc_data_types.h 
*
*  Description :Data Type declarations
*
*  Author      : Akshat K
***************************************************************************/

# ifndef _CC_DATA_TYPES_H_
# define _CC_DATA_TYPES_H_


# include "cc_config.h"

/* Typdefs for basic data types*/
typedef char INT8;
typedef unsigned char UINT8;

typedef char CHAR;
typedef unsigned char UCHAR;

typedef short INT16;
typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;


/* Typedefs for custom data types*/


/* Structure to store specified options in command
 * line .
 */
typedef struct
{
    UCHAR l_flag;
    UCHAR a_flag;
    UCHAR h_flag;
    UCHAR i_flag;
    UCHAR s_flag;
    UCHAR d_flag;
    UCHAR r_flag;
    UCHAR c_flag;
    UCHAR S_flag;
    UCHAR R_flag;
} OPTION_FLAGS;

/* Structure to store file match entries */
typedef struct file_list
{
    struct file_list *file_name_list;
    UCHAR file_name[MAX_FILE_PATH_SIZE];
} FILE_NAME_LIST;

/* Structure to store dir match entries */
typedef struct dir_list
{
    struct dir_list *dir_name_list;
    UCHAR dir_name[MAX_FILE_PATH_SIZE];
} DIR_NAME_LIST;

# define TRUE  1
# define FALSE 0
    
# endif /*_CC_DATA_TYPES_H_*/
