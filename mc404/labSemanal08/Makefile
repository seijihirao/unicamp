file=mapa
disk=disk.img

all: $(file).s $(file).o $(file) $(disk)

$(file).s: $(file).c
	arm-eabi-gcc $(file).c -S -o $(file).s
$(file).o: $(file).s
	arm-eabi-as $(file).s -g -o $(file).o
	arm-eabi-as dfs.s -g -o dfs.o
$(file): $(file).o
	arm-eabi-ld $(file).o dfs.o -g -o $(file) -Ttext=0x77802000 -Tdata=0x77803000
$(disk): $(file)
	mksd.sh --so /home/specg12-1/mc404/simulador/dummyos.elf --user $(file)
run: $(disk)
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin -g --sd=$(disk)
debug: $(file)
	arm-eabi-gdb $(file)

clean:
	rm -f $(file) $(file).o $(file).s dfs.o $(disk)
