export PATH=$PATH:/opt/devkitpro/devkitARM/bin/
export C_INCLUDE_PATH=$C_INCLUDE_PATH:/opt/devkitpro/libgba/include/

tama.gba: cpu.o interrupt.c kernel.c hal.c rom.c
	arm-none-eabi-gcc -O3 -mthumb -mthumb-interwork -specs=gba_mb.specs -o tama.gba interrupt.c cpu.o hw.o tamalib.o kernel.c hal.c rom.c

cpu.o: tamalib/cpu.c tamalib/hw.c tamalib/tamalib.c
	arm-none-eabi-gcc -Os -mthumb -mthumb-interwork -c tamalib/cpu.c tamalib/hw.c tamalib/tamalib.c
