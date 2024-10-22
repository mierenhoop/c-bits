all: test

.PHONY: test
test: o/test-cobs
	./o/test-cobs

o/test-cobs: cobs.c test/cobs.c | o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) test/cobs.c

o:
	mkdir o

.PHONY: clean
clean:
	rm -rf o
