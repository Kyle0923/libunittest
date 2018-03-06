CC = gcc
AR = ar
ARTIFACT = libunittest.a
INC = .
SRC = unittest.c
OBJ = $(SRC:.c=.o)

all: $(OBJ)
	$(AR) -cr $(ARTIFACT) -I$(INC) $(OBJ)

%.o: %.c
	$(CC) -c $< -I$(INC)

clean:
	rm $(OBJ) $(ARTIFACT)
