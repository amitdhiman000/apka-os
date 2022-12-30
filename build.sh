#!/bin/sh

build=built
c_compiler=gcc
assembler=nasm
linker=ld
c_compiler_opts="-m32 -Wall -O0 -fstrength-reduce -fomit-frame-pointer -nostdinc -fno-builtin  -I./kernel/include  -I./kernel/clib/include -I./kernel/test/include  -fno-strict-aliasing -fno-common -fno-stack-protector"
#opt1="-m32 -Wall -O0 -fstrength-reduce -fomit-frame-pointer -nostdinc -fno-builtin  -I./kernel/include   -fno-strict-aliasing -fno-common -fno-stack-protector"

linker_opts="-m elf_i386"

echo "==================="
echo "..Building Kernel.."
echo "==================="

#remove old files
rm  kernel.bin
rm  os.img
rm -r  $build/*.o


# Build C files

$c_compiler $c_compiler_opts -c  -o $build/kmain.o ./kernel/kmain.c 
$c_compiler $c_compiler_opts -c  -o $build/kconsol.o ./kernel/kconsol.c 
$c_compiler $c_compiler_opts -c  -o $build/kmem.o ./kernel/kmem.c 
$c_compiler $c_compiler_opts -c  -o $build/kio.o ./kernel/kio.c
$c_compiler $c_compiler_opts -c  -o $build/kgdt.o ./kernel/kgdt.c
$c_compiler $c_compiler_opts -c  -o $build/kidt.o ./kernel/kidt.c
$c_compiler $c_compiler_opts -c  -o $build/kisrs.o ./kernel/kisrs.c
$c_compiler $c_compiler_opts -c  -o $build/kirq.o ./kernel/kirq.c
$c_compiler $c_compiler_opts -c  -o $build/kkbd.o ./kernel/kkbd.c
$c_compiler $c_compiler_opts -c  -o $build/kmouse.o ./kernel/kmouse.c
$c_compiler $c_compiler_opts -c  -o $build/kpaging.o ./kernel/kpaging.c
$c_compiler $c_compiler_opts -c  -o $build/ktimer.o ./kernel/ktimer.c
$c_compiler $c_compiler_opts -c  -o $build/system.o ./kernel/system.c

#compile c library
$c_compiler $c_compiler_opts -c  -o $build/ctype.o ./kernel/clib/ctype.c
$c_compiler $c_compiler_opts -c  -o $build/stdio.o ./kernel/clib/stdio.c
$c_compiler $c_compiler_opts -c  -o $build/string.o ./kernel/clib/string.c
$c_compiler $c_compiler_opts -c  -o $build/number.o ./kernel/clib/number.c
#$c_compiler $c_compiler_opts -c  -o $build/video.o ./kernel/clib/video.c

#compile test
$c_compiler $c_compiler_opts -c  -o $build/ktest.o ./kernel/test/ktest.c


# Build ASM files

nasm -f elf ./kernel/asm/loader.asm -o $build/loader.o
nasm -f elf ./kernel/asm/start.asm -o $build/start.o
nasm -f elf ./kernel/asm/registers.asm -o $build/rgisters.o

# link 
$linker $linker_opts -T link.ld  $build/*.o

# to Put on floppy image
cp img/os.img  os.img
#mounting on Floppy image
sudo mkdir /media/test1
sudo mount -o loop os.img /media/test1
sudo cp kernel.bin /media/test1
sudo umount /media/test1
sudo rm -r /media/test1

mkisofs -no-emul-boot -b boot/grub/stage1 -boot-load-seg 0x07C0 -boot-load-size 8 -iso-level 2 -udf -joliet -D -N -relaxed-filenames -o os.iso iso


echo "====================="
echo "..Building Finished.."
echo "====================="
