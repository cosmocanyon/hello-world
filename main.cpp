#include <iostream>

class Chip8 {

    static constexpr const unsigned int W=64, H=32;
    static constexpr const unsigned int StartRam=0x00, StartProg=0x200, Start660=0x600, EndRam=0xFFF;
    unsigned char Instr[36/2];

    union {
        // Chip-8 has a memory upto 4KB (4096bytes = 0x1000) of RAM.
        unsigned char Mem[0x1000] {0};

        // First half of 1 KB (512bytes = 0x200bytes), reserved simulator internals.
        struct {
            // 8bits
            unsigned char V[16], DelayTimer, SoundTimer, SP, Key[16]; // unsigned char = 255 = 8bits
            unsigned char DispMem[W*H/8]; // in bytes
            unsigned char Font[16*5]; // hexa digit sprites from 1 to F
            // 16bits
            unsigned short I, PC, Stack[16]; 

        };
    };

    // init
    Chip8() {
        // install builtin font
        auto *p = Font;
        for(unsigned n: {
            0xF999F, 0x26227, 0xF1F8F, 0xF1F1F, 0x99F11, 0xF8F1F, 0xF8F9F, 0xF1244,
            0xF9F9F, 0xF9F1F, 0xF9F99, 0xE9E9E, 0xF888F, 0xE999E, 0xF8F8F, 0xF8F88 
        }) {
            for(int a=16; a>=0; a-=4) {
                *p++ = (n >> a) & 0xF;
            }
        }
    }

    ~Chip8();

    void ExecIns() {
        // read a 2-byte long opcode from memory and advance Program Counter(16bit=2bytes).
        unsigned int opcode = Mem[PC & 0xFFF]*0x100 + Mem[PC+1 & 0xFFF];
        PC += 2;

        /*
        nnn or addr - A 12-bit value, the lowest 12 bits of the instruction
        n or nibble - A 4-bit value, the lowest 4 bits of the instruction
        x - A 4-bit value, the lower 4 bits of the high byte of the instruction
        y - A 4-bit value, the upper 4 bits of the low byte of the instruction
        kk or byte - An 8-bit value, the lowest 8 bits of the instruction
        */

        // extract bit fields from opcode instruction.
        unsigned int nnn = (opcode>>0) & 0xFFF;
        unsigned int n = (opcode>>0) & 0xF;
        unsigned int x = (opcode>>8) & 0xF;
        unsigned int y = (opcode>>4) & 0xFFF;
        unsigned int kk = (opcode>>0) & 0xFF;

    }

};

int main(int argc, char *argv[]) {

std::cout << "Ciao!" << std::endl;

unsigned char Font[16*5];
    unsigned char *p = Font;
    for(unsigned n: {
        0xF999F, 0x26227, 0xF1F8F, 0xF1F1F, 0x99F11, 0xF8F1F, 0xF8F9F, 0xF1244,
        0xF9F9F, 0xF9F1F, 0xF9F99, 0xE9E9E, 0xF888F, 0xE999E, 0xF8F8F, 0xF8F88 
    }) {
        for(int a=16; a>=0; a-=4) {
            *p = (n >> a) & 0xF;
            //std::cout << static_cast<unsigned>(*p) << std::endl;
            p++;
            
        }
    }

    for(unsigned n: Font) {
        //std::cout << n << std::endl;
    }

    unsigned char test = Font[20];
    std::cout << (unsigned)test << "\n";
    char c = 'A';  
    printf("%c %d", c, c);
    std::cout << "\n";
    std::cout << 0x011*0x100 << std::endl;

    return 0;
}