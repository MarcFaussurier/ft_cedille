#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"

macro int m_state_test = 0;

macro int f(int x)
{
	return (x);
}

macro rule
(
	<	 s[i + x] == "Good night !:)"[x] 	; 	x < 4	;>
)
{
	m_state_test += 1;
	return(cat("Good night !:)"));
}

int main(int ac, char **av)
{
	printf ("Good night !:) bb! Hallo joe; Hallo ddd;");
	return (0);
}
