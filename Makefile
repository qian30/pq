CC = gcc
CFLAGS = -Wall -g -Iinclude  
AR = ar
ARFLAGS = rcs

LIB_NAME = libpq.a
EXEC_NAME = pq
SRC = src/pq.c
OBJ = $(SRC:.c=.o)

all: $(LIB_NAME) $(EXEC_NAME)

$(LIB_NAME): $(OBJ)
	@echo "build library $@"
	$(AR) $(ARFLAGS) $@ $^

$(EXEC_NAME): main.c $(LIB_NAME)
	@echo "build $@"
	$(CC) $(CFLAGS) -o $@ main.c $(LIB_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB_NAME) $(EXEC_NAME)

.PHONY: all clean