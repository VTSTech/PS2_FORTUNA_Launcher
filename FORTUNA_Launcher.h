#include <tamtypes.h>
#include <libpad.h>

//** pad.c and pad related functions from wLaunchElf 8d4a0c2

#define PAD_R3_V0 0x010000
#define PAD_R3_V1 0x020000
#define PAD_R3_H0 0x040000
#define PAD_R3_H1 0x080000
#define PAD_L3_V0 0x100000
#define PAD_L3_V1 0x200000
#define PAD_L3_H0 0x400000
#define PAD_L3_H1 0x800000

extern u32 joy_value;
extern u32 new_pad;
int setupPad(void);
int readpad(void);
int readpad_no_KB(void);
int readpad_noRepeat(void);
void waitPadReady(int port, int slot);
void waitAnyPadReady(void);
//** end
