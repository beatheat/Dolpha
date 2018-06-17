#pragma once


class Random
{
private:
	unsigned long ulState[16];
	unsigned long ulSeed;
	unsigned int iIndex;

public:
	static Random rand;

	Random();

	Random(const unsigned long seed);

	unsigned long Next();
	float NextFloat();

	static unsigned long NextInt(int min, int max);
	static unsigned long NextInt(int max);

	unsigned long GetSeed() const;
	void SetSeed(unsigned long seed);
	void ResetSeed();
};
