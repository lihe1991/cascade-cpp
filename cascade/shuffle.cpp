#include "shuffle.h"
#include "random.h"
#include <random>

#include <iostream>

using namespace Cascade;

static std::random_device rd;
static std::mt19937 mt(rd());

Shuffle::Shuffle(int nr_bits, bool identity):
    Shuffle(nr_bits, identity, random_uint64())
{
}

Shuffle::Shuffle(int nr_bits, bool identity, uint64_t seed):
    nr_bits(nr_bits),
    identity(identity),
    seed(seed)
{
    // The initial mapping of shuffled key bits to original key bits is one-on-one.
    for (int bit_nr = 0; bit_nr < this->nr_bits; ++bit_nr) {
        this->shuffled_to_orig_map[bit_nr] = bit_nr;
    }
    // Shuffle (except if identity)
    if (!this->identity) {
        mt.seed(this->seed);
        for (int from_bit_nr = 0; from_bit_nr < nr_bits - 1; ++from_bit_nr) {
            std::uniform_int_distribution<int> dist(from_bit_nr + 1, nr_bits - 1);
            int to_bit_nr = dist(mt);
            std::swap(this->shuffled_to_orig_map[from_bit_nr], 
                      this->shuffled_to_orig_map[to_bit_nr]);
        }
    }
    // Compute the reverse mapping of original key bits to shuffled key bits.
    for (int shuffled_bit_nr = 0; shuffled_bit_nr < nr_bits; ++shuffled_bit_nr) {
        int orig_bit_nr = this->shuffled_to_orig_map[shuffled_bit_nr];
        this->orig_to_shuffled_map[orig_bit_nr] = shuffled_bit_nr;
    }

}

Shuffle::~Shuffle()
{
}

uint64_t Shuffle::get_seed() const
{
    return this->seed;
}

int Shuffle::orig_to_shuffle(int orig_bit_nr) const
{
    return this->orig_to_shuffled_map.at(orig_bit_nr);
}

int Shuffle::shuffle_to_orig(int shuffle_bit_nr) const
{
    return this->shuffled_to_orig_map.at(shuffle_bit_nr);
}