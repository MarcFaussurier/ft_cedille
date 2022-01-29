- [X] spec https://github.com/MarcFaussurier/ft_cedille_spec 
- [X] parse C code 
- [X] parse macro, main and import syntaxes
- [ ] reccursive analysis in import directives
- [ ] copy everything but main to generate a compiler
- [ ] copy everything but macro in an output string
- [ ] keep replacing output string using macro definitions in the generated compiler
- [ ] add a flag to compile the output string using clang or gcc



$./ç -I$importpath file.ç -o file.ç-compiler.c 
$ cc file.ç-compiler.c -o file.ç-compiler
$ ./file.ç-compiler file.ç -o file.swp
$ if file exists file.swp2 and file.swp == file.swp2 or file.depth > depthmax
	then stop, create a hash lock using $importpath and sources, 
	and create file.c by deleteing macro defs from file.swp
$ cc -I./ -c file.c -o file.o
