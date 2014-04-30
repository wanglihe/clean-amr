CC = gcc
#CC = clang 
MAKEFILENAME = makefile


AMRNBDIR = 3gpp-amrnb/src
AMRWBDIR = 3gpp-amrwb/src

CFLAGS = -std=c99 -O3 -Wall  -I$(AMRNBDIR)

LDFLAGS = -lm

#
# source/object files
#
AMRNB_SRCS=\
	$(AMRNBDIR)/sp_enc.c\
	$(AMRNBDIR)/interf_enc.c\
	$(AMRNBDIR)/sp_dec.c \
	$(AMRNBDIR)/interf_dec.c

AMRWB_SRCS = 

AMRNB_OBJS=$(AMRNB_SRCS:.c=.o)

ALL_SRCS=$(AMRNB_SRCS) $(AMRWB_SRCS)


all: $(AMRNB_OBJS)

check: check.o $(AMRNB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f $(AMRNBDIR)/*.o *.o 

check.o: check.c $(AMRNBDIR)/typedef.h
