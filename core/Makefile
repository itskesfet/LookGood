CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lncursesw

TARGET = seven5
SRC = $(wildcard cunitext/*.c src/*.c)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
