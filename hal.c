#include <gba.h>
#include "tamalib/tamalib.h"
#include "hal_types.h"
#include "hal.h"
static u16* const LCD_MAP = (u16*)0x06000000; /* 1k */

static void do_nothing(void) {
    return;
}

static timestamp_t get_timestamp(void) {
    return 0;
}
static bool_t is_log_enabled(log_level_t type) {
    return 0;
}

static void set_lcd_matrix(u8_t x, u8_t y, bool_t val) {
    int index;
    val = val ? 1 : 0;
    index = y*32 + x;
    LCD_BUFFER[index] = val;
}
static void set_lcd_icon(u8_t icon, bool_t val) {

}

static void set_frequency(u32_t freq) {
    short const freq_table[] = {2016,2008,2000,1992,1984,1968,1951,1936};
    int n = freq_table[freq];
    REG_SOUND1CNT_X = n | 1<<15;
}
static void play_frequency(bool_t en) {
    if (en) REG_SOUNDCNT_L=0x1177;
    else REG_SOUNDCNT_L=0x0077;
}

hal_t tama_hal = {
    .get_timestamp = get_timestamp,
    .is_log_enabled = is_log_enabled,
    .set_lcd_matrix = set_lcd_matrix,
    .set_lcd_icon = set_lcd_icon,
    .set_frequency = set_frequency,
    .play_frequency = play_frequency,

    .malloc = do_nothing,
    .free = do_nothing,
    .halt = do_nothing,
    .log = do_nothing,
    .sleep_until = do_nothing,
    .update_screen = do_nothing,
    .handler = do_nothing
};
