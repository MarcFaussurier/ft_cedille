#include <fcntl.h>					
#include <stdio.h>											
#include <fcntl.h>											
#include <sys/mman.h>										
#include <unistd.h>											
#include <stdarg.h>											
#include <string.h>											
#include <stdlib.h>											
#import "ç"
#import "spec-mvp2.ç"

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
															
char *macro_0(int i, int x, char *s,char *name,char *__end){

	return (cat("Hello ", name));

}

char *macro_1(int i, int x, char *s,char *name1,char *__end){

	m_state_test += 1;
	return(cat("Hello ", name1));

}

															
															
int main(int ac, char **av)									
{															
	int		fd;												
	char	*s;												
	int		i;												
	int		x;												
															
	if (ac < 2)												
	{														
		printf("Usage: ./%s <source.ç>\n", av[0]);		
		return (1);											
	}														
	fd = open(av[1], O_RDONLY);								
	i = lseek(fd, 0, SEEK_END);								
	s = mmap(0, i, PROT_READ, MAP_PRIVATE, fd, 0);			
	i = 0;													
	while (s[i])											
	{														
		x = 0;												
		 																
					char name[1024];
*name = 0;
char __end[1024];*__end = 0;
																		
					x = 0;																	
					while (1)																
					{																		
						if (!(s[i + x] == "HEllo"[x] ))															
						{																	
							i -= x;															
							break ;															
						}																	
						if (!( s[i + x]))															
						{																	
							macro_0(i, x, s, name, __end);															
							goto success;													
						}																	
						i += 1;																
					}																		
																			
																							
					x = 0;																	
					while (1)																
					{																		
						if (!(name[x] = s[i + x] ))															
						{																	
							i -= x;															
							break ;															
						}																	
						if (!( s[i + x] != ';'))															
						{																	
							macro_0(i, x, s, name, __end);															
							goto success;													
						}																	
						i += 1;																
					}																		
			
																
					char name1[1024];
*name1 = 0;
																		
					x = 0;																	
					while (1)																
					{																		
						if (!(s[i + x] == "Hello"[x] 	))															
						{																	
							i -= x;															
							break ;															
						}																	
						if (!( x ))															
						{																	
							macro_1(i, x, s, name1, __end);															
							goto success;													
						}																	
						i += 1;																
					}																		
																			
																							
					x = 0;																	
					while (1)																
					{																		
						if (!(name1[x] = s[i + x] 	))															
						{																	
							i -= x;															
							break ;															
						}																	
						if (!( s[i + x] != '!'))															
						{																	
							macro_1(i, x, s, name1, __end);															
							goto success;													
						}																	
						i += 1;																
					}																		
			
													
		i += 1;												
	}														
	return (0);												
}