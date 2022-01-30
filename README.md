- [X] spec https://github.com/MarcFaussurier/ft_cedille_spec 
- [X] parse C code 
- [X] parse macro, main and import syntaxes
- [X] reccursive analysis in import directives
- [x] copy everything but main to generate a compiler
- [ ] copy everything but macro when macro no longer update the code
- [ ] keep replacing output string using macro definitions in the generated compiler
- [ ] add a flag to compile the output string using clang or gcc



$ ./ç -I$importpath file.ç -o file.ç-compiler.c  <br>
$ cc file.ç-compiler.c -o file.ç-compiler <br>
$ ./file.ç-compiler file.ç -o file.swp <br>
$ if file exists file.swp2 and file.swp == file.swp2 or file.depth > depthmax <br>
	then stop, create a hash lock using $importpath and sources, <br>
	and create file.c by deleteing macro defs from file.swp <br>
$ cc -I./ -c file.c -o file.o 
