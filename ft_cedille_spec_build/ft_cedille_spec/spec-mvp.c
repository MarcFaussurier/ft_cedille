#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"
#include "string.h"
#include <ctype.h>

macro int 	m_state_test = 0;
macro int	m_brace_level = 0;
macro int	m_bracket_level = 0;
macro int	m_parenthesis_level = 0;

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




macro char	*trim(char *str)
{
	int	i;
	char	*o;

	while (*str && isspace(*str))
	{
		str += 1;
	}
	i = 0;
	while (str[i] && !isspace(str[i]))
	{
		i += 1;
	}
	asprintf(&o, "%.*s", i, str);
	return (o);
}

macro char 	*lastword(char *str)
{
	char	*lastspace;
	int		i;

	i = 0;
	while (str[i])
			i += 1;
	while ((i - 1) && isspace(str[i - 1]))
		i -= 1;

	while ((i - 1) && !isspace(str[i - 1]))
		i -= 1;
	return (str + i);

}

#define await
macro		rule
(
	<
		(prev[0] = s[x])
		&&
		(
			s[x] == '{'
			||
			s[x] == semicolon
		)
		;
		(
			!(prev[1] = 0)
		)
	;>
	<
		(assignation[y] = s[x + y])
		&& 
		(
			s[x + y] != '{' 
			&& 
			s[x + y] != semicolon)
		;
		(s[x + y] == '=' || ((s[x + y] == 'a' && s[x + y + 1] == 'w') && (--x || 1)))
		&&
		!(assignation[y] = 0)
	;>
	<x
	; 
	!isspace(s[x + y]) && (--x || 1);>
	<s[x + y] == "await"[y]							; 	y == 4;>
		<(name[y] = s[x + y]) && y < 8 && s[x + y]	
		;	
		s[x + y] == '(' 
		&&
		!(
			(name[y] = 0)
			||
			(m_parenthesis_level = 0)
		)
		;>
				<(args[y] = s[x + y]) 
				&&
				(((s[x + y] == '(')
				&&
				++m_parenthesis_level) || 1)
				;
					(
						s[x + y] == ')'
						&&
						!(m_parenthesis_level < 0)
					)
					&& 
					!(
						(args[y] = 0) 
						||
						(m_brace_level = 0)
					)
				;>
					<(body[y] = s[x + y])
						&&
						(
							(
								(s[x + y] == '{' && ++m_brace_level)
								|| 		
								(s[x + y] == '}' && (m_brace_level-- || 1))
							) 
							|| 1
						)
					;	
						(s[x + y] == '}' && m_brace_level < 0)
						&&
						!(body[y] = 0)
					;>
)
{
	char	*o;


	
	asprintf(&o, "%s\n%s(%s %s ^(typeof(%s(0)) %s) { %s });\n}",
		cat (prev), cat(name), cat(args), strlen(cat(args)) ? "," : "", cat(name), lastword(cat(assignation)), cat(body));

	return (o);
}



int 	bar( void (^ptr)(int k) )
{
	ptr(21);
	return (0);
}





int 	foo( void (^ptr)(int k) )
{
	ptr(42);
	return (0);
}

int main(int ac, char **av)
{
	printf ("Good night dear bb. Hallo joe; Hallo ddd;");

	{
	foo(  ^(typeof(	foo(0)) i ) { ;
		printf("a: %i\n", i);
	bar(  ^(typeof(	bar(0)) z ) { ;
		printf("b: %i\n", z);
  });
});
}

	return (0);
}
