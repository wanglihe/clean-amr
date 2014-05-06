CC = gcc
#CC = clang 
MAKEFILENAME = makefile


AMRNBDIR = 3gpp-amrnb/src
AMRWBDIR = 3gpp-amrwb/src

CLAMRDIR = src

CFLAGS = -O3 -Wall
CFLAGS_3GPPNB = -std=c89 $(CFLAGS) -I$(AMRNBDIR)
CFLAGS_CLAMR  = -std=c99 $(CFLAGS) -I$(CLAMRDIR)

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

CLAMR_SRCS=\
    $(CLAMRDIR)/sp_enc.c\
    $(CLAMRDIR)/interf_enc.c\
    $(CLAMRDIR)/sp_dec.c \
    $(CLAMRDIR)/interf_dec.c


AMRNB_OBJS=$(AMRNB_SRCS:.c=.o)
AMRWB_OBJS=$(AMRWB_SRCS:.c=.o)

CLAMR_OBJS=$(CLAMR_SRCS:.c=.o)

ALL_SRCS=$(AMRNB_SRCS) $(AMRWB_SRCS) $(CLAMR_SRCS)
ALL_OBJS=$(AMRNB_OBJS) $(AMRWB_OBJS) $(CLAMR_OBJS)

all: $(ALL_OBJS) c3gnb.o cclnb.o

check: c3gnb cclnb
	./c3gnb
	./cclnb
	md5sum *.orig
	md5sum *.amrnb
	md5sum *.back

c3gnb: c3gnb.o $(AMRNB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
cclnb: cclnb.o $(CLAMR_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@


$(AMRNBDIR)/%.o: $(AMRNBDIR)/%.c
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@

$(CLAMRDIR)/%.o: $(CLAMRDIR)/%.c
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

clean:
	rm -f $(ALL_OBJS)
	rm -f c3gnb
	rm -f cclnb

c3gnb.o: c3gnb.c $(AMRNBDIR)/typedef.h
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@
cclnb.o: cclnb.c $(CLAMRDIR)/typedef.h
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

