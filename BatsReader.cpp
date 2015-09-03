#include "BatsReader.h"

/*
R: the name is already set; dayNum is a valid day number
M/E: load the bids-asks-volume of target day into <hBids, hAsks, hVolume>
*/

void BatsReader::loadByDay(int dayNum){
	string prefix = sBatsData + "Day " + to_string(dayNum) + "/";
	ifstream infile;
	string filePath;

	for (int i = 1; i < 800; i++){
		// to loop through all interval files starting from interval 1
		filePath = prefix + to_string(i) + txt;
		infile.open(filePath);
		if (infile.is_open() == false){
			cout << sName << "-Day" << to_string(dayNum) << " extracted\n";
			cout << "Size: " << to_string(hVolume[dayNum].size()) << "\n";
			infile.close();
			break;
		}
		
		string holder;	double bid, ask; int volume;

		while (getline(infile, holder, ',')){
			if (holder != sName){// if this is not the line we wanted, dumb rest of the line;
				getline(infile, holder);
				continue;
			}
			// if matched
			// BID, ASK, VOLUME, BID SIZE, ASK SIZE
			getline(infile, holder, ',');	// dump volume
			volume = atoi(holder.c_str());

			getline(infile, holder, ',');	// dump ask size

			getline(infile, holder, ',');	// ask price
			ask = atof(holder.c_str());

			getline(infile, holder, ',');	// dump bid size

			getline(infile, holder, ',');	// bid price
			bid = atof(holder.c_str());

			infile.close();	break;
		}
		hBids[dayNum].push_back(bid);	hAsks[dayNum].push_back(ask);	hVolume[dayNum].push_back(volume);
	}
}


/*
R: a valid local address; a valid mode(default to out, overwrite mode)
M/E: write the bid-ask-volume of a target day to <url>
*/
void BatsReader::outputByDay(int dayNum, string url, ios::openmode mode){
	ofstream outfile;	outfile.open(url, mode);

	if (outfile.is_open() == false){
		cerr << "File at: " << url << "\n cannot be opened";
		return;
	}

	outfile << "Day " << to_string(dayNum) << "-Bid, Ask, Volume\n";
	const int size = hVolume[dayNum].size();
	for (int i = 0; i < size; i++){
		outfile << hBids[dayNum][i] << "," << hAsks[dayNum][i] << "," << hVolume[dayNum][i] << "\n";
	}
	cout << sName << "-Day" << to_string(dayNum) << " outputed\n";
}
