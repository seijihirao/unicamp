file=main
disk=disk.img

all: $(file).o $(file) $(disk)

mount: $(file).c
	arm-eabi-gcc $(file).c -S $(file).s
$(file).o: $(file).s
	arm-eabi-as $(file).s -g -o $(file).o
$(file): $(file).o
	arm-eabi-ld $(file).o -g -o $(file) -Ttext=0x77802000 -Tdata=0x77803000
$(disk): $(file)
	mksd.sh --so /home/specg12-1/mc404/simulador/dummyos.elf --user $(file)
run: $(disk)
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=$(disk)
debug: $(file)
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=$(disk) &
	arm-eabi-gdb $(file)

clean:
	rm -f $(file) $(file).o $(disk)
