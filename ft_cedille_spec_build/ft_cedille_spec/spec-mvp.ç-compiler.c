#include <fcntl.h>					
#include <stdio.h>											
#include <fcntl.h>											
#include <sys/mman.h>										
#include <unistd.h>											
#include <stdarg.h>											
#include <string.h>											
#include <sys/stat.h>										
#include <stdlib.h>											
#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"

 int m_state_test = 0;

 int f(int x)
{
	return (x);
}

 


 															
#undef cat													
#define cat(...) cats(__VA_ARGS__, 0)						
															
static char *cats(char *s, ...)								
{															
	char	*o;												
	int		i;												
	va_list	ap;												
															
	va_start(ap, s);										
	o = malloc(8096);										
	*o = 0;													
	while (s)												
	{														
		strcat(o, s);										
		s = va_arg(ap, char *);								
	}														
	va_end(ap);												
	return (o);												
															
}															
															
static void mkpath(const char *dir)							
{															
    char tmp[256];											
    char *p = NULL;											
    size_t len;												
															
    snprintf(tmp, sizeof(tmp),"%s",dir);					
    len = strlen(tmp);										
    if (tmp[len - 1] == '/')								
        tmp[len - 1] = 0;									
    p = tmp + 1;											
	while(*p)												
	{														
        if (*p == '/')										
		{													
            *p = 0;											
            mkdir(tmp, S_IRWXU);							
            *p = '/';										
        }													
		p += 1;												
	}														
}															
char *macro_0(int i, int x, char *s,char *__end){

	return (cat("!! "));

}

char *macro_1(int i, int x, char *s,char *__end){

	m_state_test += 1;
	return(cat("Good night !:)"));

}

															
															
int main(int ac, char **av)									
{															
	int		out_fd;											
	int		fd;												
	char	*s;												
	int		i;												
	int		x;												
	char	*o;												
	char	buffer[8096];									
	char	*r;												
	int		success;										
															
	if (ac < 3)												
	{														
		printf("Usage: ./%s <source.ç> <dest.c>\n", av[0]);
		return (1);											
	}														
	mkpath(av[2]);											
	out_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("out_file=%s fd=%i\n", av[2], out_fd);		
	if (out_fd < 0)											
	{														
		printf("Error - unable to open output file '%s'\n", av[2]);
	}														
	fd = open(av[1], O_RDONLY);								
	printf("source_file=%s fd=%i\n", av[1], fd);		
	if (fd < 0)												
	{														
		printf("Error - unable to open source file '%s'\n", av[1]);
		return (1);											
	}														
	i = lseek(fd, 0, SEEK_END);								
	s = mmap(0, i, PROT_READ, MAP_PRIVATE, fd, 0);			
	i = 0;													
	while (s[i])											
	{														
		x = 0;												
		 success = 1;																
					char __end[1024];*__end = 0;
																		
					x = 0;																	
					while (success)															
					{																		
						if (!(s[i+x] == 0 ))															
						{																	
							success = 0;													
							break ;															
						}																	
						if (!( 0 ))															
						{																	
							break ;															
						}																	
						x += 1;																
					}																		
			if (success)									
	{															
		r = macro_0(i, x, s, __end);														
		goto success;																
	}
success = 1;																
																							
					x = 0;																	
					while (success)															
					{																		
						if (!(s[i + x] == "Hello"[x] 	))															
						{																	
							success = 0;													
							break ;															
						}																	
						if (!( 	x < 4	))															
						{																	
							break ;															
						}																	
						x += 1;																
					}																		
			if (success)									
	{															
		r = macro_1(i, x, s, __end);														
		goto success;																
	}
													
		goto failure;										
		success:											
			printf("success\n!");						
			i += x;											
			dprintf(out_fd, "%s", r);					
			goto end;										
		failure:											
			dprintf(out_fd, "%c", s[i]);					
		end:												
		i += 1;												
	}														
	return (0);												
}