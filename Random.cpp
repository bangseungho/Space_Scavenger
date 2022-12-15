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

//int RandomInt(int first, int second)
//{
//	random_device rd;
//	mt19937 gen(rd());
//	uniform_int_distribution<int> random(first, second);
//
//	return random(gen);
//}
//
//float RandomFloat(float first, float second)
//{
//	random_device rd;
//	mt19937 gen(rd());
//	uniform_real_distribution<float> random(first, second);
//
//	return random(gen);
//}