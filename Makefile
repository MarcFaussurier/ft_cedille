SRC=./ft_cedille_spec
OUT=./build
SOURCES="spec-mvp.ç"
OBJECTS=$(shell echo $(SOURCES) | tr -u '.ç' '.co')
RUN=valgrind --leak-check=full --show-leak-kinds=all
çc=./çc
all:			$(OBJECTS)
compiler:		çc
	cc  -g 	compiler.c \
			get_next_linev2/get_next_line.c\
			get_next_linev2/get_next_line_utils.c\
		-o çc
J:
	cc $(OUT)/$(SRC)/spec-mvp.c -I$(SRC) && ./a.out
%.ce:			$(SRC)/%.ç	compiler
	mkdir -p `dirname $(OUT)/$@`
	touch .a.txt
	cp .a.txt .b.txt
	touch .b.txt
	echo "oka"
	cp -n "$<" "$(OUT)/$@" || echo ""
	$(RUN) $(çc) -I$(SRC) $(OUT)/$@ -e -compiler.c -o ./
	cc -g -I$(SRC) $(OUT)/$@-compiler.c -o \
			$(OUT)/$@-compiler
	$(RUN) $(OUT)/$@-compiler\
			$(OUT)/$@ .a.txt
	cp .a.txt $(OUT)/$@
	((cmp .a.txt .b.txt) || (make $@))
%.co:			%.ce	
	rm .a.txt
	rm .b.txt
	cp $(OUT)/$< $(OUT)/$<.c 
	cc -I$(SRC)  $(OUT)/$<.c  && ./a.out 
	echo "yayy $@"
	rm "$(OUT)/$<"
clean:
	rm -rf çc çc.dSYM
.SUFFIXES:
.PHONY:	compiler çc
