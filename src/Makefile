CC = gcc
#CC = clang 
MAKEFILENAME = makefile

CFLAGS = -std=c99 -O3 -Wall  -I.

LDFLAGS = -lm

#
# source/object files
#
SRCS= sp_enc.c\
      interf_enc.c\
      sp_dec.c \
      interf_dec.c

OBJS=$(SRCS:.c=.o)

all: $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o 
