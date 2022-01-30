all:
	cc -g compiler.c get_next_linev2/get_next_line.c get_next_linev2/get_next_line_utils.c &&  ./a.out ft_cedille_spec/spec-mvp.ç

clean:
	rm -rf a.out.dSYM a.out
