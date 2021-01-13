CC=gcc
CC_OPTS=-Wall -g
PROG_NAME=sotest

sotest: main.o error.o
	${CC} ${CC_OPTS} $^ -o ${PROG_NAME} -ldl
main.o: main.c
	${CC}  ${CC_OPTS}  $^ -c  -o $@
error.o: error.c
	${CC} ${CC_OPTS} $^ -c  -o  $@
clear:
	rm -rf *.o sotest *.so
libs: so_example2.o so_example1.o
	${CC} ${CC_OPTS} -shared -o so_example1.so so_example1.o
	${CC} ${CC_OPTS} -shared -o so_example2.so so_example2.o
so_example_1.o: so_example1.c
	${CC} ${CC_OPTS} -c -fpic $^
so_example_2.o:  so_example2.c
	${CC} ${CC_OPTS} -c -fpic $^