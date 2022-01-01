#include "get_next_linev2/get_next_line.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "ctype.h"

#ifndef TOKEN_HISTORY_MAX
# define TOKEN_HISTORY_MAX 8096
#endif
#if TOKEN_HISTORY_MAX < 100
# error "cc -DTOKEN_HISTORY_MAX=100 and not bellow plz"
#endif
#define EQ(X, Y)  !strcmp(X, Y)
#define DBG_TOKEN(X) { if (!isspace(X[0])) printf("--- %s\n", X); } 
#define ERROR(X, ...) { sprintf(error, X, __VA_ARGS__);\
	printf("\033[1m%s:%i:%i: \033[31merror: \033[0m\033[1m%s\033[0m\n", path, line, col, error);\
	errors += 1; }


const char *C_TOKENS = "#.*-=+/\\!;?:, {[(<>)]} '\" \t\n\v\f\r";

int import_paths_count = 2;
const char *import_paths[255] = {
	"/usr/include",
	"/usr/local/include",
};

static int 	strlen_ctokens;

static int 		is_ctoken(char c)
{
	return ((int)memchr(C_TOKENS, c, strlen_ctokens));
}


char *strscat(char **strs, int from, int to)
{
	int i;
	int l;
	int	x;
	char *o;

	
	l = 0;
	i = from;
	while (i <= to)
	{
		l += strlen(strs[i]);
		i += 1;
	}
	o = malloc(l + 1);
	i = from;
	l = 0;
	while (i <= to)
	{
		x = 0;
		while (strs[i][x])
		{
			o[l] = strs[i][x];
			x += 1;
			l += 1;
		}
		i += 1;
	}
	return (o);
}

static int	parse(char *path)
{
	int		fd;
	int		ty;
	char	*token_history[TOKEN_HISTORY_MAX];
	char	*token;
	char	*l;
	int		token_len;
	char	*import_path;
	struct	s_is
	{
		int	quotes:					1;
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
	int		line;
	int		col;
	int		errors;
	char	error[2048];

	fd 							= open(path, O_RDONLY);
	if (fd < 0)
		return (4242);
	errors						= 0;
	line 						= 1;
	col 						= 1;
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
			line += 1;
			col = 0;
			is.comment 			= 0;
			is.preprocessor 	= 0;
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
flush_import:
				if (import_begin) 
				{
					// TODO: import using only import path 
					import_end = ty - 1;
					my = import_begin;
					import_path = strscat(token_history, import_begin, import_end);
					if (parse(import_path))
					{
						ERROR("'%s' file not found", import_path);
					}
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
						macro_fn_begin = 0;
						macro_fn_end = 0;
					}	
					else if (macro_pattern_begin && macro_body_begin)
					{
						macro_body_end 		= ty - 1;
						macro_pattern_begin = 0;
						macro_pattern_end = 0;
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
			// TODO: import using relative paths
			is.quotes 			= 0;
			goto flush_import;
		}
		else if (!EQ(token, "\\") && is.escaped)
			is.escaped 			= 0;
		goto no_error;

no_error:
		token_history[ty++] = token;
		col += token_len;
		if (is.split)
		{
			is.split = 0;
			token = l;
			goto parse_token;
		}
	}
	my = 0;
	while (my < ty)
	{
		free(token_history[my]);
		my += 1;
	}
	close (fd);
	return (errors);
}

int			main(int ac, char **av)
{

	int		i;
	int		r;
	

	if (ac < 2)
	{
		printf ("Usage: %s <file1.c file2.c ...>\n", av[0]);
		return (1);
	}
	strlen_ctokens = strlen(C_TOKENS);
	i 								= 1;
	// TODO: parse -I && -o flags
	while (i < ac)
	{
		r = parse(av[i]);
		if (r == 4242)
		{
			printf("Error: unable to open: '%s'\n", av[i]);
			return (r);
		}
		i += 1;
	}
	return (0);
}
