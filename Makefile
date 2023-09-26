CC=gcc
CFLAGS=-g
test-obj=test-hal test-bs test-fat list-root cat-file

test-hal: test/test-hal.o src/hal.o
	$(CC) -o $@ $^

test-bs: test/test-bs.o src/bs.o src/hal.o
	$(CC) -o $@ $^

test-fat: test/test-fat.o src/fat.o src/bs.o src/hal.o
	$(CC) -o $@ $^

list-root: test/list-root.o src/fat.o src/bs.o src/hal.o
	$(CC) -o $@ $^

cat-file: test/cat-file.o src/fat.o src/bs.o src/hal.o
	$(CC) -o $@ $^

clean:
	rm ./**/*.o $(test-obj)
