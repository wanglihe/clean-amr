CC = gcc
#CC = clang
MAKEFILENAME = makefile


AMRNBDIR = 3gpp-amrnb/src
AMRWBDIR = 3gpp-amrwb/src

CLAMRDIR = src

CFLAGS = -O3 -Wall -D_POSIX_C_SOURCE=200809L #-DVAD2
CFLAGS_3GPPNB = -std=c89 $(CFLAGS) -I$(AMRNBDIR)
CFLAGS_3GPPWB = -std=c89 $(CFLAGS) -I$(AMRWBDIR)
CFLAGS_CLAMR  = -std=c99 $(CFLAGS) -I$(CLAMRDIR)

LDFLAGS = -lm -lrt

#
# source/object files
#
AMRNB_SRCS=\
	$(AMRNBDIR)/sp_enc.c\
	$(AMRNBDIR)/interf_enc.c\
	$(AMRNBDIR)/sp_dec.c \
	$(AMRNBDIR)/interf_dec.c

AMRWB_SRCS =\
	$(AMRWBDIR)/dec_acelp.c\
	$(AMRWBDIR)/dec_dtx.c\
	$(AMRWBDIR)/dec_gain.c\
	$(AMRWBDIR)/dec_if.c\
	$(AMRWBDIR)/dec_lpc.c\
	$(AMRWBDIR)/dec_main.c\
	$(AMRWBDIR)/dec_rom.c\
	$(AMRWBDIR)/dec_util.c\
	$(AMRWBDIR)/enc_acelp.c\
	$(AMRWBDIR)/enc_dtx.c\
	$(AMRWBDIR)/enc_gain.c\
	$(AMRWBDIR)/enc_if.c\
	$(AMRWBDIR)/enc_lpc.c\
	$(AMRWBDIR)/enc_main.c\
	$(AMRWBDIR)/enc_rom.c\
	$(AMRWBDIR)/enc_util.c\
	$(AMRWBDIR)/if_rom.c

CLAMR_SRCS=\
	$(CLAMRDIR)/sp_enc.c\
	$(CLAMRDIR)/interf_enc.c\
	$(CLAMRDIR)/sp_dec.c\
	$(CLAMRDIR)/interf_dec.c\
	$(CLAMRDIR)/dec_acelp.c\
	$(CLAMRDIR)/dec_dtx.c\
	$(CLAMRDIR)/dec_gain.c\
	$(CLAMRDIR)/dec_if.c\
	$(CLAMRDIR)/dec_lpc.c\
	$(CLAMRDIR)/dec_main.c\
	$(CLAMRDIR)/dec_rom.c\
	$(CLAMRDIR)/dec_util.c\
	$(CLAMRDIR)/enc_acelp.c\
	$(CLAMRDIR)/enc_dtx.c\
	$(CLAMRDIR)/enc_gain.c\
	$(CLAMRDIR)/enc_if.c\
	$(CLAMRDIR)/enc_lpc.c\
	$(CLAMRDIR)/enc_main.c\
	$(CLAMRDIR)/enc_rom.c\
	$(CLAMRDIR)/enc_util.c\
	$(CLAMRDIR)/if_rom.c


AMRNB_OBJS=$(AMRNB_SRCS:.c=.o)
AMRWB_OBJS=$(AMRWB_SRCS:.c=.o)

CLAMR_OBJS=$(CLAMR_SRCS:.c=.o)

ALL_SRCS=$(AMRNB_SRCS) $(AMRWB_SRCS) $(CLAMR_SRCS)
ALL_OBJS=$(AMRNB_OBJS) $(AMRWB_OBJS) $(CLAMR_OBJS)

all: $(ALL_OBJS) c3gnb.o cclnb.o c3gwb.o cclwb.o

checknb: c3gnb cclnb
	./c3gnb
	./cclnb
	md5sum c3gnb.orig cclnb.orig
	md5sum c3gnb.amrnb cclnb.amrnb
	md5sum c3gnb.back cclnb.back

checkwb: c3gwb cclwb
	./c3gwb
	./cclwb
	md5sum c3gwb.orig cclwb.orig
	md5sum c3gwb.amrwb cclwb.amrwb
	md5sum c3gwb.back cclwb.back

check: checknb checkwb

c3gnb: c3gnb.o $(AMRNB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
cclnb: cclnb.o $(CLAMR_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
c3gwb: c3gwb.o $(AMRWB_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
cclwb: cclwb.o $(CLAMR_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

baseline: clnb_baseline clwb_baseline
	@./clnb_baseline
	@./clwb_baseline

clnb_baseline: clnb_baseline.o $(CLAMR_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@
clwb_baseline: clwb_baseline.o $(CLAMR_OBJS)
	$(CC) $^ $(LDFLAGS) -o $@


$(AMRNBDIR)/%.o: $(AMRNBDIR)/%.c
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@

$(CLAMRDIR)/%.o: $(CLAMRDIR)/%.c
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

$(AMRWBDIR)/%.o: $(AMRWBDIR)/%.c
	$(CC) -c $(CFLAGS_3GPPWB) $< -o $@

clean:
	rm -f $(CLAMR_OBJS)
	rm -f cclnb cclwb
	rm -f clnb_baseline clwb_baseline
	rm -f *.orig *.amrnb *.amrwb *.back

cleanall: clean
	rm -f $(ALL_OBJS)
	rm -f c3gnb
	rm -f c3gwb

c3gnb.o: c3gnb.c $(AMRNBDIR)/typedef.h
	$(CC) -c $(CFLAGS_3GPPNB) $< -o $@
cclnb.o: cclnb.c $(CLAMRDIR)/typedef.h
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@
c3gwb.o: c3gwb.c $(AMRWBDIR)/typedef.h
	$(CC) -c $(CFLAGS_3GPPWB) $< -o $@
cclwb.o: cclwb.c $(CLAMRDIR)/typedef.h
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

clnb_baseline.o: clnb_baseline.c $(CLAMRDIR)/typedef.h
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

clwb_baseline.o: clwb_baseline.c $(CLAMRDIR)/typedef.h
	$(CC) -c $(CFLAGS_CLAMR) $< -o $@

