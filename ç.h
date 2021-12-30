#ifndef FT_CEDILLE_H
# define FT_CEDILLE_H

# define macro_3 void macro3(char *word)
# define _(...)

# define mcpy(x, y) x##y
# define mcpy2(x, y) mcpy(x, y)
# define macro(...) mcpy2(macro_, __LINE__)

#endif
