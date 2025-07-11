CC = gcc
CFLAGS = -Wall -g -I.
LDFLAGS =

TARGET_DIR = bin
TARGET = $(TARGET_DIR)/main.out

SRCS = main.c funcoes_filme.c funcoes_aux.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c struct_filme.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET_DIR) $(OBJS)

run: all
	./$(TARGET)
