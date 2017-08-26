compile: ${input}.c
	gcc -S ${input}.c -o ${input}.s
assembly: ${input}.s
	as -o ${input}.o ${input}.s
deassembly: ${input}.o
	objdump -D ${input}.o > ${input}.d.s
link: ${inputs}
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -L /usr/lib64 ${inputs} -lc /usr/lib64/crtn.o -o ${output}.x
