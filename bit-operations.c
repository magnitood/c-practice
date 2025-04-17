#include <stdio.h>
#include <stdint.h>

#define SET_BIT(BF, N) (BF |= (unsigned long)(0x0000000000000001 << N))
#define CLR_BIT(BF, N) (BF &= (unsigned long)~(0x0000000000000001 << N))
#define SET_ALL(BF) (BF = 0xFFFFFFFFFFFFFFFF)
#define TOGGLE_BIT(BF, N) (BF ^= (unsigned long)(0x00000000000000001 << N))


int main()
{
	float f = -234.1;
	int bit_f = *((int *) &f); // getting bit representation of float
	TOGGLE_BIT(bit_f, 31); // toggling bit 31 (sign bit of IEEE-754)
	f = *((float *) &bit_f); // putting modified bit back to a float
	printf("%f\n", f);
}
