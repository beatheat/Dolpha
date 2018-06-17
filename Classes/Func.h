#pragma once

#include<string>
#include<sstream>
#include<vector>
#include<iterator>

class Math
{
private:
	static double sinTable[3600];
	static double cosTable[3600];
	static double tanTable[3600];

public:
	static void CreateTable();

	static double Sin(float value);
	static double Cos(float value);
	static double Tan(float value);

	static float FastInvSqrt(float value);
	static float FastSqrt(float value) { return FastInvSqrt(value) * value; };

	static float PointToDistance(float x1, float y1, float x2, float y2);
	static float PointToDirection(float x1, float y1, float x2, float y2);
};


template<typename T>
std::string toString(T n)
{
	std::ostringstream ss;
	ss << n;
	return ss.str();
}

template<typename Out>
void __split(const std::string &s, char delim, Out result);

std::vector<std::string> StringSplit(const std::string &s, char delim);
