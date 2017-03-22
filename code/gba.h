#ifndef GBA_H
#define GBA_H 1

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

typedef uint16 COLOR;

#define REG_VCOUNT_ADDR 0x04000006
#define REG_VCOUNT      (* (volatile uint16*) REG_VCOUNT_ADDR)

#define MEM_IO          0x04000000
#define REG_DISPCNT     *((volatile uint32*)(MEM_IO))

#define REG_IME_ADDR    0x04000208
#define REG_IME         *((volatile uint16*) REG_IME_ADDR)

#define REG_IE_ADDR     0x04000200
#define REG_IE          *((volatile uint16*) REG_IE_ADDR)

#define MEM_VRAM        0x06000000
#define vid_mem         ((uint16*)MEM_VRAM)

#define REG_DISPSTAT_ADDR 0x04000004
#define REG_DISPSTAT    *((volatile uint16*) REG_DISPSTAT_ADDR)

#define DCNT_MODE0      0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005

#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

#define COL_BLACK   0x0000
#define COL_RED     0x001F
#define COL_LIME    0x03E0
#define COL_YELLOW  0x03FF
#define COL_BLUE    0x7C00
#define COL_MAG     0x7C1F
#define COL_CYAN    0x7FE0
#define COL_WHITE   0x7FFF

inline COLOR RGB15(uint32 red, uint32 green, uint32 blue)
{
    return red | (green<<5) | (blue<<10);
}

inline void vsync()
{
  while (REG_VCOUNT >= 160);
  while (REG_VCOUNT < 160);
}





#endif
