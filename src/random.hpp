#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>

inline float random_float() {
	return rand()/(RAND_MAX+1.f);
}

#endif
