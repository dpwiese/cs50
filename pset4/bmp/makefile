.PHONY: all clean

all:
	@make copy
	@make resize
	@make whodunit

copy: copy.c makefile
	clang -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o copy copy.c -lcs -lm

resize: resize.c makefile
	clang -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o resize resize.c -lcs -lm

whodunit: whodunit.c makefile
	clang -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o whodunit whodunit.c -lcs -lm

clean:
	@rm -rf copy resize whodunit
