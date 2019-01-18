// Ableton.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "pch.h"


using namespace std;
int main()
{
	int clipArrayLength = 0;
	vector<Clip> c;
	ifstream inFile("input.txt", ios::in);
	string strOneLine;
	string token;
	Tick t;
	
	while (inFile) //the text file. 
	{
		getline(inFile, strOneLine); //get a line and put it in strOneLine
		stringstream buf(strOneLine); //make the line tokenizable by word
		while (getline(buf, token, ' '))
		{
			//HANDLE CLIP INPUT LINE
			//put clip lineput into a clip class, then onto clip vector
			if (token == "clip") {
				Clip* newClip = new Clip;
				clipArrayLength++;
				getline(buf, token, ' ');
				newClip->setName(token);
				getline(buf, token, ' ');	
				newClip->setTicksToPlay(token);
				getline(buf, token, ' ');	
				newClip->setFCOne(token);
				getline(buf, token, ' ');	
				newClip->setFCTwo(token);
				getline(buf, token, ' ');	
				newClip->setActionOne(token);
				getline(buf, token, ' ');	
				newClip->setActionTwo(token);
				//Put clips in clip vector
				string matchString = newClip->getName();
				//Put clip with duplicate name in vector
				auto it = std::find_if(c.begin(), c.end(), [matchString](Clip &  obj) { return obj.getName() == matchString; });
				if (it != c.end())
				{
					int dupNameIndex = std::distance(c.begin(), it);
					c.at(dupNameIndex) = *newClip;
					clipArrayLength--;
				}
				else
				{
					//Put clip without duplicate name in vector
					c.push_back(*newClip);
				}
					
				
				
			}
			//HANDLE TOKEN INPUT LINE
			if (token == "ticks")
			{
				getline(buf, token, ' ');
				int ticks = stoi(token);
				t.setNumTicks(ticks);
				//handle vanilla tick line e.g. "ticks 2"
				if (buf.eof()) 
				{ 
					for (int tickIdx = 0; tickIdx < ticks; tickIdx++)
					{
						array<float, 2> nullArray;
						nullArray.fill(-1);
						t.setProbArray(nullArray);
					}
				}
				else
				{
					//handle optional tick line e.g. "ticks 2 0.5 0.5 0.0 1.0"
					int eofCounter = 0;
					for (int tickIdx = 0; tickIdx < ticks; tickIdx++)
					{
						array<float, 2> newArray;
						for (int arrayIdx = 0; arrayIdx < 2; arrayIdx++)
						{
							getline(buf, token, ' ');
							float floatToken = stof(token);
							if (buf.eof())
							{ 
								eofCounter++;
								if(eofCounter>1)
									floatToken = (rand() % 10) *0.1; 
							}
							newArray[arrayIdx] = floatToken;
						}
						t.setProbArray(newArray);
					}
				}
			}
		}
			
	}

	/*
	MAIN LOOP. Count down ticks and toggle through clip array*/
	int tickCounter = t.getNumTicks();
	int numTicks = tickCounter;
	int i = 0;
	while (tickCounter > 0)
	{
		int clipCounter = c[i].getTicksToPlay();

		while (tickCounter > 0 && clipCounter > 0)
		{
			tickCounter--;
			clipCounter--;
			cout << c[i].getName() << "\n";
			
			
		}
		//Get new index of clip array based off of action chosen
		i = c[i].setClipArrayIdx(i, clipArrayLength, t, tickCounter);

	}
	

}

