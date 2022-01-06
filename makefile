CC=gcc -O3 -march=native -mtune=native -std=c99

DEPS = split.h
OBJS = split.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@

main: $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm *.o 