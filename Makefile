TARGET = diff
CC = gcc
CLIBS = -lm
CFLAGS = -c -Wall

$(TARGET): main.o $(TARGET).o Mathtree.o
	$(CC) $< -o $@

Mathtree.o: MathTree/io/mathio.c MathTree/src/tree.c
	$(CC) $(CFLAGS) $(CLIBS) $< -o $@

$(TARGET).o: src/diff.c
	$(CC) $(CFLAGS) $(CLIBS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) $< -o $@

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o