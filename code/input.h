#ifndef INPUT_H
#define INPUT_H

uint16 key_cur;
uint16 key_prev;

#define REG_KEYINPUT  (* (volatile uint32*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

// Polling function
inline void key_poll()
{
    key_prev = key_cur;
    key_cur = ~REG_KEYINPUT & KEY_MASK;
}

// Basic state checks
inline uint32 key_curr_state()            {   return key_cur;          }
inline uint32 key_prev_state()            {   return key_prev;         }
inline uint32 key_is_down(uint32 key)     {   return  key_cur & key;   }
inline uint32 key_is_up(uint32 key)       {   return ~key_cur & key;   }
inline uint32 key_was_down(uint32 key)    {   return  key_cur & key;   }
inline uint32 key_was_up(uint32 key)      {   return ~key_cur & key;   }


#endif
