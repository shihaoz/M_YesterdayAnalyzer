#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;


// How-To:
// 1. create a new BatsReader, give it a stock name;
// 2. load any day you want by calling load(day number);
// 3. use get(day number) to get bid/ask/volume vector, or
// output the bid-ask-volume of a day to a path
class BatsReader{
	const string txt = ".txt";
	const string csv = ".csv";


	// BatsReader object -- each BatsReader = 1 stock
	// Usage x1: reads and stores bats data based on Day/Stock
	// Usage x2: get any bids-ask-volume based on Day/Stock
	// Usage x3: outputs the data to file()
	const string sBatsData = "E:/Program_Montec/BatsData/";
	const string sOutputPath = "C:/Users/David/Desktop/Montec/Analysis&Results/BatsReader_Output/";
	string sName;
	// day number --> bid
	unordered_map<int, vector<double>> hBids;
	unordered_map<int, vector<double>> hAsks;
	unordered_map<int, vector<int>> hVolume;
public:

	BatsReader(){}
	BatsReader(string name){
		sName = name;
	}

	// xGS: getter + setter
	string getName() const{ return sName; }
	vector<double> getBids(int dayNum) { return hBids[dayNum]; }
	vector<double> getAsks(int dayNum) { return hAsks[dayNum]; }
	vector<int> getVolume(int dayNum){ return hVolume[dayNum]; }

	void setName(string name) { sName = name; }

	// xLoad: Load in method

	/*
	R: the name is already set; dayNum is a valid day number
	M/E: load the bids-asks-volume of target day into <hBids, hAsks, hVolume>
	*/
	void loadByDay(int dayNum);

	// xOutput: output(app mode) a day vector

	/*
	R: a valid local address; a valid mode(default to out, overwrite mode)
	M/E: write the bid-ask-volume of a target day to <url>
	*/
	void outputByDay(int dayNum, ios::openmode mode = ios::out){
		outputByDay(dayNum, sOutputPath + sName + to_string(dayNum) + csv, mode);		// workaround that you cannot use non-static member as default argument
	}
	void outputByDay(int dayNum, string url, ios::openmode mode = ios::out);

};