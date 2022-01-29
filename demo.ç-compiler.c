#include <fcntl.h>					
#include <stdio.h>											
#include "get_next_linev2/get_next_line.h" 				
#import "test.c"




 															
															
char *macro_0(char *testt42){return ( cat ( " Hello   " , test42 ) );}
char *macro_1(char *s,char *name1){return ( cat ( " Hello   " , name1 ) );}
															
															
int main(int ac, char **av)									
{															
	if (ac < 2)												
	{														
		printf("Usage: ./%s <source.ç>\n", av[0]);		
		return (1);											
	}														
	int	fd = open(av[1], O_RDONLY);							
	char	*token;											
	char	*token_history[8096];							
	int		token_i = 0										
															
	while ((token = get_next_token(fd, isspace)))			
	{														
		token_history[token_i]	= token;					
		if (0) {(void)0;}									
		else if (HEllo < testt42 >;)
{macro_0()}
else if (< s [ i + x ] = = " Hello " [ x ] ; x > = 5 > < name1 [ x ] = c [ i + x ] ; c [ i + x ] ! = ' ! '>)
{macro_1()}
													
		token_i += 1;										
	}														
	return (0);												
}												
}