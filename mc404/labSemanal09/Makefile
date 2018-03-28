file=motors
disk=disk.img

all: $(file).o $(file) $(disk)

$(file).o: $(file).s
	arm-eabi-as $(file).s -o $(file).o
$(file): $(file).o
	arm-eabi-ld $(file).o -o $(file) -Ttext=0x77802000 -Tdata=0x77803000
$(disk): $(file)
	mksd.sh --so /home/specg12-1/mc404/simulador/simulador_player/bin/knrl --user $(file)
run: $(disk)
	armsim_player --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=$(disk)
gdb: $(file)
	arm-eabi-gdb $(file)

clean:
	rm -f $(file) $(file).o $(disk)
