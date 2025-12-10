#include "acequia_manager.h"
#include <iostream>
#include <string>
#include <vector>


/*Instructions for this problem:

	The intend of this project is to simulate water management conservation principles in the context of New Mexico

	In this simulation, there exists several Regions (North, South, etc.). Each region class includes both:
	- a given water level
	- a given water need
	- a indicator boolean for if the region is flooded
	- an indicator boolean for if the region is in drought

	With each region, there are given waterSources provided (perhaps a .dat file list each waterSource to  a region) 
	and certain waterSources have canals connected to them to deliver water across regions.

	Given the current state of the region, students wil be asked to utlize the canals that connect regions to
	develop the logic and algorithm for finding a solution. The simulation has a fixed time



	The student solution will be evaluated on the criteria that each region meets the following:
	- a given region is NOT flooded
	- a given region is NOT in drought
	- the region waterNeed does not exceed the region waterLevel 
*/

/*This will be how the solveProblems function is set up. The student may enter their on  */
/*
void solveProblems(AcequiaManager& manager)
{
	//the student can call the members of the canals object such as name of canal. sourceRegion, and destinationRegion
	//This could be helpful in informing the students strategy to solve the problem
	auto canals = manager.getCanals();
	//students may call to get Region and WaterSource objects to inform decisions 


	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{	
		//enter student code here


		manager.nexthour();
	}
}
*/


/*example 2 format

void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==0)
		{
			canals[0]->setFlowRate(1);
			canals[0]->toggleOpen(true);
		}
		else if(manager.hour==1)
		{
			canals[1]->setFlowRate(0.5);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==82)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}
*/

/*example 2*/
/*
void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==1)
		{
			canals[0]->setFlowRate(0.1);
			canals[0]->toggleOpen(true);
			canals[1]->setFlowRate(0.2);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==3)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}
*/


//In this solution, students can make functions that aid in identifying the best course of action for moving
//water resources. They can set conditions that then work on the canal vectors based on the information reported

//This can help in optimizing solutions for dynamic constraints such as weather (rain, or dried up waterSources) and
//make the solution to the problem more abstract, allowing the logic and algorithm to be the sole priority of the student
//while the computation is left for the Acequia Manager

//This would be the perfect opportunity to identify the tools learned from ECE 231L such as:
//data structures (stacks, queues, trees(?)), templates, vector class functions, etc... to aid in the algorithm solution

/*
int findCanal(std::vector<Canal *> canals, std::string region)
{
	int match;
	for(int i = 0; i< canals.size();i++)
	{
		if(canals[i]->sourceRegion->name == region)
		{
			match = i;
		}
	}
	return match;
}

void release(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(true);
	canals[match]->setFlowRate(1);
	return;
}

void close(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(false);
}


void solveProblems(AcequiaManager& manager)
{

	bool check = false;
	auto canals = manager.getCanals();
	auto regions = manager.getRegions();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
		
		if(manager.hour == 0)
		{
			for(int i = 0; i<canals.size(); i++)
			{
				canals[i]->toggleOpen(true);
				canals[i]->setFlowRate(1);
			}
		}

		for(int i =0 ; i<regions.size(); i++)
		{
			if(regions[i]->isFlooded == true)
			{
				//release water from that region by a canal
				release(canals, regions[i]->name);
			}
			else if(regions[i]->isInDrought = true)
			{
				//find canal to move water
				close
			}

			else if(regions[i]->isFlooded == true && regions[i]->isInDrought == true)
			{
				close(canals, regions[i]->name);
			}
		}
		
		manager.nexthour();
	}
}
*/

// Function to find region by it's name (North, South, East).
Region* findRegionByName(const std::vector<Region*>& regions, const std::string& name) {
	for (auto r : regions) { 					// Loop through the regions and
		if (r->name == name) return r; 	// return region name to pointer r.
	}
	return nullptr; // If region is not found.
}

// Funciton to find excess water in region using r pointer established in function above.
double excess(const Region* r) {
	return r->waterLevel - r->waterNeed; 
}

// Function to find how much wafer a region needs/missing.
double deficit(const Region* r) {
	double d = r->waterNeed - r->waterLevel;
	return d > 0 ? d : 0.0; // Condensed if-else expression if d is greater than 0 return the value of d, else return 0.0. ("condition" ? Value_if_true : Value_if_false)
}

// Function to dynamically choose flow rate based on deficit gap.
double chooseFlow(double gap) {
	if (gap > 15) return 1.0; 		// Large deficit.
	if (gap > 5) return 0.85; 	 	// Medium deficit.
	if (gap > 1) return 0.55; 		// small deficit.
	if (gap > 0.001) return 0.1;	// tiny deficit.
	return 0.0; 									// No deficit ignore.
}

