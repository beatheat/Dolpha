#include"Func.h"

#include<math.h>

double Math::sinTable[3600];
double Math::cosTable[3600];
double Math::tanTable[3600];

void Math::CreateTable()
{
	for (int i = 0; i < 3600; i++) {
		float x = (float)i * M_PI / 1800.f;
		sinTable[i] = sin(x);
		cosTable[i] = cos(x);
		tanTable[i] = tan(x);
	}
}

double Math::Sin(float value)
{
	if (value == 0) return 0;

	int idx = (int)(value * 10) % 3600;
	int sign = (0xa0000000 & idx) >> 31;
	idx = 3600 * sign + idx;
	return sinTable[idx];
}


double Math::Cos(float value)
{
	if (value == 0) return 1;

	int idx = (int)(value * 10) % 3600;
	int sign = (0xa0000000 & idx) >> 31;
	idx = 3600 * sign + idx;
	return cosTable[idx];
}

inline double Math::Tan(float value)
{
	if (value == 0) return 0;

	int idx = (int)(value * 10) % 3600;
	int sign = (0xa0000000 & idx) >> 31;
	idx = 3600 * sign + idx;
	return tanTable[idx];
}

float Math::PointToDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

float Math::PointToDirection(float x1, float y1, float x2, float y2)
{
	return atan2(y2 - y1, x2 - x1) * 180 / M_PI;
}

float Math::FastInvSqrt(float value)
{
	float Half = 0.5f * value;
	int i = *(int *)&value;
	i = 0x5f3759df - (i >> 1);// This line hides a LOT of math!
	value = *(float *)&i;
	value = value * (1.5f - Half*value*value);// repeat this statement for a better approximation
	return value;
}

template<typename Out>
void __split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> StringSplit(const std::string &s, char delim) {
	std::vector<std::string> elems;
	__split(s, delim, std::back_inserter(elems));
	return elems;
}
