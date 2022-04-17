# Compiler flags
CFLAGS=-Wall
# Linker flag
LFLAGS=-lpthread -lm
SOURCES=ao_quadrado.c
EXEC=ao_quadrado.out

default: all

ao_quadrado:
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS) $(LFLAGS)

clean:
	rm spac

all:
ifeq (ls | grep $(EXEC), $(EXEC))
	clean $(CC) -o $(EXEC) $(SOURCES) $(CFLAGS) $(LFLAGS)
else
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS) $(LFLAGS)
endif
