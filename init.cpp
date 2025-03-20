#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "init.h"

std::vector<std::vector<uint64>> Rook(64, std::vector<uint64>(4096));
std::vector<std::vector<uint64>> Bishop(64, std::vector<uint64>(512));

void Gen(std::string &Filename, std::vector<std::vector<uint64>> &arr) {
	std::ofstream File(Filename);
	if (!File.is_open()){
		std::cerr << "Cannot open file.";
		return;
	}
	File << "#pragma once\n";
	File << "constexpr unsigned long long " << Filename<<"[64][4096]\n{\n";
	for (int sq = 0; sq < 64; sq++){
		File << "{";
		for (int i = 0; i < arr[sq].size(); i++){
			if (i % 12 == 0 && i != 0){
				File << '\n';
			}
			File << arr[sq][i] << "ULL" << ", ";
		}
		File << "},";
	}
	File << "\n};";
	File.close();
}



    void GenerateBlockerCombinationsRook(std::vector<uint64> &arr, const uint64 &attack_mask, int square) {
        const uint64 num_bits = r_bits[square];
        for (uint64 i = 0; i < (1ULL << num_bits); ++i) {
            uint64 blocker = 0ULL;
            int bit_index = 0;
            for (int j = 0; j < 64; ++j) {
                if (attack_mask & (1ULL << j)) {
                    if (i & (1ULL << bit_index)) {
                        blocker |= (1ULL << j);
                    }
                    ++bit_index;
                }
            }
            arr[i] = blocker;
        }
    }

    void GenerateBlockerCombinationsBishop(std::vector<uint64> &arr, const uint64 &attack_mask, int square) {
        const uint64 num_bits = b_bits[square];
        for (uint64 i = 0; i < (1ULL << num_bits); ++i) {
            uint64 blocker = 0ULL;
            int bit_index = 0;
            for (int j = 0; j < 64; ++j) {
                if (attack_mask & (1ULL << j)) {
                    if (i & (1ULL << bit_index)) {
                        blocker |= (1ULL << j);
                    }
                    ++bit_index;
                }
            }
            arr[i] = blocker;
        }
    }

void init(){
	for (int sq = 0; sq < 64; sq++){
		std::vector<uint64> rook_blockers(RookAmount[sq]);
		uint64 rook_mask = _rook_mask[sq];
		GenerateBlockerCombinationsRook(rook_blockers, rook_mask, sq);
		std::vector<uint64> bishop_blockers(BishopAmount[sq]);
		uint64 bishop_mask = _bishop_mask[sq];
		GenerateBlockerCombinationsBishop(bishop_blockers, bishop_mask, sq);
		Rook[sq] = rook_blockers;
		Bishop[sq] = bishop_blockers;
	}
}

int main(){
	std::string ROOK = "ROOKBLOCKERS.h";
	std::string BISHOP = "BISHOPBLOCKERS.h";
	init();
	Gen(ROOK, Rook);
	Gen(BISHOP, Bishop);
}
