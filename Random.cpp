#include "Random.h"


int RandomPlusMinus()
{
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> random(-1, 2);

		if (random(gen) > 0)
			return -1;
		else
			return 1;
	}
}
