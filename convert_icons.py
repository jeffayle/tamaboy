#!/usr/bin/python3
from PIL import Image

im = Image.open('icons.png')

def get_tile(sx,sy):
    global im
    tdata = []
    next_int = 0
    i = 0

    for y in range(sy,sy+8):
        for x in range(sx,sx+8):
            c = im.getpixel((x,y))[0] >= 128
            next_int |= c<<i
            i += 1
            if i==32:
                tdata.append(next_int)
                next_int = 0
                i = 0
    return tdata

def get_16_tile(sx,sy):
    tiles = []
    for dy in [0,8,16,24]:
        for dx in [0,8,16,24]:
            tiles += get_tile(sx+dx,sy+dy)
    return tiles 

print("int const LCD_ICONS_RAW[256] = {")
for y in [0,32]:
    for x in [0,32,64,96]:
        d = map(hex, get_16_tile(x,y))
        print("    %s,"%(", ".join(d)))
print("};")
