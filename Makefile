CC = gcc
CFLAGS = -Wall -g -pthread
INCLUDE = -Iinclude

SRC = src/main.c src/scheduler.c src/process.c src/sync.c
OUT = hybrid_scheduler

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)