#include <fcntl.h>					
#include <stdio.h>											
#include <fcntl.h>											
#include <sys/mman.h>										
#include <unistd.h>											
#import "ç"
#import "spec-mvp2.ç"




 															
															
char *macro_0(){
	return x;
}
char *macro_1(char *s,char *name){
	return (cat("Hello ", name));
}
char *macro_2(char *s,char *name1){
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
		else if ()
{macro_0()}
else if (
	<s[i + x] == "HEllo"[x] ; x[i + x]>
		<name[x] = s[i + x] ; x[i + x] != ';'>
)
{macro_1()}
else if (
	<s[i + x] == "Hello"[x] 	; x >= 5>
		<name1[x] = c[i + x] 	; c[i + x] != '!'>
)
{macro_2()}
	*/												
		len += 1;											
	}														
	return (0);												
}