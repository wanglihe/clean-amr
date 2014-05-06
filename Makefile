CC = gcc
#CC = clang 
MAKEFILENAME = makefile


AMRNBDIR = 3gpp-amrnb/src
AMRWBDIR = 3gpp-amrwb/src

CFLAGS = -O3 -Wall 
CFLAGS_3GPPNB = -std=c89 $(CFLAGS) -I$(AMRNBDIR)

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

c3gnb: c3gnb.o $(AMRNB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(AMRNBDIR)/%.o: $(AMRNBDIR)/%.c
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@

clean:
	rm -f $(AMRNBDIR)/*.o *.o 
	rm -f c3gnb

c3gnb.o: c3gnb.c $(AMRNBDIR)/typedef.h
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@

