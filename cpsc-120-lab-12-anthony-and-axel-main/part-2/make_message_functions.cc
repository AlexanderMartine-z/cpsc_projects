// Alexander Martinez
// CPSC 120-01
// 2022-11-29
// alex_m007@csu.fullerton.edu
// @alex3809
//
// Lab 12-02
// Partners: @ahernandez09
//
// Creates Output Image 

#include "make_message_functions.h"

#include <iomanip>

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  return ((file_name.size() >= extension.size()) &&
          (file_name.compare(file_name.size() - extension.size(),
                             extension.size(), extension) == 0));
}

std::seed_seq rng_seed{1, 2, 3, 4, 5};

RandomNumberGenerator rng_01{0, 1, rng_seed};
RandomNumberGenerator rng_11{-1, 1, rng_seed};
RandomNumberGenerator rng_coin_flip{-1, 1, rng_seed};

double RandomDouble01() { return rng_01.next(); }

double RandomDouble11() { return rng_11.next(); }

bool CoinFlip() { return (rng_coin_flip.next() > 0.0); }
