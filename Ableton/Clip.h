#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include "Tick.h"
using namespace std;

class Clip
{
private:
	string name;
	int ticks_to_play;
	double follow_chance_one;
	double follow_chance_two;
	string action_one;
	string action_two;
	string pickAction(Tick& t, int tickCounter);
public:

	Clip();
	~Clip();
	std::string getName();
	int getTicksToPlay();
	double getFCOne();
	double getFCTwo();
	string getActionOne();
	string getActionTwo();
	void setName(string p_name);
	void setTicksToPlay(string p_ticks_to_play);
	void setFCOne(string p_follow_chance_one);
	void setFCTwo(string p_follow_chance_two);
	void setActionOne(string p_action_one);
	void setActionTwo(string p_action_two);
	int setThreshold(double& follow_chance_one, double& follow_chance_two, const int& randRange);
	int setClipArrayIdx(int& i, int clipArrayLength, Tick& t, int& tickCounter);
};

