CC=gcc
CFLAGS=-g
test-obj=test-hal test-utils

test-hal: test/test-hal.o src/hal-layer.o src/utils.o
	$(CC) -o $@ $^

test-utils: test/test-utils.o src/utils.o
	$(CC) -o $@ $^

clean:
	rm ./**/*.o $(test-obj)
