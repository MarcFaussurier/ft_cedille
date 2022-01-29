#include <fcntl.h>					
#include <stdio.h>											
#include "get_next_linev2/get_next_line.h" 				
#import "test.c"




 															
															
char *macro_0(char *testt42){return ( cat ( " Hello   " , test42 ) );}
char *macro_1(char *wordG,char *word,char *test){return ( cat ( " Hello   dear   " , word ) );}
															
															
int main(int ac, char **av)									
{															
	if (ac < 2)												
	{														
		printf("Usage: ./%s <source.ç>
", av[0]);		
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
else if (Hello < wordG dd > < word tt > < test f >!)
{macro_1()}
													
		token_i += 1;										
	}														
	return (0);												
}