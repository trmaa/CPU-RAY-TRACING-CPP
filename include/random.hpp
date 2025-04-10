#ifndef RANDO_HPP
#define RANDO_HPP

#include <cstdlib>

inline float rando_float() {
    return rand()/(RAND_MAX+1.f);
}

#endif
