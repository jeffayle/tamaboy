#include <gba.h>

void interrupt_handler(void) {
    REG_IF = IRQ_VBLANK;
    *(short*)0x3007FF8 |= IRQ_VBLANK;
}
