#include <gba.h>
#include "tamalib/tamalib.h"
#include "tamalib/cpu.h"
#include "hal.h"
#include "rom.h"
#include "interrupt.h"

static int* const TILES = (int*)0x0600c000;
static u16* const LCD_MAP = (u16*)0x06000000; /* 1k */

void setup_vram(void);

void main(void) {
    int i;
    u32_t* cycle_count;
    u32_t next_frame_count=0;
    int next_frame_overflow=0;

    setup_vram();
    tamalib_register_hal(&tama_hal);
    tamalib_init(g_program, NULL, 1000);
    cpu_set_speed(0);
    cycle_count = cpu_get_state()->tick_counter;
    /* enable interrupts */
    REG_IME = 0;
    REG_IE |= 1;
    REG_DISPSTAT |= 8;
    *(int*)0x03007FFC = (int*)&interrupt_handler;
    REG_IME = 1;
    while (1) {
        /* wait for vblank */
        SystemCall(5);
        /* copy buffer to screen */
        for (i=0; i<256; i++)
            ((u32*)LCD_MAP)[i] = ((u32*)LCD_BUFFER)[i];
        /* process buttons */
        i = ~REG_KEYINPUT;
        hw_set_button(BTN_LEFT, (i&KEY_SELECT)?1:0);
        hw_set_button(BTN_MIDDLE, (i&KEY_B)?1:0);
        hw_set_button(BTN_RIGHT, (i&KEY_A)?1:0);
        /* set number of cycles to next frame */
        next_frame_count += 546;
        next_frame_overflow += 0xa;
        if (next_frame_overflow >= 0x10) {
            next_frame_overflow &= 0xf;
            next_frame_count++;
        }
        /* do some processor stuff */
        while (*cycle_count < next_frame_count) {
            tamalib_step();
            tamalib_step();
            tamalib_step();
            tamalib_step();
        }
    }
}

void setup_vram(void) {
    int i;

    /* initialize LCD_BUFFER */
    for (i=0; i<1024; i++)
        LCD_BUFFER[i] = 0;

    /* set up palette */
    BG_PALETTE[0] = 0xffff; /* white */
    BG_PALETTE[1] = 0x0000; /* black */

    /* tile 0 is blank */
    for (i=0; i<64/4; i++)
        TILES[i] = 0;
    /* tile 1 is solid "pixel" */
    for ( ; i<128/4; i++)
        TILES[i] = 0x01010101;

    REG_BG3CNT = (3<<2) | (1<<7) | (0<<8) | (1<<14);
    REG_BG3X = 0;
    REG_BG3Y = -0x1400;
    REG_BG3PA = 0x111;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 0x111;

    /* enable bg3 */
    REG_DISPCNT = (1<<11) + 2;
}
