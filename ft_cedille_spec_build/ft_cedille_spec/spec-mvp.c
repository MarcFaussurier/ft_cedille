#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"

macro int m_state_test = 0;

macro int f(int x)
{
	return (x);
}

/*
	<continue while ; succeed on ;>
*/

// test

macro rule
(
	<	 	s[i + x + y] == "Hello"[y]			; 	y == 4 				;>
		< 	s[i + x + y] == " bb"[y]			;	y == 1				;>

)
{
	m_state_test += 1;
	return(cat("Good night !:)"));
}

int main(int ac, char **av)
{
	printf ("Good night !:)! Hallo joe; Hallo ddd;");
	return (0);
}
