#include <cstdint>
#include <cstdlib>
#include <thread>
#include <random>
#include <iostream>
#include <cstring>
#include <cassert>
//#include <bitset> slow idk

#include "time.h"
#include "init.h"
#include "BishopBlockers.h"
#include "RookBlockers.h"

// macros //
#define R1 (uint64)(rand() & 0xFFFF)
#define R2 (uint64)(rand() & 0xFFFF)
#define R3 (uint64)(rand() & 0xFFFF)
#define R4 (uint64)(rand() & 0xFFFF)
#define Rand uint64(R1 | (R2 << 16) | (R3 << 32) | (R4 << 48))
#define GetRandomBits() (Rand & Rand & Rand)
#define GetRandomBits2() (Rand & Rand & Rand ^ (Rand & Rand)) // fastest -> 196000 - 240000 microseconds not very consistent
#define GetRandomBits3() (Rand & Rand | Rand ^ (Rand & Rand))
#define GetRandomBits4() (Rand ^ Rand | Rand & (Rand & Rand))
#define GetRandomBits5() (Rand & Rand ^ (Rand & Rand)) // thrid fastest
#define GetRandomBits6() (Rand & Rand ^ (Rand | (Rand & Rand & Rand))) // second fastest -> 220000 microseconds
#define GetRandomBits7() (Rand & Rand & (Rand ^ (Rand & Rand & Rand))) // god damn slow -> actually 500000 microseconds
#define GetRandomBits8() (Rand ^ Rand | (Rand & (Rand | Rand & Rand))) // slow -> almost 300000 microseconds
#define GetRandomBits9() (Rand ^ Rand ^ (Rand & (Rand | Rand ^ Rand))) // slow -> 250000 microseconds
#define GetRandomBits10() (Rand ^ Rand ^ (Rand & (Rand ^ Rand ^ Rand))) // slow -> 250000 microseconds
#define GetRandomBits11() (Cgen(GetRandomBits2() | GetRandomBits5() ^ GetRandomBits())) // pretty fast -> 192000 -> 225000 more consistent
#define GetRandomMagic() (rng() & rng() & rng())
#define GetRandomMagic2() (GetRandomBits11() & GetRandomBits11() & GetRandomBits11()) // extremely slow -> 2000000
#define GetRandomMagic3() ((rng() & rng() & rng()) | 0xF00000000000000ULL)
#define GetRandomMagic4() ((rng() & rng() ) ^ (rng() ^ 0x02F000000000000ULL))
#define GetRandomMagic5() (GetRandomBits)
#define BISHOPBLOCKER BISHOPBLOCKERS[square][j]
#define ROOKBLOCKER ROOKBLOCKERS[square][j]
#define Count(b) (__builtin_popcountll(b))


// magic candidate generator
inline uint64 Cgen(uint64 num){ 
    uint64 num2 = num ^ 0xffad0c2f;
    uint64 num4 = num2 ^ num ^ (num ^ (num + 0xffed1cad24dfd1c4));
    uint64 num3 = num2 ^ num;
    return num ^ (num2 + (num2 ^ num3) ^ num4);
}

// slower -> std::mt19937_64 rngbase(rand());
// slower -> std::random_device rd;
std::mt19937_64 rng(GetRandomBits5());
// slower -> std::uniform_int_distribution<uint64> dist(0xffff, UINT64_MAX);
// slower -> std::mt19937_64 rng(std::random_device(){});

#define IDX(magic, mask, bits) (unsigned)((int)mask * (int)magic ^ (int)(mask >> 32) * \
                      (int)(magic >> 32)) >> (32 - bits);

