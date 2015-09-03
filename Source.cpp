#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "BatsReader.h"

using namespace std;


void main(){
	BatsReader* BR = new BatsReader("CZR");

	// part xLoad
	BR->loadByDay(4);
	// part xGetSet
	vector<double> holder = BR->getAsks(4);
	holder = BR->getBids(4);
	
	vector<int> holder2;
	holder2 = BR->getVolume(4);
	cout << BR->getName() << "\n";
	// part xOutput

	BR->outputByDay(4);

	delete BR;

	cin.get();
	return;
}