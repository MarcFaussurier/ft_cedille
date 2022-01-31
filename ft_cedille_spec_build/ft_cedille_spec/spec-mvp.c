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
	<; s[i + x] == "Hello"[x] 	; x < 6 ;>
		<; name1[x] = s[i + x] 	; (s[i + x] != '!' || (name1[x] = 0)) ; >
)
{
	m_state_test += 1;
	return(cat("Hello ", name1, "!:))\n"));
}

int main(int ac, char **av)
{
	printf ("Hello aa, bb! Hallo joe;");
	return (0);
}
