cd src/
nasm -felf32 ./Bootloader/boot.asm -o ./boot.o
i686-elf-gcc -ffreestanding -O2 -Wall -Wextra -c ./Kernel/kernel.c -o kernel.o
i686-elf-gcc -T ../linker.ld -o ../estrogen.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
cd ..



if grub-file --is-x86-multiboot estrogen.bin; then
    echo "Operating system is multiboot"
    mv estrogen.bin ./isodir/boot/
    grub-mkrescue -o estrogen.iso isodir
else
    echo "Operating system is not multiboot"
fi



qemu-system-x86_64 -cdrom estrogen.iso

cd src/
rm boot.o
rm kernel.o