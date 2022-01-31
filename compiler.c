// ft :
#include "get_next_linev2/get_next_line.h"
// syscalls :
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
// will be replaced by ft :
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdarg.h"

#ifndef TOKEN_HISTORY_MAX
# define TOKEN_HISTORY_MAX 8096
#endif
#if TOKEN_HISTORY_MAX < 100
# error "cc -DTOKEN_HISTORY_MAX=100 and not bellow plz"
#endif
#define EQ(X, Y)  !strcmp(X, Y)
#define DBG_TOKEN(X) 					\
{										\
	if (!isspace(X[0])) 				\
		printf("--- %s\n", X); 			\
} 
#define ERROR(X, ...) 					\
{ 										\
	sprintf(error, X, __VA_ARGS__);		\
	printf("\033[1m%s:%i:%i: \033[31merror: \033[0m\033[1m%s\033[0m\n",\
			path, line, col, error);	\
	errors += 1; 						\
}
#define CMD_ERROR(X, ...)				\
{				\
	sprintf(error, X, __VA_ARGS__);		\
	printf("ç: \033[1m\033[31merror: \033[0m%s\n", error);\
	errors += 1; 						\
}
#define c_tokens "#.*-=+/\\!;?:, {[(<>)]} '\" \t\n\v\f\r"
#define default_output_sufix "-compiler.c"
#define default_output_prefix "./"

int 		import_paths_count = 2;
char 		import_paths[255][255] = { "/usr/include", "/usr/local/include"};
int 		sources_count = 0;
char 		sources[255][255];
int			macro_patterns_count = 0;
char		macro_patterns[255][2][4096];
int			references_count = 0;
char		references[255][255];
int			label_count = 0;
char		labels[255][255];


static int	is_def(char *label)
{
	int		i;

	i = 0;
	while (i < label_count)
	{
		if (EQ(labels[i], label))
			return (1);
		i += 1;
	}
	return (0);
}

static int 	is_ctoken(char c)
{
	return ((int)memchr(c_tokens, c, sizeof(c_tokens) / sizeof(char) - 1));
}

static int	is_name(char c)
{
	return 	(c >= 'a' && c <= 'z')
		||	(c >= 'A' && c <= 'Z')
		|| 	(c == '_')
		||	(c >= '0' && c <= '9');
}

// mode 0 ==> macro typed args
// mode 1 ==> decl typed inits
// mode 2 ==> fn calls
char		*ft_generate_macro_labels(char *id, char *pattern, char *body, int mode)
{
	int		i;
	int		z;
	int		y;
	char	*out = malloc(8096);
	int		u;
	int		p;
	int		passed_label_count = 0;
	char	*passed_labels[255];

	passed_labels[0] = "";
	*out = 0;
	if (mode == 2)
		strcat(out, "i, x, s, ");
	else if (mode == 0)
		strcat(out, "int i, int x, char *s,");
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '<')
		{
			i += 1;
			while (isspace(pattern[i]))
				i += 1;
			u = 0;
			while (is_name(pattern[i]))
				labels[label_count][u++] = pattern[i++];

			labels[label_count][u] = 0;
			
			if (!EQ(labels[label_count], "s") && !EQ(labels[label_count], "x") && !EQ(labels[label_count], "i"))
			{

				if (mode == 0)
				{
					p = 0;
					while (p < passed_label_count && !EQ(passed_labels[p], labels[label_count]))
					{
						p += 1;
					}
				//	if (p == label_count)
				//	{
						strcat(out, "char *");
						strcat(out, labels[label_count]);
						strcat(out, ",");
				//		sprintf(passed_labels[passed_label_count], "%s", labels[label_count]);
				//		passed_label_count += 1;
				//	}
				}
				else if (mode == 1 && !is_def(labels[label_count]))
				{
					strcat(out, "char ");
					strcat(out, labels[label_count]);
					strcat(out, "[1024];\n*");
					strcat(out, labels[label_count]);
					strcat(out, " = 0;\n");
					label_count += 1;

				}
				else if (mode == 2)
				{
					p = 0;
					while (p < passed_label_count && !EQ(passed_labels[p], labels[label_count]))
					{
						p += 1;
					}
				//	if (p == label_count)
				//	{
						strcat(out, labels[label_count]);
						strcat(out, ", ");
				//		sprintf(passed_labels[passed_label_count], "%s", labels[label_count]);
				//		passed_label_count += 1;
				//	}
				}

			}
			while (!(pattern[i] == ';'))
					i += 1;
			i += 1;
			while (!(pattern[i] == ';'))
					i += 1;
			i += 1;
			while (!(pattern[i] == '>'))
					i += 1;
		}
		i += 1;
	}
	if (!mode)
	{
		strcat(out, "char *__end");
	}
	else if (mode == 1 && !is_def("__end"))
	{
			strcat(out, "char __end[1024];*__end = 0;\n");
			sprintf(labels[label_count], "%s","__end");
			label_count += 1;
	}
	else if (mode == 2)
		strcat(out, "__end");
	return (out);	
}

