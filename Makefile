export PATH=$PATH:/opt/devkitpro/devkitARM/bin/
export C_INCLUDE_PATH=$C_INCLUDE_PATH:/opt/devkitpro/libgba/include/

tama.gba: tama.out cpu.o
	arm-none-eabi-objcopy -O binary tama.out tama.gba

cpu.o: tamalib/cpu.c tamalib/hw.c tamalib/tamalib.c
	arm-none-eabi-gcc -Os -mthumb -mthumb-interwork -c tamalib/cpu.c tamalib/hw.c tamalib/tamalib.c

interrupt.o: interrupt.c interrupt.h
	arm-none-eabi-gcc -Os -mthumb-interwork -mthumb -c interrupt.c

tama.out: cpu.o interrupt.o kernel.c hal.c rom.c
	arm-none-eabi-gcc -Os -mthumb -mthumb-interwork -specs=gba_mb.specs -o tama.out interrupt.o cpu.o hw.o tamalib.o kernel.c hal.c rom.c
