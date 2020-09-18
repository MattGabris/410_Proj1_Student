/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

std::vector<process_stats> &data;


//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	// CLEARS the output vector
	data.clear();

	// Create input stream for input file and open it
	ifstream inStreamFile;
	inStreamFile.open(filename, ios::in);

	// CHECK : is the file open?
	if (!inStreamFile.is_open()){ // if file did not open
		return COULD_NOT_OPEN_FILE; // RETURN because the file was not opened
	}

	// Variable initialization to hold data from input
	std::string curline; // string to hold the line of text to be parsed
	std::string processnum; // string to hold first number
	std::string stime; // string to hold second number
	std::string ctime; // string to hold third number
	std::string itime; // string to hold fourth number

	// Create temp data object from struct to fill with info
	process_stats tempdata;
	std::stringstream ss;

	while(!inStreamFile.eof()){
		std::getline(inStreamFile,curline); // load new line
		ss.str(curline); // convert line stream from input stream to string stream and store in ss

		// CHECK : does the line have any data?
		if (curline.empty()){
			break;
		}

		// CHECK : is ignoreFirstRow true?
		if (ignoreFirstRow){
			ignoreFirstRow = false;
		}
		else {
			// Take data from input and store data
			if (curline.length != 0){
				std::getline(ss, processnum, CHAR_TO_SEARCH_FOR);
			} else { break; }
			if (curline.length != 0){
				std::getline(ss, stime, CHAR_TO_SEARCH_FOR);
			} else { break; }
			if (curline.length != 0){
				std::getline(ss, ctime, CHAR_TO_SEARCH_FOR);
			} else { break; }
			if (curline.length != 0){
				std::getline(ss, itime, CHAR_TO_SEARCH_FOR);
			} else { break; }

			// Convert data (string to int)
			tempdata.process_number = stoi(processnum);
			tempdata.start_time = stoi(stime);
			tempdata.cpu_time = stoi(ctime);
			tempdata.io_time = stoi(itime);

			// Push temp data onto back of data vector
			data.push_back(tempdata);
		}
		// Clear the string stream to prep for new line
		ss.clear();
	}
	// By this point all the data should have been parsed and organized

	// CLOSE file
	inStreamFile.close();

	// CHECK : does the data vector have any data?
	if (data.size() == 0){ // if data vector is empty
		return COULD_NOT_OPEN_FILE;	// RETURN because vector is empty
	}

	return SUCCESS;	// RETURN because file was successfully iterated through and placed into a vector
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return 0;
}