char		*ft_generate_macro_function(char *id, char *pattern, char *body)
{
	int		i;
	int		z;
	int		y;
	char	*out = malloc(8096);
	int		p;
	int		u;

	printf("pattern=%s - body=%s\n", pattern, body);
	*out = 0;
	strcat(out, "char *");
	strcat(out, id);
	strcat(out, "(");
	strcat(out, ft_generate_macro_labels(id, pattern, body, 0));
	strcat(out, ")");
	strcat(out, "{\n");
	strcat(out, body);
	strcat(out, "\n}\n");
	return (out);	
}

char		*ft_generate_macro_parser(char *id, char *pattern, char *body)
{
	char	*out = malloc(8096);
	char	name1[8096];
	char	cond1[8096];
	char	cond2[8096];
	int		i = 0;
	int		y = 0;
	char	*aspf;
	int		x;
	int		last;


	asprintf(&aspf, "success = 1;");
	strcat(out, aspf);
	while (pattern[i])
	{
		if (pattern[i] == '<')
		{
			i += 1;
			while (isspace(pattern[i]))
				i += 1;
			y = 0;
			cond1[0] = 0;
			while (pattern[i] != ';')
			{	
				cond1[y] = pattern[i];
				y += 1;
				i += 1;
			}
			cond1[y] = 0;
			i += 1;
			y = 0;
			cond2[0] = 0;
			while (pattern[i] != ';')
			{
				cond2[y] = pattern[i];
				i += 1;
				y += 1;
			}
			x = 0;
			last = 1;
			while (pattern[i + x] && pattern[i + x] != ')' )
			{
				if (pattern[i + x] == ';' && pattern[i + x + 1] == '>')
					last = 0;
				x += 1;
			}
			cond2[y] = 0;
			asprintf(&aspf, "																\n\
					%s																		\n\
					x = 0;																	\n\
					while (success)															\n\
					{																		\n\
						if (!(%s))															\n\
						{																	\n\
							macro_name = \"%s\";											\n\
							success = 0;													\n\
							break ;															\n\
						}																	\n\
						if (!(%s))															\n\
						{																	\n\
							break ;															\n\
						}																	\n\
						x += 1;																\n\
					}																		\n\
			", ft_generate_macro_labels(id, pattern, body, 1), cond1, id, cond2);
			strcat(out, aspf);
		}

		i += 1;
	}

	asprintf(&aspf, "if (success)									\n\
	{															\n\
		r = %s(%s);														\n\
		goto success;																\n\
	}", id, ft_generate_macro_labels(id, pattern, body, 2));
	strcat(out, aspf);

	return (out);	
}


char 		*strscat(char **strs, int from, int to, int s)
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
	o = malloc(l * 2 + 1);
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
		if (s && i < to)
			o[l++] = ' ';
	}
	o[l] = 0;
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

