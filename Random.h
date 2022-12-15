#pragma once
#include <random>
#include <iostream>

using namespace std;

int RandomPlusMinus();

template<typename T>
inline int RandomInt(T first, T second)
{
	int f, s;
	try
	{
		f = int(first);
		s = int(second);
	}
	catch (const std::exception&)
	{
		cout << "RandomInt : Type 에러" << endl;
		exit(1);
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> random(f, s);

	return random(gen);
}

template<typename T>
inline float RandomFloat(T first, T second)
{
	float f, s;
	try
	{
		f = float(first);
		s = float(second);
	}
	catch (const std::exception&)
	{
		cout << "RandomFloat : Type 에러" << endl;
		exit(1);
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> random(f, s);

	return random(gen);
}
