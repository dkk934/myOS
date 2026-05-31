# myOS

A simple hobby operating system project.

## Requirements

Install these tools before building:

- `nasm`
- `i686-elf-gcc`
- `i686-elf-ld`
- `grub-mkrescue`
- `qemu-system-i386`

## Build

Run:

```sh
make
```

This builds the kernel and creates the bootable ISO file:

```sh
myOS.iso
```

## Run

Run the OS in QEMU:

```sh
make run
```

The emulator command used is:

```sh
qemu-system-i386 -cdrom myOS.iso
```

## Clean

Remove build files:

```sh
make clean
```
