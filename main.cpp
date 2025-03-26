#include <cstdlib>
#include <future>
#include <thread>
#include <random>
#include <iostream>
#include <vector>

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
            bool idx_list[amount] = {}; // changed allocation size to only use as much as needed.
            for (int i = 0; i < 10000000; i++) {
                const uint64 magic = GetRandomMagic();
                bool dupe = false;
				bool idx_list[amount] = {}; // changed allocation size to only use as much as needed.
                for (int j = 0; j < amount; j++) {
					const uint64 blocker = BISHOPBLOCKERS[square][j];
                    const int idx = (magic * blocker) >> (64 - num_bits);
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
                bool dupe = false;
                for (int j = 0; j < amount; j++) {
					const uint64 blocker = ROOKBLOCKERS[square][j];
                    const int idx = (magic * blocker) >> (64 - num_bits);
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

template<const bool Bishop, const int square>
void Gen(){
	if constexpr (Bishop){
		BishopMagic[square] = Magic::GetMagicNumber<true, square>();
	}
	else {
		RookMagic[square] = Magic::GetMagicNumber<false, square>();
	}
}

int main() {
	std::srand(static_cast<uint64_t>(std::time(nullptr) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ std::random_device{}()));
	{
		Timer time;
		std::vector<std::future<void>> futures;

		futures.push_back(std::async(std::launch::async, Gen<false, 0>));
		futures.push_back(std::async(std::launch::async, Gen<false, 1>));
		futures.push_back(std::async(std::launch::async, Gen<false, 2>));
		futures.push_back(std::async(std::launch::async, Gen<false, 3>));
		futures.push_back(std::async(std::launch::async, Gen<false, 4>));
		futures.push_back(std::async(std::launch::async, Gen<false, 5>));
		futures.push_back(std::async(std::launch::async, Gen<false, 6>));
		futures.push_back(std::async(std::launch::async, Gen<false, 7>));
		futures.push_back(std::async(std::launch::async, Gen<false, 8>));
		futures.push_back(std::async(std::launch::async, Gen<false, 9>));
		futures.push_back(std::async(std::launch::async, Gen<false, 10>));
		futures.push_back(std::async(std::launch::async, Gen<false, 11>));
		futures.push_back(std::async(std::launch::async, Gen<false, 12>));
		futures.push_back(std::async(std::launch::async, Gen<false, 13>));
		futures.push_back(std::async(std::launch::async, Gen<false, 14>));
		futures.push_back(std::async(std::launch::async, Gen<false, 15>));
		futures.push_back(std::async(std::launch::async, Gen<false, 16>));
		futures.push_back(std::async(std::launch::async, Gen<false, 17>));
		futures.push_back(std::async(std::launch::async, Gen<false, 18>));
		futures.push_back(std::async(std::launch::async, Gen<false, 19>));
		futures.push_back(std::async(std::launch::async, Gen<false, 20>));
		futures.push_back(std::async(std::launch::async, Gen<false, 21>));
		futures.push_back(std::async(std::launch::async, Gen<false, 22>));
		futures.push_back(std::async(std::launch::async, Gen<false, 23>));
		futures.push_back(std::async(std::launch::async, Gen<false, 24>));
		futures.push_back(std::async(std::launch::async, Gen<false, 25>));
		futures.push_back(std::async(std::launch::async, Gen<false, 26>));
		futures.push_back(std::async(std::launch::async, Gen<false, 27>));
		futures.push_back(std::async(std::launch::async, Gen<false, 28>));
		futures.push_back(std::async(std::launch::async, Gen<false, 29>));
		futures.push_back(std::async(std::launch::async, Gen<false, 30>));
		futures.push_back(std::async(std::launch::async, Gen<false, 31>));
		futures.push_back(std::async(std::launch::async, Gen<false, 32>));
		futures.push_back(std::async(std::launch::async, Gen<false, 33>));
		futures.push_back(std::async(std::launch::async, Gen<false, 34>));
		futures.push_back(std::async(std::launch::async, Gen<false, 35>));
		futures.push_back(std::async(std::launch::async, Gen<false, 36>));
		futures.push_back(std::async(std::launch::async, Gen<false, 37>));
		futures.push_back(std::async(std::launch::async, Gen<false, 38>));
		futures.push_back(std::async(std::launch::async, Gen<false, 39>));
		futures.push_back(std::async(std::launch::async, Gen<false, 40>));
		futures.push_back(std::async(std::launch::async, Gen<false, 41>));
		futures.push_back(std::async(std::launch::async, Gen<false, 42>));
		futures.push_back(std::async(std::launch::async, Gen<false, 43>));
		futures.push_back(std::async(std::launch::async, Gen<false, 44>));
		futures.push_back(std::async(std::launch::async, Gen<false, 45>));
		futures.push_back(std::async(std::launch::async, Gen<false, 46>));
		futures.push_back(std::async(std::launch::async, Gen<false, 47>));
		futures.push_back(std::async(std::launch::async, Gen<false, 48>));
		futures.push_back(std::async(std::launch::async, Gen<false, 49>));
		futures.push_back(std::async(std::launch::async, Gen<false, 50>));
		futures.push_back(std::async(std::launch::async, Gen<false, 51>));
		futures.push_back(std::async(std::launch::async, Gen<false, 52>));
		futures.push_back(std::async(std::launch::async, Gen<false, 53>));
		futures.push_back(std::async(std::launch::async, Gen<false, 54>));
		futures.push_back(std::async(std::launch::async, Gen<false, 55>));
		futures.push_back(std::async(std::launch::async, Gen<false, 56>));
		futures.push_back(std::async(std::launch::async, Gen<false, 57>));
		futures.push_back(std::async(std::launch::async, Gen<false, 58>));
		futures.push_back(std::async(std::launch::async, Gen<false, 59>));
		futures.push_back(std::async(std::launch::async, Gen<false, 60>));
		futures.push_back(std::async(std::launch::async, Gen<false, 61>));
		futures.push_back(std::async(std::launch::async, Gen<false, 62>));
		futures.push_back(std::async(std::launch::async, Gen<false, 63>));
		futures.push_back(std::async(std::launch::async, Gen<true, 0>));
		futures.push_back(std::async(std::launch::async, Gen<true, 1>));
		futures.push_back(std::async(std::launch::async, Gen<true, 2>));
		futures.push_back(std::async(std::launch::async, Gen<true, 3>));
		futures.push_back(std::async(std::launch::async, Gen<true, 4>));
		futures.push_back(std::async(std::launch::async, Gen<true, 5>));
		futures.push_back(std::async(std::launch::async, Gen<true, 6>));
		futures.push_back(std::async(std::launch::async, Gen<true, 7>));
		futures.push_back(std::async(std::launch::async, Gen<true, 8>));
		futures.push_back(std::async(std::launch::async, Gen<true, 9>));
		futures.push_back(std::async(std::launch::async, Gen<true, 10>));
		futures.push_back(std::async(std::launch::async, Gen<true, 11>));
		futures.push_back(std::async(std::launch::async, Gen<true, 12>));
		futures.push_back(std::async(std::launch::async, Gen<true, 13>));
		futures.push_back(std::async(std::launch::async, Gen<true, 14>));
		futures.push_back(std::async(std::launch::async, Gen<true, 15>));
		futures.push_back(std::async(std::launch::async, Gen<true, 16>));
		futures.push_back(std::async(std::launch::async, Gen<true, 17>));
		futures.push_back(std::async(std::launch::async, Gen<true, 18>));
		futures.push_back(std::async(std::launch::async, Gen<true, 19>));
		futures.push_back(std::async(std::launch::async, Gen<true, 20>));
		futures.push_back(std::async(std::launch::async, Gen<true, 21>));
		futures.push_back(std::async(std::launch::async, Gen<true, 22>));
		futures.push_back(std::async(std::launch::async, Gen<true, 23>));
		futures.push_back(std::async(std::launch::async, Gen<true, 24>));
		futures.push_back(std::async(std::launch::async, Gen<true, 25>));
		futures.push_back(std::async(std::launch::async, Gen<true, 26>));
		futures.push_back(std::async(std::launch::async, Gen<true, 27>));
		futures.push_back(std::async(std::launch::async, Gen<true, 28>));
		futures.push_back(std::async(std::launch::async, Gen<true, 29>));
		futures.push_back(std::async(std::launch::async, Gen<true, 30>));
		futures.push_back(std::async(std::launch::async, Gen<true, 31>));
		futures.push_back(std::async(std::launch::async, Gen<true, 32>));
		futures.push_back(std::async(std::launch::async, Gen<true, 33>));
		futures.push_back(std::async(std::launch::async, Gen<true, 34>));
		futures.push_back(std::async(std::launch::async, Gen<true, 35>));
		futures.push_back(std::async(std::launch::async, Gen<true, 36>));
		futures.push_back(std::async(std::launch::async, Gen<true, 37>));
		futures.push_back(std::async(std::launch::async, Gen<true, 38>));
		futures.push_back(std::async(std::launch::async, Gen<true, 39>));
		futures.push_back(std::async(std::launch::async, Gen<true, 40>));
		futures.push_back(std::async(std::launch::async, Gen<true, 41>));
		futures.push_back(std::async(std::launch::async, Gen<true, 42>));
		futures.push_back(std::async(std::launch::async, Gen<true, 43>));
		futures.push_back(std::async(std::launch::async, Gen<true, 44>));
		futures.push_back(std::async(std::launch::async, Gen<true, 45>));
		futures.push_back(std::async(std::launch::async, Gen<true, 46>));
		futures.push_back(std::async(std::launch::async, Gen<true, 47>));
		futures.push_back(std::async(std::launch::async, Gen<true, 48>));
		futures.push_back(std::async(std::launch::async, Gen<true, 49>));
		futures.push_back(std::async(std::launch::async, Gen<true, 50>));
		futures.push_back(std::async(std::launch::async, Gen<true, 51>));
		futures.push_back(std::async(std::launch::async, Gen<true, 52>));
		futures.push_back(std::async(std::launch::async, Gen<true, 53>));
		futures.push_back(std::async(std::launch::async, Gen<true, 54>));
		futures.push_back(std::async(std::launch::async, Gen<true, 55>));
		futures.push_back(std::async(std::launch::async, Gen<true, 56>));
		futures.push_back(std::async(std::launch::async, Gen<true, 57>));
		futures.push_back(std::async(std::launch::async, Gen<true, 58>));
		futures.push_back(std::async(std::launch::async, Gen<true, 59>));
		futures.push_back(std::async(std::launch::async, Gen<true, 60>));
		futures.push_back(std::async(std::launch::async, Gen<true, 61>));
		futures.push_back(std::async(std::launch::async, Gen<true, 62>));
		futures.push_back(std::async(std::launch::async, Gen<true, 63>));
		for (auto& future : futures) {
			future.get();
		}
	    std::cout << "Rook_magic[64] = {" << '\n';
		std::cout << "0x" << std::hex << RookMagic[0] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[1] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[2] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[3] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[4] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[5] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[6] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[7] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[8] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[9] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[10] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[11] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[12] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[13] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[14] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[15] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[16] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[17] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[18] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[19] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[20] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[21] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[22] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[23] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[24] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[25] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[26] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[27] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[28] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[29] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[30] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[31] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[32] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[33] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[34] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[35] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[36] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[37] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[38] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[39] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[40] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[41] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[42] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[43] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[44] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[45] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[46] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[47] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[48] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[49] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[50] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[51] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[52] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[53] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[54] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[55] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[56] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[57] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[58] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[59] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[60] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[61] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[62] << "ULL,\n";
		std::cout << "0x" << std::hex << RookMagic[63] << "ULL,\n";
	    std::cout << "};" << '\n';
	
	    std::cout << "Bishop_magic[64] = {" << '\n';
		std::cout << "0x" << std::hex << BishopMagic[0] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[1] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[2] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[3] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[4] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[5] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[6] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[7] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[8] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[9] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[10] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[11] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[12] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[13] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[14] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[15] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[16] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[17] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[18] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[19] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[20] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[21] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[22] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[23] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[24] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[25] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[26] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[27] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[28] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[29] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[30] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[31] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[32] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[33] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[34] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[35] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[36] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[37] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[38] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[39] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[40] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[41] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[42] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[43] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[44] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[45] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[46] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[47] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[48] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[49] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[50] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[51] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[52] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[53] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[54] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[55] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[56] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[57] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[58] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[59] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[60] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[61] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[62] << "ULL,\n";
		std::cout << "0x" << std::hex << BishopMagic[63] << "ULL,\n";
		std::cout << std::dec;
	    std::cout << "};" << '\n';
	
	    std::cout << "Finished." << std::endl;
		}
}
