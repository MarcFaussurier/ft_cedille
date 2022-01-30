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
		x = 0;												
	/*	if (0) {(void)0;}									
		else if (
	<s[i + x] == "HEllo"[x] ; x[i + x]>
		<name[x] = s[i + x] ; x[i + x] != ';'>
)
{macro_0()}
else if (
	<s[i + x] == "Hello"[x] 	; x >= 5>
		<name1[x] = c[i + x] 	; c[i + x] != '!'>
)
{macro_1()}
	*/												
		len += 1;											
	}														
	return (0);												
}