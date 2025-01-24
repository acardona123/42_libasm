
# 42_libasm


## Sources
[class x86 Assembly guide University of Virginia](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)

[github klaudiagrz assembly presentation](https://github.com/0xAX/asm?tab=readme-ov-file)


## Compilation and debug

### Compilation
`nasm -O0 -f elf64 -g source_file.asm`

If the file contains a main:
	`gcc object_file.o`
else (ie only _start):
	`ld object_file.o [other objects files]`

### gdb debug
Compiling as usual but make sure to use the `-g` flag.

`gdb pgm_name`

`b _start`

`layout asm`

`layout reg`

`set disassembly_flavor intel` <=> `set disassembly-f i`

`run`

`si` to move to the next instruction

To check the content of an addr pointed by a reg: `x/s (char*)$rsi`