void solveProblems(AcequiaManager& manager) {

	// Get regions and canals.
	auto regions = manager.getRegions();
	auto canals = manager.getCanals();

	// Identify region names using findRegionByName funciton and storing them to respective variables.
	Region* north = findRegionByName(regions, "North"); // Store the address of North region in variable north.
	Region* south = findRegionByName(regions, "South"); // Same as above but for south.
	Region* east = findRegionByName(regions, "East"); 	// Repeated for East.

	if (!north || !south || !east) { // Error handling if findRegionByName function doesn't work properly.
		std::cerr << "Error: Could not find expected regions.\n";
		return;
	}

	// Identify canals.
	
	// Create canal variables to be assigned to later.
	Canal* canalA = nullptr;
	Canal* canalB = nullptr;
	Canal* canalC = nullptr;
	Canal* canalD = nullptr;

	for (auto c : canals) { // Iterate through canal pointers and assign them to respective canalA/B/C/D variables.
		if (c->name == "Canal A") canalA = c;  			// Assignment of Canal A to canalA 		// Canal water movement is North -> South.
		else if (c->name == "Canal B") canalB = c; 	// Assignment of Canal B to canalB 		//Canal water movement is South -> East.
		else if (c->name == "Canal C") canalC = c; 	// Assignment of Canal C to canalC 		// Canal water movement is North -> East.
		else if (c->name == "Canal D") canalD = c; 	// Assignment of Canal D to canalC 		// Canal water movement is East -> North.
	}

	if (!canalA || !canalB || !canalC || !canalD) { // Same error handling as north/south/east but for canals.
		std::cerr << "Error: Could not find expected canals.\n";
		return;
	}

	// Main loop to keep code going and automantically move time forward until either problem is solved or max time has been reached.
	while (!manager.isSolved && manager.hour != manager.SimulationMax) {

		// Close canals at the start of each hour.
		for (auto c : canals) {
			c->toggleOpen(false);
			c->setFlowRate(0.0);
		}

		// Calculate region status each hour.
		double northExcess = excess(north);
		double southExcess = excess(south);
		double eastExcess = excess(east);

		double northDeficit = deficit(north);
		double southDeficit = deficit(south);
		double eastDeficit = deficit(east);

		// Have region send water to other regions based on deficit and excess.
	
		// Send water from North (canalA) to South if south needs water and north has excess.
		if ((south->isInDrought || southDeficit > 0) && northExcess > 0) {
			double gap = std::min(northExcess, southDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalA->setFlowRate(flow); 	// Canal A flows North to South.
				canalA->toggleOpen(true);
			}
		}

		// Send water from South (canalB) to East if East needs water and south has excess.
		if ((east->isInDrought || eastDeficit > 0) && southExcess > 0) {
			double gap = std::min(southExcess, eastDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalB->setFlowRate(flow); 	// Canal B flows South to East.
				canalB->toggleOpen(true);
			}
		}

		// Send water from North (canalC) to East if East needs water and North has excess.
		if ((east->isInDrought || eastDeficit > 0) && northExcess > 0) {
			double gap = std::min(northExcess, eastDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalC->setFlowRate(flow); // Canal C flows North to East.
				canalC->toggleOpen(true);
			}
		}

		// Send water from east (canaD) to north if North needs water and east has excess.
		if ((north->isInDrought || northDeficit > 0) && eastExcess > 0) {
			double gap = std::min(eastExcess, northDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalD->setFlowRate(flow); 	// Canal D flows East to North.
				canalD->toggleOpen(true);
			}
		}

		// Send water from east (canalD and canalA) to south if south needs water and east has excess.
		if ((south->isInDrought || southDeficit > 0) && eastExcess > 0) {
			double gap = std::min(eastExcess, southDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalD->setFlowRate(flow); 	// Canal D flows East to North.
				canalD->toggleOpen(true);
				canalA->setFlowRate(flow); 	// Canal A flows North to South.
				canalA->toggleOpen(true);
			}
		}

		// Send water from south (canalB and canalD) to north if north needs water and south has excess.
		if ((north->isInDrought || northDeficit > 0) && southExcess > 0) {
			double gap = std::min(southExcess, northDeficit);
			double flow = chooseFlow(gap);
			if (flow > 0.0) {
				canalB->setFlowRate(flow); 	// Canal B flows South to East.
				canalB->toggleOpen(true);
				canalD->setFlowRate(flow); 	// Canal D flows East to North.
				canalD->toggleOpen(true);
			}
		}

		// Print out the status of regions each hour.
		std::cout << "Hour " << manager.hour << ":\n";
		std::cout << " North: Level: " << north->waterLevel << " Need: " << north->waterNeed << " is Flooded: " 
			<< (north->isFlooded ? "YES" : "NO") << " in Drought: " << (north->isInDrought ? "YES" : "NO") << std::endl;
		std::cout << " South: Level: " << south->waterLevel << " Need: " << south->waterNeed << " is Flooded: " 
			<< (south->isFlooded ? "YES" : "NO") << " in Drought: " << (south->isInDrought ? "YES" : "NO") << std::endl;
		std::cout << " East: Level: " << east->waterLevel << " Need: " << east->waterNeed << " is Flooded: " 
			<< (east->isFlooded ? "YES" : "NO") << " in Drought: " << (east->isInDrought ? "YES" : "NO") << std::endl << std::endl;

		// Call nexthour function to advance simulation time.
		manager.nexthour();
	}
}
