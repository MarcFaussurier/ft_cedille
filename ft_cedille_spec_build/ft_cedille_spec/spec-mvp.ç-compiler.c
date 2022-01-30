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
															
char *macro_0(char *s,char *name){
	return (cat("Hello ", name));
}
char *macro_1(char *s,char *name1){
	return(cat("Hello ", name1));
}
															
															
int main(int ac, char **av)									
{															
	int		fd;												
	int		len;											
	char	*data;											
	int		i;												
	int		x;												
															
	if (ac < 2)												
	{														
		printf("Usage: ./%s <source.ç>\n", av[0]);		
		return (1);											
	}														
	fd = open(av[1], O_RDONLY);								
	len = lseek(fd, 0, SEEK_END);							
	data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);		
	len = 0;												
	while (data[len])										
	{														
		i = len;											
		/* 																
					// ifndef names, define names as big enough charis						
																							
					x = 0;																	
					while (1)																
					{																		
						if (!s)															
							break ;															
						if (!)															
							callback(names);												
							goto success ;													
						i += 1;																
					}																		
																			
					// ifndef names, define names as big enough charis						
																							
					x = 0;																	
					while (1)																
					{																		
						if (!name)															
							break ;															
						if (!)															
							callback(names);												
							goto success ;													
						i += 1;																
					}																		
			)
{macro_0()}
																
					// ifndef names, define names as big enough charis						
																							
					x = 0;																	
					while (1)																
					{																		
						if (!s)															
							break ;															
						if (!)															
							callback(names);												
							goto success ;													
						i += 1;																
					}																		
																			
					// ifndef names, define names as big enough charis						
																							
					x = 0;																	
					while (1)																
					{																		
						if (!name1)															
							break ;															
						if (!)															
							callback(names);												
							goto success ;													
						i += 1;																
					}																		
			)
{macro_1()}
	*/											
		len += 1;											
	}														
	return (0);												
}