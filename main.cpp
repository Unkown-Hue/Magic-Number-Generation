#include <cstdlib>
#include <thread>
#include <random>
#include <iostream>

#include "init.h"
#include "time.h"
std::mt19937_64 rng(std::random_device{}());


namespace Magic{

	static uint64 GetRandomMagic() {
	    uint64 first = rng() & 0xFFFF;
	    uint64 second = rng() & 0xFFFF;
	    uint64 third = rng() & 0xFFFF;
	    uint64 fourth = rng() & 0xFFFF;
	    second <<= 16;
	    third <<= 32;
	    fourth <<= 48;
	    return first | second | third | fourth;
	}

	template<const int square>
    static void GenerateBlockerCombinationsRook(uint64 *arr, const uint64 *attack_mask) {
        const uint64 *num_bits = &r_bits[square];
        for (uint64 i = 1; i < (1ULL << *num_bits); i++) {
            uint64 blocker = 0ULL;
            int bit_index = 0;
            for (int j = 0; j < 64; ++j) {
                if (*attack_mask & (1ULL << j)) {
                    if (i & (1ULL << bit_index)) {
                        blocker |= (1ULL << j);
                    }
                    ++bit_index;
                }
            }
            arr[i] = blocker;
        }
    }

	template<const int square>
    static void GenerateBlockerCombinationsBishop(uint64 *arr, const uint64 *attack_mask) {
        const uint64 *num_bits = &b_bits[square];
        for (uint64 i = 1; i < (1ULL << *num_bits); i++) {
            uint64 blocker = 0ULL;
            int bit_index = 0;
            for (int j = 0; j < 64; ++j) {
                if (*attack_mask & (1ULL << j)) {
                    if (i & (1ULL << bit_index)) {
                        blocker |= (1ULL << j);
                    }
                    ++bit_index;
                }
            }
            arr[i] = blocker;
        }
    }

	template<bool Bishop, const int square>
    static uint64 GetMagicNumber() {
        if constexpr (Bishop) {
            const uint64 *bishop_mask = &_bishop_mask[square];
            const uint64 *num_bits = &b_bits[square];
			const int *amount = &BishopAmount[square];
			uint64 bishop_blockers[BishopAmount[square]];
			GenerateBlockerCombinationsBishop<square>(bishop_blockers, bishop_mask);
            for (int i = 0; i < 10000000; i++) {
                bool idx_list[MaxBishopSq] = {};
                const uint64 magic = GetRandomMagic();
                //if (magic & 0xFF00000000000000) { makes the program a lot slower up to more than 2x.
                    //continue;
                //}
                bool dupe = false;
                for (int j = 0; j < *amount; j++) {
					uint64 blocker = bishop_blockers[j];
                    const int idx = ((magic * blocker) >> (64 - *num_bits));
                    if (idx_list[idx]) {
                        dupe = true;
                        break;
                    }
                    idx_list[idx] = true;
                }
                if (!dupe) {
                    return magic;
                }
            }
            return 0ULL;
        } else {
            const uint64 *rook_mask = &_rook_mask[square];
            const uint64 *num_bits = &r_bits[square];
			const int *amount = &RookAmount[square];
			uint64 rook_blockers[RookAmount[square]];
			GenerateBlockerCombinationsRook<square>(rook_blockers, rook_mask);
            for (int i = 0; i < 10000000; i++) {
                bool idx_list[MaxRookSq] = {};
                const uint64 magic = GetRandomMagic();
                //if (magic & 0xFF00000000000000) { makes the program a lot slower up to more than 2x.
                    //continue;
                //}
                bool dupe = false;
                for (int j = 0; j < *amount; j++) {
					uint64 blocker = rook_blockers[j];
                    const int idx = ((magic * blocker) >> (64 - *num_bits));
                    if (idx_list[idx]) {
                        dupe = true;
                        break;
                    }
                    idx_list[idx] = true;
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
	std::srand(static_cast<uint32_t>(std::time(nullptr) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ std::random_device{}()));
	{
	    std::cout << "Rook_magic[64] = {" << '\n';
		Timer time;
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 0>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 1>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 2>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 3>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 4>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 5>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 6>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 7>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 8>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 9>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 10>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 11>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 12>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 13>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 14>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 15>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 16>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 17>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 18>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 19>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 20>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 21>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 22>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 23>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 24>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 25>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 26>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 27>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 28>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 29>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 30>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 31>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 32>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 33>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 34>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 35>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 36>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 37>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 38>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 39>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 40>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 41>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 42>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 43>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 44>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 45>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 46>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 47>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 48>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 49>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 50>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 51>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 52>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 53>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 54>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 55>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 56>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 57>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 58>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 59>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 60>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 61>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 62>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 63>() << "ULL\n";
	    std::cout << "};" << '\n';
	
	    std::cout << "Bishop_magic[64] = {" << '\n';
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 0>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 1>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 2>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 3>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 4>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 5>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 6>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 7>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 8>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 9>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 10>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 11>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 12>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 13>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 14>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 15>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 16>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 17>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 18>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 19>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 20>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 21>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 22>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 23>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 24>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 25>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 26>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 27>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 28>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 29>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 30>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 31>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 32>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 33>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 34>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 35>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 36>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 37>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 38>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 39>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 40>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 41>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 42>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 43>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 44>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 45>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 46>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 47>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 48>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 49>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 50>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 51>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 52>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 53>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 54>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 55>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 56>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 57>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 58>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 59>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 60>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 61>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 62>() << "ULL\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 63>() << "ULL\n";
		std::cout << std::dec;
	    std::cout << "};" << '\n';
	
	    std::cout << "Finished." << std::endl;
		}
}
