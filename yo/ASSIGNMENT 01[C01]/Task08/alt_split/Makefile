CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra
OBJS    = input.o tariff.o report.o

billing_split.out: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c billing8.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.out all_in_one.c