static int	parse(const char *path, int depth, const char *output_sufix, const char *output_prefix)
{
	int		fd;
	int		outfd;
	int		ty;
	char	*token_history[TOKEN_HISTORY_MAX];
	char	*full_token_history[TOKEN_HISTORY_MAX];
	int 	fty;
	char	*compiler[TOKEN_HISTORY_MAX];
	int		compiler_i;
	char	buffer[255];
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
		int	local_import:			1;
		int	in_compiler:			2;
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
	int		line;
	int		col;
	int		errors;
	int		p;
	int		r;
	char	error[2048];
	char	macros[4096];
	char	parser[4096];
	char	header[4096];
	char	*body;
	char	*pattern;
	char	idz[64];

	p = 0;
	while (p < references_count)
	{
		if (!strcmp(references[p], path))
		{
			ERROR("File '%s' already included !\n", path);
			return (0);
		}
		p += 1;
	}
	sprintf(references[references_count], "%s", path);
	references_count += 1;
	printf("__________\n");
	printf ("#parsing: %s\n", path);
	fd 							= open(path, O_RDONLY);
	if (fd < 0)
		return (4242);
	errors						= 0;
	line 						= 1;
	col 						= 1;
	ty 							= 0;
	fty							= -1;
	is.import 					= 0;
	is.quotes 					= 0;
	is.quote 					= 0;
	is.comment 					= 0;
	is.ml_comment 				= 0;
	is.escaped 					= 0;
	is.preprocessor				= 0;
	is.import					= 0;
	is.split					= 0;
	is.in_compiler				= 1;
	parenthesis_level 			= 0;
	bracket_level				= 0;
	brace_level					= 0;
	compiler_i					= 0;
	macro_pattern_begin 		= 0;
	macro_pattern_end 			= 0;
	macro_body_begin 			= 0;
	macro_body_end 				= 0;
	main_begin					= 0;
	main_end 					= 0;
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
		full_token_history[++fty] = token;
		if (!(!is.quotes && !is.quote && !is.comment && !is.ml_comment) 
				 || !isspace(token[0]))
		{
				printf("%i:\t%s\n", ty, token);
			 	token_history[ty] = token;
		 }
		 else
		 {
				ty -= 1;
				goto next;
		 }
		col += token_len;
		if (EQ(token, "\\") && !is.escaped)
			is.escaped = 1;
		else if (EQ(token, "\n") && !is.escaped)
		{
			line += 1;
			col = 0;
			is.comment = 0;
			is.preprocessor = 0;
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
		//		ty -= 1;
				is.in_compiler = -1;
			}
			else if (EQ(token, "rule") && EQ(token_history[ty - 1], "macro"))
			{
				is.in_compiler = 0;
				macro_pattern_begin = -1;
			}
			else if (EQ(token, "main") && EQ(token_history[ty - 1], "int"))
			{
				main_begin = ty - 1;
				is.in_compiler = 0;
				compiler_i -= 2;
				printf("main begins at %i\n", main_begin);
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
				is.local_import = 0;
flush_import:
				if (import_begin) 
				{
					import_end = ty - 1;
					import_path = strscat
					(
					 	token_history, import_begin, import_end, 0
					);
					import_begin = 0;
					import_end = 0;
					if (is.local_import)
					{
						if (parse(import_path, depth + 1, output_sufix, output_prefix))
						{
							printf("-- parse(%s) returned %i\n", buffer, r);
						}
						else
							goto next;

					}
					p = 0;
					while (p < import_paths_count)
					{
						buffer[0] = 0;
						sprintf(buffer, "%s/%s", import_paths[p], import_path);
						r = parse(buffer, depth + 1, output_sufix, output_prefix);
						if (!r)
						{
							p = 0;
							goto next;
						}
						printf("-- parse(%s) returned %i\n", buffer, r);
						p += 1;
					}

					ERROR("'%s' file not found", import_path);
				}
			}
			else if (EQ(token, "("))
			{
				parenthesis_level += 1;

				if (parenthesis_level == 1 && macro_pattern_begin == -1)
					macro_pattern_begin = fty + 1;
			}
			else if (EQ(token, ")"))
			{
				parenthesis_level -= 1;
				if (!parenthesis_level && macro_pattern_begin && !macro_body_begin)
					macro_pattern_end = fty - 1;
			}
			else if (EQ(token, "{"))
			{
				brace_level += 1;
				if (brace_level == 1 && macro_pattern_begin && !macro_body_begin)
				{
					macro_body_begin = fty + 1;
				}
			}
			else if (EQ(token, "}"))
			{
				brace_level -= 1;
				if (brace_level == 0)
				{
					if (macro_pattern_begin && macro_body_begin)
					{
						macro_body_end 		= fty - 1;
						pattern = strscat(full_token_history, macro_pattern_begin, macro_pattern_end, 0);
						body = strscat(full_token_history, macro_body_begin, macro_body_end, 0);
						printf("Macro pattern[pattern='%s'\n\tbody='%s']\n", pattern, body);
						sprintf(macro_patterns[macro_patterns_count][0], "%s", pattern);
						sprintf(macro_patterns[macro_patterns_count][1], "%s", body);
						macro_patterns_count += 1;	
						is.in_compiler = -1;
						macro_pattern_begin = 0;
						macro_pattern_end = 0;
						macro_body_begin = 0;
						macro_body_end = 0;
					}
					else if (main_begin)
					{
						is.in_compiler = -1;
					}
				}
			}
			else if (import_begin == -1 && (bracket_level || is.quotes))
				import_begin = ty;
		}
		else if (EQ(token, "'") && !is.escaped && !is.quotes &&	is.quote)
			is.quote = 0;
		else if (EQ(token, "\"") && !is.escaped && is.quotes && !is.quote)
		{
			is.quotes = 0;
			is.local_import = 1;
			goto flush_import;
		}
		else if (!EQ(token, "\\") && is.escaped)
			is.escaped 			= 0;
