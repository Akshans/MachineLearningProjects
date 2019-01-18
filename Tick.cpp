#include "pch.h"

Tick::Tick()
{
	numTicks = 0;
}

Tick::~Tick()
{

}

//numTicks handling
int Tick::getNumTicks()
{
	return numTicks;
}
void Tick::setNumTicks(int ticks)
{
	numTicks = numTicks + ticks;
}

//probArray handling
vector<array<float, 2>> Tick::getProbArray()
{
	return probArray;
}

void Tick::setProbArray(array<float, 2> a)
{
	probArray.push_back(a);
}
