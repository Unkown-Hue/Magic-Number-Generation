#include <cstdint>
#include <random>
#include <iostream>
#include <cassert>

#include "time.h"
#include "init.h"
#include "BishopBlockers.h"
#include "RookBlockers.h"
#include "random.h"

// macros //
#define GetRandomBits12() (splitmax())
#define GetRandomMagic() (rng() & rng() & rng())
#define BISHOPBLOCKER BISHOPBLOCKERS[square][j]
#define ROOKBLOCKER ROOKBLOCKERS[square][j]
//

std::mt19937_64 rng(GetRandomBits12());

// 32 bit multiplication
#define IDX(magic, mask, bits) (unsigned)((int)mask * (int)magic ^ (int)(mask >> 32) * \
                      (int)(magic >> 32)) >> (32 - bits);

namespace Magic{
    template<bool Bishop, const int square>
    uint64 GetMagicNumber() {
        uint32_t collision_check[4096] = {0};
        uint16_t current_gen = 1;
        if constexpr (Bishop) {
            constexpr uint64 bishop_mask = _bishop_mask[square];
            constexpr uint64 num_bits = 64 - b_bits[square];
            constexpr int amount = BishopAmount[square];
            uint64 magic;
            int idx;
            int i;
            int j;
            int_fast8_t dupe;
            for (i = 0; i < 1000000; i++) {
                magic = GetRandomMagic();
                dupe = false;
                ++current_gen;
                for (j = 0; j < amount; j++) {
                    idx = IDX(magic, BISHOPBLOCKER, b_bits[square]);
                    if (collision_check[idx] == current_gen) {
                        dupe = true;
                        break;
                    }
                    collision_check[idx] = current_gen;
                }
                if (!dupe) {
                    return magic;
                }
            }
            return 0ULL;
        } 
        else {
            constexpr uint64 rook_mask = _rook_mask[square];
            constexpr uint64 num_bits = 64 - r_bits[square];
            constexpr int amount = RookAmount[square];
            uint64 magic;
            int idx;
            int i;
            int j;
            int_fast8_t dupe;
            for (i = 0; i < 1000000; i++) {
                magic = GetRandomMagic();
                dupe = false;
                ++current_gen;
                for (j = 0; j < amount; j++) {
                    idx = IDX(magic, ROOKBLOCKER, r_bits[square]); //
                    if (collision_check[idx] == current_gen) {
                        dupe = true;
                        break;
                    }
                    collision_check[idx] = current_gen;
                }
                if (!dupe) {
                    return magic;
                }
            }
            return 0ULL;
        }
    }
};

int main() {
    Seed();
    {
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
        // seperate rook from bishop
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
