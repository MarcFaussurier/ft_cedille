#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"

macro int 	m_state_test = 0;
macro int	m_brackets_level = 0;

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
	<s[x + y] == "Hello"[y]		;	y == 4;>
		<s[x + y] == " bb"[y]	;	y == 1;>
)
{
	m_state_test += 1;
	return(cat("Good night !:)"));
}

macro	rule
(
	<s[x + y] == "await"[y]							; 	y == 4;>
		<x && y < 10 && s[x + y]					;	!isspace(s[x + y]);>
			<x	&& y < 10 && s[x + y]				;	s[x + y] == '(';>
				<(args[y] = s[x + y])  				;	s[x + y] && s[x + y] == ')'	&& !(args[y] = 0);>
					<x								;	s[x + y] && !isspace(s[x + y]);>
							<(body[y] = s[x + y]) 
								&&
								((
								(	s[x + y] == '{' && m_brackets_level++) 
									|| 		
									(s[x + y] == '}' && m_brackets_level--)
								) || 1)
							;	
								(s[x + y] == '}' && !m_brackets_level)
								||
								!(body[y] = 0)
							;>
)
{
	return (cat("printf(\"508 PSE\");"));
}
#define await
#define foo()
int main(int ac, char **av)
{
	printf ("Good night !:)! Hallo joe; Hallo ddd;");

	printf("508 PSE");return (0);
}
