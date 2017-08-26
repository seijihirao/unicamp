prog.x: main.o math.o log.o 
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -L /usr/lib64 main.o math.o log.o -lc /usr/lib64/crtn.o -o prog.x

main.s: main.c
	gcc -S main.c -o main.s
math.s: math.c
	gcc -S math.c -o math.s
log.s: log.c
	gcc -S log.c -o log.s

main.o: main.s
	as -o main.o main.s
math.o: math.s
	as -o math.o math.s
log.o: log.s
	as -o log.o log.s

clean: 
	rm -f main.s math.s log.s main.o math.o log.o prog.x
