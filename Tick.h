#pragma once
using namespace std;
#include "pch.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <array>

class Tick
{
private:
	int numTicks;
	vector<array<float, 2>> probArray;
public:
	Tick();
	~Tick();
	int getNumTicks();
	void setNumTicks(int ticks);
	vector<array<float, 2>> getProbArray();
	void setProbArray(array<float, 2> a);
};

