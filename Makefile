TARGET = diff
CC = gcc
CLIBS = -lm
CFLAGS = -Wall

$(TARGET): main.o $(TARGET).o tree.o
	$(CC) main.o $(TARGET).o tree.o $(CLIBS) -o $(TARGET)

$(TARGET).o: src/diff.c
	$(CC) $(CFLAGS) -c $< -o $@

tree.o: MathTree/src/mathtree.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o