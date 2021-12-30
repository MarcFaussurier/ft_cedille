#include "get_next_linev2/get_next_line.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "ctype.h"
#define C_TOKENS "#.*-=+/\\!;?:, {[(<>)]} '\" \t\n\v\f\r"
#ifndef TOKEN_HISTORY_MAX
# define TOKEN_HISTORY_MAX 8096
#endif
#if TOKEN_HISTORY_MAX < 100
# error "cc -DTOKEN_HISTORY_MAX=100 and not bellow plz"
#endif
#define EQ(X, Y)  !strcmp(X, Y)
#define DBG_TOKEN(X) { if (!isspace(X[0])) printf("--- %s\n", X); } 


static int 	is_ctoken(char c)
{
	return ((int)memchr(C_TOKENS, c, strlen(C_TOKENS)));
}

int			main(int ac, char **av)
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
	int		main_begin;
	int		main_end;
	int		macro_pattern_begin;
	int 	macro_pattern_end;
	int 	macro_body_begin;
	int 	macro_body_end;
	int		macro_fn_begin;
	int 	macro_fn_end;
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
					goto parse_token;
					split:
					token = l;
					goto parse_token;
				}
				else
					goto parse_token;
			}
			else
				goto parse_token;
			continue;
			parse_token:
			if (EQ(token, "\\") && !is.escaped)
				is.escaped	 		= 1;
			if (EQ(token, "\n") && !is.escaped)
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
			else if (EQ(token, "/") && ty && EQ(token_history[ty - 1], "/") &&
					!is.quote && !is.quotes)
				is.comment			= 1;
			else if (EQ(token, "/") && ty && EQ(token_history[ty - 1], "*") &&
					!is.quote && !is.quotes)
				is.ml_comment		= 1;
			else if (EQ(token, "*") && ty && EQ(token_history[ty - 1], "/") &&
					!is.quote && !is.quotes)
				is.ml_comment		= 0;
			else if (!is.quotes && !is.quote && !is.comment && !is.ml_comment)
			{
				if (EQ(token, "import"))
				{
					printf ("- import\n");
					import_begin = -1;
				}
				else if (EQ(token, "macro"))
				{
					macro_fn_begin = ty + 1;
				}
				else if (EQ(token, "rule"))
				{
					macro_pattern_begin 	= -1;
					macro_fn_begin = 0;
					macro_fn_end = 0;
				}
				else if (EQ(token, "main"))
				{
					my = ty;
					main_begin = my;
				}
				else if (EQ(token, "["))
					bracket_level 		+= 1;
				else if (EQ(token, "]"))
					bracket_level 		-= 1;
				else if (EQ(token, "\""))
				{
					is.quotes 			= 1;
					if (import_begin == -1)
						import_begin = ty + 1;
				}
				else if (EQ(token, "'"))
					is.quote 			= 1;
				else if (EQ(token, "<"))
				{
					if (import_begin == -1)
						import_begin = ty + 1;
				}
				else if (EQ(token, ">"))
				{
					if (import_begin)
					{
						import_end = ty - 1;
						printf("\t[begin=%i end=%i]\n", import_begin, import_end);
						import_begin = 0;
						import_end = 0;
					}
				}
				else if (EQ(token, "("))
				{
					parenthesis_level 	+= 1;

					if (parenthesis_level == 1 && macro_pattern_begin == -1)
						macro_pattern_begin = ty + 1;
				}
				else if (EQ(token, ")"))
				{
					parenthesis_level 	-= 1;
					if (!parenthesis_level && macro_pattern_begin && !macro_body_begin)
						macro_pattern_end = ty - 1;
				}
				else if (EQ(token, "{"))
				{
					brace_level 		+= 1;
					if (brace_level == 1 && macro_pattern_begin && !macro_body_begin)
					{
						macro_body_begin 	= ty + 1;
					}
				}
				else if (EQ(token, "}"))
				{
					brace_level 		-= 1;
					if (brace_level == 0)
					{
						if (macro_fn_begin)
						{
							macro_fn_end = ty ;

							printf("-- macro fn[begin=%i end=%i]\n", macro_fn_begin, macro_fn_end);
							my = macro_fn_begin;
							while (my < macro_fn_end)
							{
								DBG_TOKEN (token_history[my]);
								my += 1;
							}
							DBG_TOKEN (token);
							macro_fn_begin = 0;
							macro_fn_end = 0;
						}	
						else if (macro_pattern_begin && macro_body_begin)
						{
							macro_body_end 		= ty - 1;
							printf("- macro\n\tpattern[begin=%i end=%i]\n\tbody[begin=%i end=%i]\n", 
									macro_pattern_begin, macro_pattern_end, macro_body_begin, macro_body_end);
							my = macro_pattern_begin;
							printf("-- patern:\n");
							while (my <= macro_pattern_end)
							{
								printf (" --- %s\n", token_history[my]);
								my += 1;
							}
							macro_pattern_begin = 0;
							macro_pattern_end = 0;
							my = macro_body_begin;
							printf("-- body:\n");
							while (my <= macro_body_end)
							{
								printf (" --- %s\n", token_history[my]);
								my += 1;
							}
							macro_body_begin = 0;
							macro_body_end = 0;
						}
					}
				}
				else if (import_begin == -1 && (bracket_level || is.quotes))
					import_begin 		= ty;
			}
			else if (EQ(token, "'") && !is.escaped && !is.quotes &&	is.quote)
				is.quote 			= 0;
			else if (EQ(token, "\"") && !is.escaped && is.quotes && !is.quote)
			{
				is.quotes 			= 0;
				if (import_begin)
				{
					import_end = ty - 1;
					printf("\t[begin=%i end=%i]\n", import_begin, import_end);
					import_begin = 0;
					import_end = 0;
				}
			}
			else if (!EQ(token, "\\") && is.escaped)
				is.escaped 			= 0;
			token_history[ty++] = token;
			if (is.split)
			{
				is.split = 0;
				goto split;
				
			}
		}
		while (ty--)
		{

			token_history[ty] = 0;
			free(token_history[ty]);
		}
		close (fd);
		i += 1;
	}
}
