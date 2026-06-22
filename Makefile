CC = gcc
CFLAGS = -Wall -Wextra

SRC = *.c 
TARGET = StockManagement

all: 
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
run:
	./$(TARGET)
clean:
	rm -f $(TARGET)