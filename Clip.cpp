#include "pch.h"


Clip::Clip()
{
	name = "";
	ticks_to_play = -1;
	follow_chance_one = -1;
	follow_chance_two = -1;
	action_one = "";
	action_two = "";
}

Clip::~Clip()
{

}

//GETTERS
string Clip::getName()
{
	return name;
}
int Clip::getTicksToPlay()
{
	return ticks_to_play;
}
double Clip::getFCOne()
{
	return follow_chance_one;
}
double Clip::getFCTwo()
{
	return follow_chance_two;
}
string Clip::getActionOne()
{
	return action_one;
}
string Clip::getActionTwo()
{
	return action_two;
}

//SETTERS
void Clip::setName(string p_name)
{
	name = p_name;
}
void Clip::setTicksToPlay(string p_ticks_to_play)
{
	ticks_to_play = stoi(p_ticks_to_play);
}
void Clip::setFCOne(string p_follow_chance_one)
{
	follow_chance_one = stod(p_follow_chance_one);
}
void Clip::setFCTwo(string p_follow_chance_two)
{
	follow_chance_two = stod(p_follow_chance_two);
}
void Clip::setActionOne(string p_action_one)
{
	action_one = p_action_one;
}
void Clip::setActionTwo(string p_action_two)
{
	action_two = p_action_two;
}

//OTHER METHODS

/*MY MAIN LOGIC FOR DEALING WITH FOLLOW ACTION PROBABILITIES

I interpreted the instructions as so:

Instructions: " If action1 has Chance set to 1, and action2 has Chance set to 0, action1 will be chosen every time.
				If, on the other hand, action2 has Chance set to 10 in this scenario, action_one will be chosen ten times 
				less often than action_two on average." 

"Follow_action_one Follow_action_two"

"1 0"			action_one has 100% chance of playing action_two has 0%

"1 10"			action_two will be chosen 10 times more than action_one. If we choose 100 times, we can represent as equation x + 10x = 100. 
				Solving for x: x=9.09, which rounds to 9. Thus, action1 is chosen 9/100 times, action2 90/100. We represent this programatically
				as  bool selectAction = (rand() % 100) < 9; selectAction ? action_one : action_2; 
				Or more generally: bool selectAction = (rand() % 100) < x*follow_chance_one; 
							       selectAction ? action_one : action_two;

"2 4"			I interpreted numbers>1 as a rate of being chosen if 1 denotes standard rate of being chosen. Therefore, I precede to solve 
				in the same fashion as the previous case. If we choose 100 times, we can represent as equation 2x + 4x = 100
				Solving for x: x=16.67, which rounds to 17. Thus, action1 is chosen 34/100 times, action2 68/100. We represent this programatically
				as  bool selectAction = (rand() % 100) < 17; selectAction ? action_one : action_2.
				Or more generally: bool selectAction = (rand() % 100) < x*follow_chance_one; 
								   selectAction ? action_one : action_two;

As for the instructions regarding random numbers in a tick, I interpreted it as so:

Instructions: "The ticks line may optionally contain a pair of random numbers (between 0 and 1) for each tick.
				These pairs of random numbers are optionally supplied to ensure that the output can be made deterministic. 
				If these pairs of random numbers are absent in the ticks input, real random numbers should be used instead."

I originally decided to deal with tick random numbers the same way as before. (See above). However, since the goal is a deterministic OUTPUT, 
I thought that the best way to get a nonrandom output is to say that the action corresponded w/the bigger tick number gets selected.
		
*/

//Returns action based off of the current tick program is on
string Clip::pickAction(Tick& t, int tickCounter)
{
	const int randRange = 100;
	int tickIdx = t.getProbArray().size() - tickCounter-1;
	array<float, 2> nullArray{ -1,-1};
	array<float, 2> x = t.getProbArray()[tickIdx];
	//Handle case where tick probabilities are present
	if (x != nullArray)
	{
		if (x[0] >= x[1])
			return action_one;
		else
			return action_two;
		
	}

	//Select action based on rand number from 0-99. If this number <= threshold, action_one is chosen. Else action_two is chosen
	int threshold = setThreshold(follow_chance_one, follow_chance_two, randRange); 
	bool selectAction = (rand() % randRange) < threshold;
	if (selectAction == true)
	{
		return action_one;
	}
	else
	{
		return action_two;
	}
}

// Logic to set threshold used above. 
//I do calculation of threshold as a double, then round that and store as int to get most accurate int
int Clip::setThreshold(double& follow_chance_one, double& follow_chance_two, const int& randRange)
{
	int thresh = 0;
	thresh = round(follow_chance_one*randRange/(follow_chance_one + follow_chance_two));
	return thresh;
}



//return clip vector idx based on action selected
int Clip::setClipArrayIdx(int& i, int clipArrayLength, Tick& t, int& tickCounter)
{
	string action = pickAction(t, tickCounter);
	if (action.compare("none") == 0)
	{
		return i;
	}
	else if (action.compare("any") == 0)
	{
		int randI = rand() % clipArrayLength;
		return randI;
	}
	else if (action.compare("other") == 0)
	{
		int randI = i;
		while (randI == i)
		{
			randI = rand() % clipArrayLength;
		}
		return randI;
	}
	else if (action.compare("next") == 0)
	{
		i = (i + 1) % clipArrayLength;
		return i;
	}
	else if (action.compare("previous") == 0)
	{
		i--;
		if (i < 0) {
			i = clipArrayLength - 1;
		}
		return i;
	}
}


	





