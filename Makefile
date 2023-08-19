CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm
OBJS = main.o estruturas.o auxiliares.o calcula_intervalo.o  operacoes.o 
CC = gcc

all: main

main: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) -c $(LDFLAGS) $<

estruturas.o: estruturas.c
	$(CC) -c $(LDFLAGS) $<

auxiliares.o: auxiliares.c
	$(CC) -c $(LDFLAGS) $<

calcula_intervalo.o: calcula_intervalo.c
	$(CC) -c $(LDFLAGS) $<

operacoes.o: operacoes.c
	$(CC) -c $(LDFLAGS) $<

clean:
	rm -f $(OBJS)

purge: clean
	rm -f main

check:
	./main < input.txt > output.txt
	diff -w output.txt expected.txt
