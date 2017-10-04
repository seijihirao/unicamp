file=hamming
disk=disk.img

all: $(file).o $(file) $(disk)

$(file).o: $(file).s
	arm-eabi-as $(file).s -o $(file).o
$(file): $(file).o
	arm-eabi-ld $(file).o -o $(file) -Ttext=0x77802000 -Tdata=0x77803000
$(disk): $(file)
	mksd.sh --so /home/specg12-1/mc404/simulador/dummyos.elf --user $(file)
run: $(disk)
	arm-sim --rom=/home/specg12-1/mc404/simulador/dumboot.bin --sd=$(disk)
debug: $(file)
	arm-eabi-gdb $(file)

clean:
	rm -f $(file) $(file).o $(disk)