namespace Magic{
    template<bool Bishop, const int square>
    uint64 GetMagicNumber() {
        if constexpr (Bishop) {
            constexpr uint64 bishop_mask = _bishop_mask[square];
            constexpr uint64 num_bits = 64 - b_bits[square];
            constexpr int amount = BishopAmount[square];
            uint64 magic;
            int idx;
            int i;
            int j;
            uint8_t idx_list[amount]; // changed allocation size to only use as much as needed.
            int_fast8_t dupe;  
            for (i = 0; i < 10000000; i++) {
                memset(idx_list, 0, amount);
                magic = GetRandomMagic();
                //if (Count((magic * bishop_mask) & 0xFF0000000000000ULL) < 6) continue; dosent matter for the bishop. removing this increases speed -> ~ 155000
                dupe = false;
                for (j = 0; j < amount; j++) {
                    //const uint64 blocker = BISHOPBLOCKERS[square][j];
                    //idx = (magic * BISHOPBLOCKER) >> (num_bits);
                    idx = IDX(magic, BISHOPBLOCKER, b_bits[square]); // 32 bit multiplying instead of 64 bit -> from 200000 to 166000 - 186000
                    if (idx_list[idx]) {
                        dupe = true;
                        break;
                    }
                    idx_list[idx] = true;
                }
                if (!dupe) {
                    //std::cout << std::dec << "  bishop fails: " << i << std::hex << "  ";
                    return magic;
                }
            }
            return 0ULL;
        } else {
            constexpr uint64 rook_mask = _rook_mask[square];
            constexpr uint64 num_bits = 64 - r_bits[square];
            constexpr int amount = RookAmount[square];
            uint64 magic;
            int idx;
            int i;
            int j;
            int_fast8_t dupe;
            //bool idx_list[4096];
            uint8_t idx_list[amount]; // seems faster than putting amount
            //char idx_list[amount];
            //uint64 idx_list[amount];
            for (i = 0; i < 10000000; i++) {
                memset(idx_list, 0, amount);
                magic = GetRandomMagic();
                //if (Count((magic * rook_mask) & 0xff0000000000000ULL) < 6) continue; damn. removing this brought it from -> 150000 to 83000 - 87000                
                dupe = false;
                for (j = 0; j < amount; j++) {
                    //const uint64 blocker = ROOKBLOCKERS[square][j];
                    //idx = (magic * ROOKBLOCKER) >> (num_bits);
                    idx = IDX(magic, ROOKBLOCKER, r_bits[square]); //
                    if (idx_list[idx]) {
                        dupe = true;
                        break;
                    }
                    idx_list[idx] = 1;
                }
                if (!dupe) {
                    //std::cout << std::dec << "  rook fails: " << i << std::hex << "  ";
                    return magic;
                }
            }
            return 0ULL;
        }
    }
};

int main() {
    std::srand(static_cast<uint64_t>(std::time(nullptr) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ std::random_device{}()));
    {
        // printf is slower than using std::cout
        std::cout << "Rook_magic[64] = {" << '\n';
        Timer time;
        std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 0>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 1>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 2>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 3>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 4>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 5>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 6>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 7>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 8>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 9>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 10>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 11>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 12>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 13>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 14>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 15>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 16>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 17>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 18>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 19>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 20>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 21>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 22>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 23>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 24>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 25>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 26>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 27>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 28>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 29>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 30>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 31>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 32>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 33>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 34>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 35>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 36>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 37>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 38>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 39>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 40>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 41>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 42>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 43>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 44>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 45>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 46>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 47>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 48>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 49>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 50>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 51>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 52>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 53>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 54>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 55>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 56>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 57>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 58>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 59>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 60>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 61>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 62>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<false, 63>() << "ULL,\n";
        std::cout << "};" << '\n';
    
        std::cout << "Bishop_magic[64] = {" << '\n';
        std::cout << "0x" << Magic::GetMagicNumber<true, 0>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 1>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 2>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 3>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 4>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 5>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 6>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 7>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 8>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 9>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 10>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 11>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 12>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 13>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 14>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 15>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 16>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 17>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 18>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 19>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 20>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 21>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 22>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 23>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 24>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 25>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 26>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 27>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 28>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 29>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 30>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 31>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 32>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 33>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 34>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 35>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 36>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 37>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 38>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 39>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 40>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 41>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 42>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 43>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 44>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 45>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 46>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 47>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 48>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 49>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 50>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 51>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 52>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 53>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 54>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 55>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 56>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 57>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 58>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 59>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 60>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 61>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 62>() << "ULL,\n";
        std::cout << "0x" << Magic::GetMagicNumber<true, 63>() << "ULL,\n" << std::dec;
        std::cout << "};" << '\n';
    
        std::cout << "Finished." << std::endl;
        }
}
