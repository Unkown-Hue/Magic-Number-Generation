#include <stdint.h>
#include <cstdint>
#include <thread>
#include <random>
#include <cassert>

extern uint64_t s[4];

uint64_t next();

void Seed();

uint64_t splitmax();

