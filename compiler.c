#include "get_next_linev2/get_next_line.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#define eq(X, Y)  !strcmp(X, Y)
#define C_TOKENS "#.*-=+/\\!;?:, {[(<>)]} '\" \t\n\v\f\r"

#ifndef TOKEN_HISTORY_MAX
# define TOKEN_HISTORY_MAX 8096
#endif
#if TOKEN_HISTORY_MAX < 100
# error "cc -DTOKEN_HISTORY_MAX=100 and not bellow plz"
#endif

static int is_ctoken(char c)
{
	return ((int)memchr(C_TOKENS, c, strlen(C_TOKENS)));
}

int main(int ac, char **av)
{

	int		i;
	int 	fd;
	int		ty;
	char	*token_history[TOKEN_HISTORY_MAX];
	char 	*token;
	char	*l;
	int		token_len;
	struct	s_is
	{
		int quotes:					1;
		int quote:					1;
		int	comment:				1;
		int	ml_comment:				1;
		int escaped:				1;
		int preprocessor:			1;
		int	import:					1;
		int macro_pattern:			1;
		int macro_body:				1;
		int split:					1;
	}		is;
	int 	parenthesis_level;
	int 	bracket_level;
	int 	brace_level;
	int		import_begin;
	int		import_end;
	int		macro_pattern_begin;
	int 	macro_pattern_end;
	int 	macro_body_begin;
	int 	macro_body_end;
	int 	my;

	if (ac < 2)
	{
		printf ("Usage: %s <file1.c file2.c ...>\n", av[0]);
		return (0);
	}
	i 								= 1;
	while (i < ac)
	{
		printf ("opening: %s\n", av[i]);
		fd 							= open(av[i], O_RDONLY);
		if (fd < 0)
		{
			printf ("Error: unable to open file.\n");
			return (1);
		}
		ty 							= 0;
		is.import 					= 0;
		is.quotes 					= 0;
	 	is.quote 					= 0;
		is.comment 					= 0;
		is.ml_comment 				= 0;
		is.escaped 					= 0;
		is.preprocessor				= 0;
	 	is.import					= 0;
		is.split					= 0;
		parenthesis_level 			= 0;
	 	bracket_level				= 0;
	 	brace_level					= 0;
		while ((token 				= get_next_token(fd, is_ctoken)))
		{
		//	printf("-t: %s\n", token);
			token_len = strlen(token);
			if (is_ctoken(token[token_len - 1]))
			{
				if (token_len > 1)
				{

					l = malloc(2);
					l[0] = token[token_len - 1];
					l[1] = 0;
					token[token_len - 1] = 0;
					
					is.split = 1;
				//	printf("--splited %s -- %s\n", token, l);
					goto parse_token;
					split:
					token = l;
					goto parse_token;
				}
				else
				{
				//	printf("--onechar\n");
					goto parse_token;
				}	
			}
			else
				goto parse_token;
			continue;
			parse_token:
		//	printf("--- %s\n", token);
			if (eq(token, "(") && !is.quotes && !is.quote)
			{
				parenthesis_level 	+= 1;
				if (parenthesis_level == 1 && macro_pattern_begin == -1)
					macro_pattern_begin = ty + 1;
			}
			else if (eq(token, ")") && !is.quotes && !is.quote)
			{
				parenthesis_level 	-= 1;
				if (!parenthesis_level && macro_pattern_begin && !macro_body_begin)
					macro_pattern_end = ty - 1;
			}
			else if (eq(token, "{") && !is.quotes && !is.quote)
			{
				brace_level 		+= 1;
				if (brace_level == 1 && macro_pattern_begin && !macro_body_begin)
				{
					macro_body_begin 	= ty + 1;
				}
			}
			else if (eq(token, "}") && !is.quotes && !is.quote)
			{
				brace_level 		-= 1;
				if (brace_level == 0 && macro_pattern_begin && macro_body_begin)
				{
					macro_body_end 		= ty - 1;
					printf(" - macro\n\tpattern[begin=%i end=%i]\n\tbody[begin=%i end=%i]\n", macro_pattern_begin, macro_pattern_end, macro_body_begin, macro_body_end);
					my = macro_pattern_begin;
					printf("-- patern:\n");
					while (my <= macro_pattern_end)
					{
					printf (" - %s\n", token_history[my]);
						my += 1;
					}
					macro_pattern_begin = 0;
					macro_pattern_end = 0;
					my = macro_body_begin;
					printf("-- body:\n");
					while (my <= macro_body_end)
					{
						printf (" - %s\n", token_history[my]);
						my += 1;
					}
					macro_body_begin = 0;
					macro_body_end = 0;
				}
			}
			else if (eq(token, "[") && !is.quotes && !is.quote)
				bracket_level 		+= 1;
			else if (eq(token, "]") && !is.quotes && !is.quote)
				bracket_level 		-= 1;
			else if (eq(token, "\"") && !is.quotes && !is.quote)
				is.quotes 			= 1;
			else if (eq(token, "'") && !is.quotes && !is.quote)
				is.quotes 			= 1;
			else if (eq(token, "\\") && !is.escaped)
				is.escaped	 		= 1;
			else if (eq(token, "'") && !is.escaped && !is.quotes &&	is.quote)
				is.quote 			= 0;
			else if (eq(token, "\"") && !is.escaped && is.quotes && !is.quote)
				is.quotes 			= 0;
			else if (eq(token, "/") && ty && eq(token_history[ty - 1], "/") &&
					!is.quote && !is.quotes)
				is.comment			= 1;
			else if (eq(token, "/") && ty && eq(token_history[ty - 1], "*") &&
					!is.quote && !is.quotes)
				is.ml_comment		= 1;
			else if (eq(token, "*") && ty && eq(token_history[ty - 1], "/") &&
					!is.quote && !is.quotes)
				is.ml_comment		= 0;
			else if (is.import && (bracket_level || is.quotes))
				import_begin 		= ty;
			else if (is.preprocessor && eq(token, "import"))
				is.import 			= 1;
			else if (eq(token, "macro") && !is.quote && !is.quotes && !is.comment && !is.ml_comment)	
				macro_pattern_begin 	= -1;
			else if (eq(token, "\n") && !is.escaped)
			{
				is.comment 			= 0;
				is.preprocessor 	= 0;

				if (is.import)
				{
					import_end 		= ty - 1;
					printf("import [begin=%i end=%i]\n", import_begin, import_end);
					is.import 		= 0;
				}
			}
			else if (!eq(token, "\\") && is.escaped)
				is.escaped 			= 0;
			token_history[ty++] = token;
			if (is.split)
			{
				is.split = 0;
				goto split;
				
			}
		}
		while (ty--)
			free(token_history[ty]);
		close (fd);
		i += 1;
	}
}
