CC=gcc
CFLAGS=-g
test-obj=test-hal test-bs test-fat main

test-hal: test/test-hal.o src/hal.o
	$(CC) -o $@ $^

test-bs: test/test-bs.o src/bs.o src/hal.o
	$(CC) -o $@ $^

test-fat: test/test-fat.o src/fat.o src/bs.o src/hal.o
	$(CC) -o $@ $^

main: src/main.o src/fat.o src/bs.o src/hal.o
	$(CC) -o $@ $^

test: test-hal test-bs test-fat
	./test-hal
	./test-bs
	./test-fat
	
run: main
	./main

clean:
	rm ./**/*.o $(test-obj)
