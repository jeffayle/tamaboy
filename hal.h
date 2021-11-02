static int* const TILES = (int*)0x0600c000;
static u16* const LCD_MAP = (u16*)0x06000000; /* 1k */
static u16* const ICONS_MAP = (u16*)0x06000800; /* 256 bytes */

hal_t tama_hal;
u8 LCD_BUFFER[1024];
