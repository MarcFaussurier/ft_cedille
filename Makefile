SRC=./ft_cedille_spec
OUT=./ft_cedille_spec_build

all:
	cp $(SRC)/spec-mvp.ç a.txt
	cc  -g 	compiler.c \
			get_next_linev2/get_next_line.c\
			get_next_linev2/get_next_line_utils.c\
		-o çc
	#TODO::RECCURSIVE MACRO DEFINITIONS
	valgrind ./çc -I$(SRC) $(SRC)/spec-mvp.ç -e -compiler.c -o $(OUT)
	cc -g -I$(SRC) $(OUT)/$(SRC)/spec-mvp.ç-compiler.c -o \
			$(OUT)/$(SRC)/spec-mvp.ç-compiler
#TODO: recompile the compiler using itself ? or re-compile the final file
	valgrind $(OUT)/$(SRC)/spec-mvp.ç-compiler\
			$(SRC)/spec-mvp.ç $(OUT)/$(SRC)/spec-mvp.c
	cp $(OUT)/$(SRC)/spec-mvp.c a.txt
	valgrind $(OUT)/$(SRC)/spec-mvp.ç-compiler\
			a.txt $(OUT)/$(SRC)/spec-mvp.c
	c -g -I$(SRC) $(OUT)/$(SRC)/spec-mvp.c -o\
			$(OUT)/$(SRC)/spec-mvp
	cp $(OUT)/$(SRC)/spec-mvp.c b.txt
	((cmp a.txt b.txt) || (make J) || make)

J:
	echo "same!"

#TODO: repeat using checksum
clean:
	rm -rf çc çc.dSYM
