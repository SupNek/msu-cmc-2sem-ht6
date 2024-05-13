CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

.PHONY: clean all test
clean:
	rm -rf *.o
all: integral
test: integral
#testing intersections and integrals
	./integral -R 1:2:-10:10:0.0001:1.7963
	./integral -R 2:3:0.1:10:0.0001:1.5396
	./integral -R 1:3:0.1:10:0.0001:0.61803
	./integral -I 1:1:10:0.0001:58.5
	./integral -I 2:1:10:0.0001:2472.75
	./integral -I 3:1:10:0.0001:2.3026
integral: integral.o functions.o
	$(CC) $(CFLAGS) -o integral integral.o functions.o $(LDLIBS)
integral.o:
	$(CC) $(CFLAGS) -c integral.c $(LDLIBS)
functions.o:
	nasm -f elf32 functions.asm