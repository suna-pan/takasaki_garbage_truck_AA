CC=cc
CFLAGS=-O

tgt: tgt.c tgt.h
	$(CC) $(CFLAGS) -o tgt tgt.c -lcurses
#	$(CC) $(CFLAGS) -o tgt tgt.c -lcurses -ltermcap
#
clean: 
	rm -f tgt

