#include "random.h"

uint64_t s[4] = {4, 3, 2, 1};

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

void Seed(){
    uint64_t seed = static_cast<uint64_t>(std::time(nullptr) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ std::random_device{}());
    for (int i = 0; i < 4; i++) {
        seed = seed * 6364136223846793005ULL + 1;
        s[i] = seed;
    }
}

uint64_t next() {
	const uint64_t result = rotl(s[0] + s[3], 23) + s[0];
	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rotl(s[3], 45);

	return result;
}

uint64_t splitmax(){
	uint64_t z = next();
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
	z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
	return z ^ (z >> 31);
}
