#include <cstdlib>
#include <thread>
#include <random>
#include <iostream>

#include "time.h"
#include "init.h"
#include "BishopBlockers.h"
#include "RookBlockers.h"

std::mt19937_64 rng(std::random_device{}());

namespace Magic{

    uint64 GetRandomMagic() { // changed number generation.
        return rng() & rng() & rng(); // dosent shift bits anymore, but just gets rng() and & together.
    }

	template<bool Bishop, const int square>
    uint64 GetMagicNumber() {
        if constexpr (Bishop) {
            constexpr uint64 bishop_mask = _bishop_mask[square];
            constexpr uint64 num_bits = b_bits[square];
			constexpr int amount = BishopAmount[square];
            for (int i = 0; i < 10000000; i++) {
                bool idx_list[amount] = {}; // changed allocation size to only use as much as needed.
                const uint64 magic = GetRandomMagic();
                bool dupe = false;
                for (int j = 0; j < amount; j++) {
					const uint64 blocker = BISHOPBLOCKERS[square][j];
                    const int idx = ((magic * blocker) >> (64 - num_bits));
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
            constexpr uint64 rook_mask = _rook_mask[square];
            constexpr uint64 num_bits = r_bits[square];
			constexpr int amount = RookAmount[square];
            for (int i = 0; i < 10000000; i++) {
                bool idx_list[amount] = {}; // changed allocation size to only use as much as needed.
                const uint64 magic = GetRandomMagic();
				
				// I dont think this even works...
				if constexpr (amount == 1024) {
					if (!(magic << 36)){
						continue;
					}
				}
				else if constexpr (amount == 2048) {
					if (!(magic << 42)){
						continue;
					}
				}
				else if constexpr (amount == 4096) {
					if (!(magic << 45)){
						continue;
					}
				}
                bool dupe = false;
                for (int j = 0; j < amount; j++) {
					const uint64 blocker = ROOKBLOCKERS[square][j];
                    const int idx = ((magic * blocker) >> (64 - num_bits));
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
	std::srand(static_cast<uint64_t>(std::time(nullptr) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ std::random_device{}()));
	{
	    std::cout << "Rook_magic[64] = {" << '\n';
		Timer time;
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 0>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 1>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 2>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 3>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 4>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 5>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 6>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 7>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 8>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 9>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 10>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 11>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 12>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 13>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 14>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 15>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 16>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 17>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 18>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 19>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 20>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 21>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 22>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 23>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 24>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 25>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 26>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 27>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 28>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 29>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 30>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 31>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 32>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 33>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 34>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 35>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 36>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 37>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 38>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 39>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 40>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 41>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 42>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 43>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 44>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 45>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 46>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 47>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 48>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 49>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 50>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 51>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 52>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 53>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 54>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 55>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 56>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 57>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 58>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 59>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 60>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 61>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 62>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<false, 63>() << "ULL,\n";
	    std::cout << "};" << '\n';
	
	    std::cout << "Bishop_magic[64] = {" << '\n';
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 0>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 1>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 2>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 3>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 4>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 5>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 6>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 7>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 8>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 9>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 10>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 11>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 12>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 13>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 14>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 15>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 16>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 17>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 18>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 19>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 20>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 21>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 22>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 23>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 24>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 25>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 26>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 27>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 28>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 29>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 30>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 31>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 32>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 33>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 34>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 35>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 36>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 37>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 38>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 39>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 40>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 41>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 42>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 43>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 44>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 45>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 46>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 47>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 48>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 49>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 50>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 51>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 52>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 53>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 54>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 55>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 56>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 57>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 58>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 59>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 60>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 61>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 62>() << "ULL,\n";
		std::cout << "0x" << std::hex << Magic::GetMagicNumber<true, 63>() << "ULL,\n";
		std::cout << std::dec;
	    std::cout << "};" << '\n';
	
	    std::cout << "Finished." << std::endl;
		}
}
