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
����"(&H������H������H������������ǅ���������H�������H��B�����cA���������<���������ǅ������Hc�D�9Hc�Q�Hc������
5@Q����A��>�=���H���9�����������������A���������M ��@���@�����@���@����@���@����`���H�5Q:��`����7H�c8H������Hc=~IH�528���� �������E��XE���9���M��E��E��E�$��]�D�UH��H��pH�!6E�H�U�L�E�����H�}�H�5�5�}Ш3�H�u�H�U�L�E�L�E�L�E�L�E��E���2	�EȋMă��M�H�E�HcM��<�U2}�H�5�3�E�HcM����	H�E�H�EȋMă��M������E�M�Hc����)@��@��?�����?�����Hc����>��H�5h1h�����8����	V/(���H������H��X���H�52�-X����UH��H��0H�}��u�U��M��E��U�������E�����Hc��,�E�;E����-��U�H��HcU�@�4Hc?E�HcM�H���P��o����T*��H�}�H�5Z.	Hcy:�u��E��EM�Hi����&�E�H��&H�@UH��H����@��������������P��ǅ����"ǅ@�����f�����f���f�����f�����f���f�����f�����f���f�����f�����f���f�����f�����f��f�����f�����f%��f�����f�����f%��f���%�8�f��f���ȃ����H����������������1���ȃ����H�5�#�����f��f���ȃ�������M	H�5_!����Hc�H������H�5� � �f�����f����f�������������������h�����H�5�����H�5���p��&���5Ɖ�����������H����H�����H�=���H�5_��������P������P���	��������t����t���)5������������T����`����\���>���1�H�����H������X����T������H�=�H����H������=%x���f��f���ȃ��f���f���������f���ȃ�������%���H�����H�5����������Hc�H������f�����f%��f������I�I�Lc�L��I��L�H�VH�Ή�����
���H�����H�5)���������(��H�����H��� ��F����L�������ǅL����L��Hc�H�������� ���L��(�����0��(���ǅ�����&	�����ǅL�������H�8l�H9A��L������������H��Ƅ�����������UH��H��0�}�H�u�}����M�H�|�X� �WL�M�L����ʨ�A��H�H�E�H�M؀<H�M�H�	H�	�H�E�H�@H�M�H�IH�1H��H��H�9�0H�}��Ѓ����h`��h�, char *s, har __end[1024];*__end = 0;
s = 1;
x=i;
							
					while (success)															
					{																		
						if (!(%s))															
						{																	
							macro_name = "%s";											
							success = 0;													
							break ;															
						}																	
						if (%s)																
						{																	
							y += 1;															
							printf("%%s succeed %s %%i!\n", str(%s), i);					
							break ;															
						}																	
						y += 1;																
					}																		
					x += y;																	
			 (success)																			
	{																						
		r = %s(%s);																			
		goto success;																		
	}output sufix	: %s
%s'ror: [0m[1m%s[0m
le not foundnclude <fcntl.h>					
#include <stdio.h>											
#include <fcntl.h>											
#include <sys/mman.h>										
#include <unistd.h>											
#include <stdarg.h>											
#include <string.h>											
#include <sys/stat.h>										
#define str(x) #x											
#include <stdlib.h>											
%s 															
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
															
    snprintf(tmp, sizeof(tmp),"%%s",dir);					
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
%s															
															
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
		printf("Usage: ./%%s <source.ç> <dest.c>\n", av[0]);
		return (1);											
	}														
	mkpath(av[2]);											
	out_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("out_file=%%s fd=%%i\n", av[2], out_fd);		
	if (out_fd < 0)											
	{														
		printf("Error - unable to open output file '%%s'\n", av[2]);
	}														
	fd = open(av[1], O_RDONLY);								
	printf("source_file=%%s fd=%%i\n", av[1], fd);		
	if (fd < 0)												
	{														
		printf("Error - unable to open source file '%%s'\n", av[1]);
		return (1);											
	}														
	i = lseek(fd, 0, SEEK_END);								
	s = mmap(0, i, PROT_READ, MAP_PRIVATE, fd, 0);			
	i = 0;													
	macro_name = "marvin";								
	i_len = strlen(s);										
	while (s[i])											
	{														
		 %s													
		goto failure;										
		success:											
			printf("1 macro applied [id=%%s i=%%d x=%%d on=%%.*s].\n", macro_name,  i, x, x - i, s + i);
			i = x - 1 ;										
			dprintf(out_fd, "%%s", r);					
			if (i >= i_len)									
				break;										
			goto end;										
		failure:											
			dprintf(out_fd, "%%c", s[i]);					
		end:												
		i += 1;												
	}														
	return (0);												
})]} '" 	
�LFMerallocstrcmpacro_unctionSs�a�@ `p `'0< G�0�h�E0K��^�l||acro_functionatternsces_count_guardintfcompiler.ct_generate_macro_labelse_macro_parserort_pathsabelsinev2/_line-ef3b16.oline_utils.cs-f6c0a2.okenend 															
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