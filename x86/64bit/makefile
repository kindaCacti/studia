CC=gcc
ASMBIN=nasm
BUILDDIR=.

all : asm cc link
asm : 
	$(ASMBIN) -o $(BUILDDIR)/func.o -f elf64 -g -l $(BUILDDIR)/func.lst func.asm
cc :
	$(CC) -m64 -c -g -o $(BUILDDIR)/main.o -O0 main.c &> $(BUILDDIR)/errors.txt
link :
	$(CC) -m64 -fno-pie -no-pie -lstdc++ -g -o $(BUILDDIR)/markerFinder $(BUILDDIR)/main.o $(BUILDDIR)/func.o
