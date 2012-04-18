#pragma once

#include <memory>

//Code from Game Coding Complete, 3rd Edition, by Mr.Mike

/* Period parameters */  
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

class Random;
typedef std::shared_ptr<Random> RandomPtr;

class Random
{
public:
	static RandomPtr getSingleton();
	Random();

	unsigned int rand(unsigned int n);
	float rand( );
	void setSeed(unsigned int n);
	unsigned int getSeed();
	void randomize();

protected:
	static RandomPtr singleton;
	unsigned int rseed;
	unsigned int rseed_sp;
	unsigned long mt[CMATH_N];
	int mti;
};
