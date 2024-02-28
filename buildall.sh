#!/usr/bin/bash

CC=clang
AS=as
LD=ld.lld
STRIP=llvm-strip

ARCH=x64
CFLAGS="-Wall -Oz -Iinclude -fno-builtin -fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-stack-protector"

mkdir -p build

$AS -msyntax=intel -mnaked-reg -o build/sys.o src/$ARCH/sys.S
$AS -msyntax=intel -mnaked-reg -o build/crt.o src/$ARCH/crt.S
$CC $CFLAGS -c -o build/io.o src/io.c
$CC $CFLAGS -c -o build/str.o src/str.c
$CC $CFLAGS -c -o build/conv.o src/conv.c

$CC $CFLAGS -c -o build/calc.o examples/calc.c

$LD -o build/calc \
	build/calc.o \
    build/crt.o \
    build/io.o \
	build/sys.o \
	build/str.o \
	build/conv.o

$STRIP -R .comment build/calc
