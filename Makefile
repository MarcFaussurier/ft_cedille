all:
	cc -g compiler.c get_next_linev2/get_next_line.c get_next_linev2/get_next_line_utils.c -o çc
	./çc -I./ft_cedille_spec/ ft_cedille_spec/spec-mvp.ç -e -compiler.c -o ft_cedille_spec_build
	cc -g -I./ft_cedille_spec ft_cedille_spec_build/ft_cedille_spec/spec-mvp.ç-compiler.c -o \
			ft_cedille_spec/spec-mvp.ç-compiler
	./ft_cedille_build/ft_cedille_spec/spec-mvp.ç-compiler ./ft_cedille/spec-mvp.ç -o \
			ft_cedille_spec/spec-mvp.c
	cc ft_cedille_build/ft_cedille_spec/spec-mvp.c -o\
			ft_cedille_spec/spec-mvp.c ft_cedille_build/ft_cedille_spec/spec-mvp
clean:
	rm -rf çc çc.dSYM
