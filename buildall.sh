#!/usr/bin/bash

set -e

CC=clang
AS=as
LD=ld.lld
STRIP=llvm-strip

ARCH=x64
CFLAGS="-Wall -Oz -Iinclude -fno-builtin -fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-stack-protector"

mkdir -p out

assemble() {
    $AS -msyntax=intel -mnaked-reg -o out/$(basename $1 .S).o src/$ARCH/$1
}

compile() {
    $CC $CFLAGS -c -o out/$(basename $1 .c).o $1
}

link() {
    $LD -o out/$1 \
        out/$1.o \
        out/crt.o \
        out/io.o \
        out/sys.o \
        out/str.o \
        out/conv.o
}

fullstrip() {
    $STRIP -R .comment -R .note.gnu.property -R .note.gnu.build-id out/$1
}

assemble sys.S
assemble crt.S

compile src/io.c
compile src/str.c
compile src/conv.c
compile examples/cards.c
link cards
fullstrip cards

rm out/*.o
