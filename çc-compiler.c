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
Ïúíş"(&H‰½ø÷ÿÿH‰µğ÷ÿÿH‰•è÷ÿÿ‰ä÷ÿÿÇ…Ì÷ÿÿ…À÷ÿÿH‰…¸÷ÿÿ°H³B°÷ÿÿècA°ÿÿ„ ÷ÿÿú<…à÷ÿÿé¾ÿÿÿÇ…Ô÷ÿÿÿÿHcúDŠ9HcìQÊHcÔ÷ÿÿÆ
5@Q÷ÿÿA¨…>è=ƒøÈH‰Á°9…À÷ÿÿ„…Ì÷ÿÿˆ÷ÿÿAÿÿŠ…÷ÿÿ¨…M ”Æ@€öÿ@öÆ…”Æ@€öÿ@öÆ…Æ@€öÿ@öÆ…½`÷ÿÿH5Q:ÿ…`÷ÿÿ„7Hc8H‰½À÷ÿÿHc=~IH528öÿÿ„ „èöÿÿ…ˆEşXEÿƒø9ÁˆMıŠEıˆEşŠEş$¶À]ÃDÿUH‰åHƒìpH!6EèH‰U¨L‰Â‰E¤è¿ñÿÿH}°H5Ú5ƒ}Ğ¨3øH‰uğH‰UèL‰EàL‰EØL‰EĞL‰EÈÇEÄèõ2	‰EÈ‹MÄƒÁ‰MÄH‹EğHcMÄ¾<èU2}ˆH5ä3„EğHcMÄ¾°„	H‹E€H‰EÈ‹MÄƒÁ‰MÄéÿÿÿÇE´M´HcÑ¾ƒù)@•Æ@ˆµ?ÿÿÿŠ…?ÿÿÿ¨…HcÑ¾ƒù>…ÿH5h1hÿÿÿ‰…8ÿÿÿ°	V/(ÿÿÿH‰Âè„ëÿÿH½XÿÿÿH52è¥-Xÿÿÿ„UH‰åHƒì0H‰}ø‰uô‰Uğ‰MìÇEä‰UèéÉÿÿÿ‹EäÁàƒÀHcøè¾,‹Eè;Eğƒú-…­UìH‹ÑHcUà@Š4Hc?EğHcMìH‹È¾Pƒúo…±éT*ÿÿH}ĞH5Z.	Hcy:‹uÀ‰E˜°EMèHiÉÿĞè†&ÇEèH“&HÇ@UH‰åHì ø…@ıÿµ…Ìıÿ°ÿƒÀ‰…PıÿÇ…ìıÿì"Ç…@ıÿ€ıÿf‹…€ıÿfƒàûf‰…€ıÿf‹…€ıÿfƒà÷f‰…€ıÿf‹…€ıÿfƒàïf‰…€ıÿf‹…€ıÿfƒàßf‰…€ıÿf‹…€ıÿfƒà¿f‰…€ıÿf‹…€ıÿf%ÿıf‰…€ıÿf‹…€ıÿf%ÿçfıÿ%ø8fÁàfÁø¿Èƒù¼ıÿH‹• ıÿ°ıÿƒè‰…¼ıÿé1ƒù¿Èƒù ıÿH5Ğ#‹…€ıÿfÁàfÁø¿Èƒùƒ½¼ıÿ…M	H5_!ıÿƒèHcÈH‹¼ÍğÿÿH5ÿ Í ÿf‹€ıÿfáÿçf‰€ıÿ‹…´ıÿƒè‰…´ıÿ‹µhıÿ°ıÿH5ø½ ıÿH5§ƒ½pıÿ&ıÿè„5Æ‰…¬ıÿèäñÿÿ‰…Hıÿƒ½HıÿˆıÿH=âıÿH5_ıÿ‰…¤ıÿ°PıÿƒÀ‰…Pıÿé	ÿ…ıÿƒÀ‰…tıÿƒ½tıÿ…)5şÿ‹…¸ıÿƒè‰…Tıÿ‹µ`ıÿ‹•\ıÿè>æÿÿ1ÉH½ğşÿH‰…ıÿ‹µXıÿ‹•TıÿèæÿÿH=ÿH‹µıÿH‹•ıÿ°‹=%xıÿéfÁàfÁø¿Èƒùÿfƒàıf‰…€ıÿéíÁàfÁø¿Èƒù‰…€ıÿé%øÿÿH‹½ ıÿH5î€ıÿéƒù•´ıÿHcùH‰„ığıÿf‹…€ıÿf%ÿçf¿ÁƒøıÿIÈI‹Lc…LıÿIÁàLÆH‹VH‰Î‰…˜ıÿè
ÚÿÿH½ğıÿH5)°ıÿ„ğıÿıÿ(ıÿH‰…èıÿH‹•„ ÿèFƒÀ‰…LıÿéÙüÿÿÇ…Lıÿ‰•LıÿHcÁH‹”Åğıÿ°„ °ıÿL‹…(ıÿ°ƒ½0ıÿ(ıÿ„Ç…¨ıÿÿè&	éÊÿÿÿÇ…Lıÿ…´ıÿÈHƒ8lÑH9A„•LıÿéàşÿÿÇ è¹ÿÿHƒèÆ„ğşÿÿ‹…àşÿÿÆUH‰åHƒì0‰}ôH‰uèƒ}ôÇèÒMôH‹|ÈXè ‹WLM°L‹õÂèÊ¨ÆA¶ÃH‹H‹EøH‹MØ€<H‹MèH‹	H‹	ŠH‹EğH‹@H‹MèH‹IH‹1H‰÷HƒÇH‰9ˆ0Hƒ}àÿĞƒøÜÿÿh`ÿÿhÍ, char *s, har __end[1024];*__end = 0;
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
		printf("Usage: ./%%s <source.Ã§> <dest.c>\n", av[0]);
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
âLFMerallocstrcmpacro_unctionSsıa°@ `p `'0< G0èhE0KàÌ^Ğl||acro_functionatternsces_count_guardintfcompiler.ct_generate_macro_labelse_macro_parserort_pathsabelsinev2/_line-ef3b16.oline_utils.cs-f6c0a2.okenend 															
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
		printf("Usage: ./%s <source.Ã§> <dest.c>\n", av[0]);
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