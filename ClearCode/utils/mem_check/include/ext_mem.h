/**************************************************************************
 *   Copyright (C) 2003. MindTree Consulting Ltd. All rights reserved.
 * 
 *   File Name   :  
 * 
 *   Description :  
 * 
 *   Author      : Akshat Kumar \ IN4395
 * ***************************************************************************/



# ifndef _EXT_MEM_H
# define _EXT_MEM_H


# ifdef MEM_CHECK

# define MEM_START    mem_init(10)
# define MEM_SHUT     mem_shutdown()
# define malloc(size) mem_malloc_wrapper((size),__FILE__,__LINE__,0)
# define free(ptr)    mem_free_wrapper((ptr),__FILE__,__LINE__,0)

void mem_shutdown(void);
void mem_free_wrapper(void* ptr,char * file,int  line,int fileid);
void* mem_malloc_wrapper(size_t size,  char* file,int line,int fileid);
void mem_init(unsigned long int val);

# else 

# define MEM_START    ;
# define MEM_SHUT     ;

# endif /*MEM_CHECK*/ 

# endif /*_EXT_MEM_H */
