all:
	cc -g compiler.c get_next_linev2/get_next_line.c get_next_linev2/get_next_line_utils.c -o çc
	./çc -I./ft_cedille_spec/ ft_cedille_spec/spec-mvp.ç -e -compiler.c -o ft_cedille_spec_build

clean:
	rm -rf çc çc.dSYM
