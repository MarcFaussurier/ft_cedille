SRC=./ft_cedille_spec
OUT=./ft_cedille_spec_build

all:
	cc  -g 	compiler.c \
			get_next_linev2/get_next_line.c\
			get_next_linev2/get_next_line_utils.c\
		-o çc
	valgrind ./çc -I$(SRC) $(SRC)/spec-mvp.ç -e -compiler.c -o $(OUT)
	cc -g -I$(SRC) $(OUT)/$(SRC)/spec-mvp.ç-compiler.c -o \
			$(OUT)/$(SRC)/spec-mvp.ç-compiler
#TODO: recompile the compiler using itself ? or re-compile the final file
	valgrind $(OUT)/$(SRC)/spec-mvp.ç-compiler\
			$(SRC)/spec-mvp.ç $(OUT)/$(SRC)/spec-mvp.c
	cc -g -I$(SRC) $(OUT)/$(SRC)/spec-mvp.c -o\
			$(OUT)/$(SRC)/spec-mvp
#TODO: repeat using checksum
clean:
	rm -rf çc çc.dSYM
