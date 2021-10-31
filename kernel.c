#include <gba.h>
#include "tamalib/tamalib.h"
#include "tamalib/cpu.h"
#include "hal.h"
#include "rom.h"

static int* const TILES = (int*)0x0600c000;
static u16* const LCD_MAP = (u16*)0x06000000; /* 1k */

void setup_vram(void);

void main(void) {
    int i;
    u32_t* cycle_count;
    u32_t next_frame_count=0;

    setup_vram();
    tamalib_register_hal(&tama_hal);
    tamalib_init(g_program, NULL, 1000);
    cpu_set_speed(0);
    cycle_count = cpu_get_state()->tick_counter;
    /* enable interrupts */
    /*REG_IE |= 1;
    REG_IME = 1;*/
    while (1) {
        /* wait for vblank */
        /*SystemCall(5);*/
        /* copy buffer to screen */
        for (i=0; i<256; i++)
            ((u32*)LCD_MAP)[i] = ((u32*)LCD_BUFFER)[i];
        /* */
        next_frame_count += 546;
        /* do some processor stuff */
        for (i=0; i<1000; i++) {
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

    /* enable bg3 */
    REG_DISPCNT = (1<<11) + 2;
}
