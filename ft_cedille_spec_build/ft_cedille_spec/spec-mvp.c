#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"
#include "string.h"

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
	<s[x + y] == "Hello "[y]				;	y == 5;>
		<(test[y] = s[x + y]) && y < 5		;	s[x + y] == "!"[0]	&& !(test[y] = 0);>
)
{
	m_state_test += 1;
	return(cat("Good night dear ", test, "."));
}

#define await
macro	rule
(
	<s[x + y] == "await"[y]							; 	y == 4;>
		<(name[y] = s[x + y]) && y < 11 && s[x + y]	;	s[x + y] == '(' && !(name[y] = 0);>
				<(args[y] = s[x + y])  				
				;	
					s[x + y] == ')'	
					&& 
					!(
						(args[y] = 0) 
						|| 
						(m_brackets_level = 0)
					)
				;>
					<(body[y] = s[x + y]) 
						&&
						(
							(
								(s[x + y] == '{' && ++m_brackets_level) 
								|| 		
								(s[x + y] == '}' && (m_brackets_level-- || 1))
							) 
							|| 1
						)
					;	
						(s[x + y] == '}' && m_brackets_level < 0)
						&&
						!(body[y] = 0)
					;>
)
{
	char	*o;

	asprintf(&o, "%s(%s %s ^() { %s });\n}", 
		cat(name), cat(args), strlen(cat(args)) ? "," : "", cat(body));

	return (o);
}



void 	bar( void (^ptr)() )
{

}





void 	foo( void (^ptr)() )
{

}

int main(int ac, char **av)
{
	printf ("Good night dear bb. Hallo joe; Hallo ddd;");

	{
			foo(  ^() { ;
		printf("a");
		await	bar(0);
		printf("a");
 });
}

	return (0);
}
