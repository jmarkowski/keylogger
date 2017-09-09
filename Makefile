CC = gcc
CFLAGS  = -c -Wall -O0 -ggdb -std=c11

SRCS = main.c

PROG = keyloggerd

VPATH = src

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

print-%:
# Debug target used for dumping makefile variables.
# usage: make print-VAR
	@echo '$*=$($*)'

clean:
	-rm -rf $(OBJ_DIR)
	-rm -f $(PROG)

.PHONY: all clean