next:
		if (!depth && is.in_compiler)
		{
			if (is.in_compiler > 0)
				compiler[compiler_i++] = token;
			is.in_compiler = 1;
		}
		ty += 1;
		if (is.split)
		{
			is.split = 0;
			token = l;
			goto parse_token;
		}
	}
	if (!depth)
	{
		macros[0] = 0;
		parser[0] = 0;
		p = 0;
		while (p < macro_patterns_count)
		{
			idz[0] = 0;
			sprintf(idz, "macro_%i", p);
			strcat(macros, ft_generate_macro_function
					(idz, macro_patterns[p][0], macro_patterns[p][1]));
			strcat(macros, "\n");
			strcat(parser, ft_generate_macro_parser(idz, macro_patterns[p][0], macro_patterns[p][1]));
			strcat(parser, "\n");
			p += 1;
		}
		p = 0;
		header[0] = 0;
		while (p < compiler_i)
		{
			strcat(header, compiler[p]);
			p += 1;
		}
		buffer[0] = 0;
		sprintf(buffer, "%s/%s%s", output_prefix, path, output_sufix);
		mkpath(buffer);
		outfd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dprintf(outfd, "#include <fcntl.h>					\n\
#include <stdio.h>											\n\
#include <fcntl.h>											\n\
#include <sys/mman.h>										\n\
#include <unistd.h>											\n\
#include <stdarg.h>											\n\
#include <string.h>											\n\
#include <sys/stat.h>										\n\
#include <stdlib.h>											\n\
%s 															\n\
#undef cat													\n\
#define cat(...) cats(__VA_ARGS__, 0)						\n\
															\n\
static char *cats(char *s, ...)								\n\
{															\n\
	char	*o;												\n\
	int		i;												\n\
	va_list	ap;												\n\
															\n\
	va_start(ap, s);										\n\
	o = malloc(8096);										\n\
	*o = 0;													\n\
	while (s)												\n\
	{														\n\
		strcat(o, s);										\n\
		s = va_arg(ap, char *);								\n\
	}														\n\
	va_end(ap);												\n\
	return (o);												\n\
															\n\
}															\n\
															\n\
static void mkpath(const char *dir)							\n\
{															\n\
    char tmp[256];											\n\
    char *p = NULL;											\n\
    size_t len;												\n\
															\n\
    snprintf(tmp, sizeof(tmp),\"%%s\",dir);					\n\
    len = strlen(tmp);										\n\
    if (tmp[len - 1] == '/')								\n\
        tmp[len - 1] = 0;									\n\
    p = tmp + 1;											\n\
	while(*p)												\n\
	{														\n\
        if (*p == '/')										\n\
		{													\n\
            *p = 0;											\n\
            mkdir(tmp, S_IRWXU);							\n\
            *p = '/';										\n\
        }													\n\
		p += 1;												\n\
	}														\n\
}															\n\
%s															\n\
															\n\
int main(int ac, char **av)									\n\
{															\n\
	int		out_fd;											\n\
	int		fd;												\n\
	char	*s;												\n\
	int		i;												\n\
	int		x;												\n\
	char	*o;												\n\
	char	buffer[8096];									\n\
	char	*r;												\n\
	int		success;										\n\
	char	*macro_name;									\n\
															\n\
	if (ac < 3)												\n\
	{														\n\
		printf(\"Usage: ./%%s <source.ç> <dest.c>\\n\", av[0]);\n\
		return (1);											\n\
	}														\n\
	mkpath(av[2]);											\n\
	out_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);\n\
	printf(\"out_file=%%s fd=%%i\\n\", av[2], out_fd);		\n\
	if (out_fd < 0)											\n\
	{														\n\
		printf(\"Error - unable to open output file '%%s'\\n\", av[2]);\n\
	}														\n\
	fd = open(av[1], O_RDONLY);								\n\
	printf(\"source_file=%%s fd=%%i\\n\", av[1], fd);		\n\
	if (fd < 0)												\n\
	{														\n\
		printf(\"Error - unable to open source file '%%s'\\n\", av[1]);\n\
		return (1);											\n\
	}														\n\
	i = lseek(fd, 0, SEEK_END);								\n\
	s = mmap(0, i, PROT_READ, MAP_PRIVATE, fd, 0);			\n\
	i = 0;													\n\
	macro_name = \"marvin\";								\n\
	while (s[i])											\n\
	{														\n\
		 %s													\n\
		goto failure;										\n\
		success:											\n\
			printf(\"1 macro applied [id=%%s i=%%d x=%%d on=%%.*s].\\n\", macro_name, i, x, x, s + i);\n\
			i += x;											\n\
			dprintf(out_fd, \"%%s\", r);					\n\
			goto end;										\n\
		failure:											\n\
			dprintf(out_fd, \"%%c\", s[i]);					\n\
		end:												\n\
		i += 1;												\n\
	}														\n\
	return (0);												\n\
}", header, macros, parser);
			close(outfd);
		}
	p = 0;
	while (p < ty)
	{
		free(token_history[p]);
		p += 1;
	}
	close (fd);
	printf("__________\n");
	return (errors);
}

