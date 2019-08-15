CFLAGS = -Wall -g
CC = gcc $(CFLAGS)

commando : commando.h commando.o util.o cmd.o cmdcol.o
	$(CC) $^ -o $@

commando.o : commando.c
	$(CC) $^ -c

clean :
	rm commando.o commando cmd.o cmdcol.o test_functions.o test_utils.o util.o

cmd.o : cmd.c
	$(CC) $^ -c

cmdcol.o : cmdcol.c
	$(CC) $^ -c

test : test-functions test-commando

util.o : util.c
	$(CC) $^ -c

test-functions : test_functions
	@printf "Tests for correctness of functions\n"
	./test_functions
	@printf "\n"
	@printf "Valgrind with function tests\n"
	valgrind ./test_functions

test-commando : commando
	@printf "Tests for correctness of commando program\n"
	chmod u+x test_commando.sh standardize_pids
	./test_commando.sh

test_utils.o : test_utils.c test_utils.h
	$(CC) -c $<

test_functions.o : test_functions.c commando.h test_utils.h
	$(CC) -c $<

test_functions : test_functions.o cmd.o cmdcol.o test_utils.o
	$(CC) -o $@ $^

clean-tests :
	rm -f test_functions test-data/*.tmp

fix-tests :
	touch stuff
	touch test-data/stuff/empty
	chmod u+x test-data/stuff/table.sh
