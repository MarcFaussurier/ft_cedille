#include <fcntl.h>					
#include <stdio.h>											
#include <fcntl.h>											
#include <sys/mman.h>										
#include <unistd.h>											
#include <stdarg.h>											
#include <string.h>											
#include <sys/stat.h>										
#define str(x) #x											
#include <stdlib.h>											
#import "ç"
#import "spec-mvp2.ç"
#include "stdio.h"
#include "string.h"
#include <ctype.h>

 int 	m_state_test = 0;
 int	m_brace_level = 0;
 int	m_bracket_level = 0;
 int	m_parenthesis_level = 0;

 int f(int x)
{
	return (x);
}

/*
	<continue while ; succeed on ;>
*/

// test

 




 char	*trim(char *str)
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

 char 	*lastword(char *str)
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
		



int 	bar( int p, void (^ptr)(int k) )
{
	ptr(21);
	return (0);
}





int 	foo( int p, char c, void (^ptr)(int k) )
{
	ptr(42);
	return (0);
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
															
static void mkpath(const char *dir)							
{															
    char tmp[256];											
    char *p = NULL;											
    size_t len;												
															
    snprintf(tmp, sizeof(tmp),"%s",dir);					
    len = strlen(tmp);										
    if (tmp[len - 1] == '/')								
        tmp[len - 1] = 0;									
    p = tmp + 1;											
	while(*p)												
	{														
        if (*p == '/')										
		{													
            *p = 0;											
            mkdir(tmp, S_IRWXU);							
            *p = '/';										
        }													
		p += 1;												
	}														
}															

char *macro_0(int i, int x, int y, char *s, char *__end){

	return (cat("!! "));

}


char *macro_1(int i, int x, int y, char *s, char *test2, char *__end){

	m_state_test += 1;
	return(cat("Good night dear ", test2, "."));

}


char *macro_2(int i, int x, int y, char *s, char *prev, char *assignation, char *name, char *args, char *body, char *__end){

	char	*o;


	
	asprintf(&o, "%s\n%s(%s %s ^(typeof(%s(0)) %s) { %s });\n}",
		cat (prev), cat(name), cat(args), strlen(cat(args)) ? "," : "", cat(name), lastword(cat(assignation)), cat(body));

	return (o);

}

															
															
int main(int ac, char **av)									
{															
	int		out_fd;											
	int		fd;												
	char	*s;												
	int		i;												
	int		x;												
	int		y;												
	char	*o;												
	char	*r;												
	int		success;										
	char	*macro_name;									
	int		i_len;											
															
	if (ac < 3)												
	{														
		printf("Usage: ./%s <source.ç> <dest.c>\n", av[0]);
		return (1);											
	}														
	mkpath(av[2]);											
	out_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("out_file=%s fd=%i\n", av[2], out_fd);		
	if (out_fd < 0)											
	{														
		printf("Error - unable to open output file '%s'\n", av[2]);
	}														
	fd = open(av[1], O_RDONLY);								
	printf("source_file=%s fd=%i\n", av[1], fd);		
	if (fd < 0)												
	{														
		printf("Error - unable to open source file '%s'\n", av[1]);
		return (1);											
	}														
	i = lseek(fd, 0, SEEK_END);								
	s = mmap(0, i, PROT_READ, MAP_PRIVATE, fd, 0);			
	i = 0;													
	macro_name = "marvin";								
	i_len = strlen(s);										
	while (s[i])											
	{														
		 
																
					success = 1;
x=i;
																		
					char __end[1024];*__end = 0;
																		
					y = 0;																	
					while (success)															
					{																		
						if (!(s[x+y] == 0 ))															
						{																	
							macro_name = "macro_0";											
							success = 0;													
							break ;															
						}																	
						if ( 0 )																
						{																	
							y += 1;															
							printf("%s succeed macro_0 %i!\n", str( 0 ), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
	if (success)																			
	{																						
		r = macro_0(i, x, y, s, __end);																			
		goto success;																		
	}

																
																					
					success = 1;
x=i;
																		
					char test2[1024];
*test2 = 0; 																		
					y = 0;																	
					while (success)															
					{																		
						if (!(s[x + y] == "Hello "[y]				))															
						{																	
							macro_name = "macro_1";											
							success = 0;													
							break ;															
						}																	
						if (	y == 5)																
						{																	
							y += 1;															
							printf("%s succeed macro_1 %i!\n", str(	y == 5), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!((test2[y] = s[x + y]) && y < 5		))															
						{																	
							macro_name = "macro_1";											
							success = 0;													
							break ;															
						}																	
						if (	s[x + y] == "!"[0]	&& !(test2[y] = 0))																
						{																	
							y += 1;															
							printf("%s succeed macro_1 %i!\n", str(	s[x + y] == "!"[0]	&& !(test2[y] = 0)), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
	if (success)																			
	{																						
		r = macro_1(i, x, y, s, test2, __end);																			
		goto success;																		
	}

																
																					
																					
																					
																					
																					
																					
					success = 1;
x=i;
																		
					char prev[1024];
*prev = 0; char assignation[1024];
*assignation = 0; char name[1024];
*name = 0; char args[1024];
*args = 0; char body[1024];
*body = 0; 																		
					y = 0;																	
					while (success)															
					{																		
						if (!((prev[0] = s[x])
		&&
		(
			s[x] == '{'
			||
			s[x] == semicolon
		)
		))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if (
		(
			!(prev[1] = 0)
		)
	)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str(
		(
			!(prev[1] = 0)
		)
	), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!((assignation[y] = s[x + y])
		&& 
		(
			s[x + y] != '{' 
			&& 
			s[x + y] != semicolon)
		))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if (
		(s[x + y] == '=' || ((s[x + y] == 'a' && s[x + y + 1] == 'w') && (--x || 1)))
		&&
		!(assignation[y] = 0)
	)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str(
		(s[x + y] == '=' || ((s[x + y] == 'a' && s[x + y + 1] == 'w') && (--x || 1)))
		&&
		!(assignation[y] = 0)
	), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!(x
	))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if ( 
	!isspace(s[x + y]) && (--x || 1))																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str( 
	!isspace(s[x + y]) && (--x || 1)), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!(s[x + y] == "await"[y]							))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if ( 	y == 4)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str( 	y == 4), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!((name[y] = s[x + y]) && y < 8 && s[x + y]	
		))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if (	
		s[x + y] == '(' 
		&&
		!(
			(name[y] = 0)
			||
			(m_parenthesis_level = 0)
		)
		)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str(	
		s[x + y] == '(' 
		&&
		!(
			(name[y] = 0)
			||
			(m_parenthesis_level = 0)
		)
		), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!((args[y] = s[x + y]) 
				&&
				(((s[x + y] == '(')
				&&
				++m_parenthesis_level) || 1)
				))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if (
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
				)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str(
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
				), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
																							
					y = 0;																	
					while (success)															
					{																		
						if (!((body[y] = s[x + y])
						&&
						(
							(
								(s[x + y] == '{' && ++m_brace_level)
								|| 		
								(s[x + y] == '}' && (m_brace_level-- || 1))
							) 
							|| 1
						)
					))															
						{																	
							macro_name = "macro_2";											
							success = 0;													
							break ;															
						}																	
						if (	
						(s[x + y] == '}' && m_brace_level < 0)
						&&
						!(body[y] = 0)
					)																
						{																	
							y += 1;															
							printf("%s succeed macro_2 %i!\n", str(	
						(s[x + y] == '}' && m_brace_level < 0)
						&&
						!(body[y] = 0)
					), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
																					
	if (success)																			
	{																						
		r = macro_2(i, x, y, s, prev, assignation, name, args, body, __end);																			
		goto success;																		
	}
													
		goto failure;										
		success:											
			printf("1 macro applied [id=%s i=%d x=%d on=%.*s].\n", macro_name,  i, x, x - i, s + i);
			i = x - 1 ;										
			dprintf(out_fd, "%s", r);					
			if (i >= i_len)									
				break;										
			goto end;										
		failure:											
			dprintf(out_fd, "%c", s[i]);					
		end:												
		i += 1;												
	}														
	return (0);												
}