int			main(int ac, char **av)
{

	int			i;
	int			p;
	int			r;
	int			q;
	int			errors;
	char		error[255];
	const char	*output_prefix;
	const char	*output_sufix;

	if (ac < 2)
	{
		printf ("Usage: %s <file1.c file2.c ...>\n", ac == 1 ? av[0] : "ç");
		return (1);
	}
	errors 			= 0;
	i 				= 1;
	output_prefix	= default_output_prefix;
	output_sufix 	= default_output_sufix;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'I')
			{
				q = 2;
				while (av[i][q])
				{
					import_paths[import_paths_count][q - 2] = av[i][q];
					q += 1;
				}
				import_paths_count += 1;

			}
			else if (av[i][1] == 'o' && !av[i][2])
			{

				if (ac < i)
				{	
					CMD_ERROR("missing output path, default to '%s'", default_output_prefix);
				}
				else
					output_prefix = av[i +  1];
				i += 2;
				continue ;
			}
			else if (av[i][1] == 'e' && !av[i][2])
			{

				if (ac < i)
				{	
					CMD_ERROR("missing output sufix, default to '%s'", default_output_sufix);
				}
				else
					output_sufix = av[i +  1];
				i += 2;
				continue ;
			}
			else
			{
				CMD_ERROR("unknown argument: '%s'", av[i]);
			}
			i += 1;
			continue ;
		}
		else
		{
			q = 0;
			while (av[i][q])
			{
				sources[sources_count][q] = av[i][q];
				q += 1;
			}
			sources[sources_count][q] = 0;
			sources_count += 1;
		}


		i += 1;
	}
	printf("output path\t: %s\n", output_prefix);
	printf("output sufix\t: %s\n", output_sufix);
	p = 0;
	while (p < import_paths_count)
		printf("includes[]\t: %s\n", import_paths[p++]);
	p = 0;
	while (p < sources_count)
	{
		printf("sources[]\t: %s\n", sources[p]);
		r = parse(sources[p], 0, output_sufix, output_prefix);
		if (r == 4242)
		{
			CMD_ERROR("no such file or directory: '%s'", sources[p]);
		}
		else
		{	
			printf("file %s/%s%s generated!\n", output_prefix, sources[p], output_sufix);
		}
		macro_patterns_count = 0;
		references_count = 0;
		p += 1;
	}
	return (errors);
}
