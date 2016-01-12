###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash # for ubuntu

###############################################################################

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))
ATT = $(EXE:=.att)
DAT = $(EXE:=.dat)
PNG = $(EXE:=.png)
SVG = $(EXE:=.svg)

###############################################################################

CFLAGS = -Ofast -Wall
CXXFLAGS = $(CFLAGS) -std=c++0x

###############################################################################

default: $(EXE) $(SVG)

all: default $(ATT) $(PNG)

clean:
	$(RM) -rfv $(ATT) $(DAT) $(EXE) $(PNG) $(SVG) core.* *~ 

tools:
	@for i in convert gnuplot g++; do \
		if [ -z $$(which $$i 2> /dev/null) ]; then \
			echo instala $$i; \
			exit 1; \
		fi \
	done

###############################################################################

%.att: %
	objdump -C -d $< -S > $@

%.dat: %
	./$< | tee $@

%.png: %.svg
	convert $< $@

%.svg: %.dat Makefile
	gnuplot <<< "\
		set terminal svg; \
		set output '$@'; \
		set nokey; \
		set grid; \
		set xlabel 'size (B)'; \
		set ylabel 'time (ns/op)'; \
		set logscale x 2; \
		set logscale y; \
		set xtics rotate; \
		set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1k' 1024, '2k' 2048, '4k' 4096, '8k' 8192, '16k' 16384, '32k' 32768, '64k' 65526, '128k' 131072, '256k' 262144, '512k' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864, '128M' 134217728, '256M' 268435456, '512M' 536870912, '1G' 1073741824); \
		plot '$<' u 1:2 w lp lc 1 pt 7"

###############################################################################

.PHONY: all clean default tools
.PRECIOUS: $(DAT) $(PNG) $(SVG)

###############################################################################
