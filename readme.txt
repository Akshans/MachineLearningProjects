TASK 2 FOLLOW ME README

Instructions: Input data by modifying the input.txt file. Make sure that you leave no spaces after writing each line. 
The program can handle duplicate clip names and tick input commands like "tick 4 0.5" 
Output is printed on console. 

Classes:
pch.cpp - Contains all precompiled headers
Clip.cpp - Class for storing a clip. A clip is an ADT that has a clip name, num ticks associated with it, 
		two actions, and two follow chances. The algorithm for choosing the next clip based on the
		action is also stored here. 
Tick.cpp - Class for storing tick information. This is the total number of ticks in the input. It also stores/handles 
		the follow action numbers that make the output deterministic
Ableton.cpp - Main method. Contains file parsing code, and the loop that decrements ticks and outputs clip names.


***********************************************************************************************************************
MY MAIN LOGIC FOR DEALING WITH FOLLOW ACTION PROBABILITIES

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