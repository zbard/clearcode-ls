/**************************************************************************
*  Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
*
*  File Name   :cc_common.h 
*
*  Description :
*               
*
*  Author      : Akshat K
***************************************************************************/

# ifndef _CC_COMMON_H
# define _CC_COMMON_H

# include "cc_data_types.h"

UCHAR cc_parser_getflags(INT32 argc, CHAR **argv,OPTION_FLAGS* options_flags); 
void add_node_to_dir_list(DIR_NAME_LIST **ptr_to_first_node, UCHAR* dir_name, 
        UCHAR* path, UCHAR add_sorted_flag);
void add_node_to_file_list(FILE_NAME_LIST **ptr_to_first_node, UCHAR* file_name,
        UCHAR* path, UCHAR add_sorted_flag);
void flush_file_queue(FILE_NAME_LIST **ptr_to_first_node, 
        OPTION_FLAGS options_flags);
void flush_dir_queue(DIR_NAME_LIST **ptr_to_first_node, 
        OPTION_FLAGS options_flags);

# endif /*_CC_COMMON_H */
