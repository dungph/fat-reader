CC=gcc
CFLAGS=-g
test-obj=test-hal

test-hal: test/test-hal.o src/hal.o
	$(CC) -o $@ $^

clean:
	rm ./**/*.o $(test-obj)
