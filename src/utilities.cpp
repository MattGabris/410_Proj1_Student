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

std::vector<process_stats> data;



//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	cout << "- - - - - - New loadData() - - - - - -" << endl;
	cout << "for " << filename << endl;


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

		cout << "- - - - - - - - - - - - - -" << endl;
		cout << "Current line: " << curline << endl;

		int count = 0;

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
			if (curline.length() != 0){
				std::getline(ss, processnum, CHAR_TO_SEARCH_FOR);
				const char* processnumcopy = processnum.c_str();
				tempdata.process_number = stringToInt(processnumcopy);
				if (*processnumcopy != '\0'){
					count++;
				}
				cout << "processnum: " << processnum << endl;
			} else { break; }
			if (curline.length() != 0){
				std::getline(ss, stime, CHAR_TO_SEARCH_FOR);
				const char* stimecopy = stime.c_str();
				tempdata.start_time = stringToInt(stimecopy);
				if (*stimecopy != '\0'){
					count++;
				}
				cout << "stime: " << stime << endl;
			} else { break; }
			if (curline.length() != 0){
				std::getline(ss, ctime, CHAR_TO_SEARCH_FOR);
				const char* ctimecopy = ctime.c_str();
				tempdata.cpu_time = stringToInt(ctimecopy);
				if (*ctimecopy != '\0'){
					count++;
				}
				cout << "ctime: " << ctime << endl;
			} else { break; }
			if (curline.length() != 0){
				std::getline(ss, itime, CHAR_TO_SEARCH_FOR);
				const char* itimecopy = itime.c_str();
				tempdata.io_time = stringToInt(itimecopy);
				if (*itimecopy != '\0'){
					count++;
				}
				cout << "itime: " << itime << endl;
			} else { break; }


			// Convert data (string to int)
//			tempdata.process_number = stringToInt(processnumcopy);
//			tempdata.start_time = stoi(stimecopy);
//			tempdata.cpu_time = stoi(ctimecopy);
//			tempdata.io_time = stoi(itimecopy);

			// Push temp data onto back of data vector
			if (count == 4){
				data.push_back(tempdata);
			}
			cout << "data vector size: " << data.size() << endl;
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

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	std::vector<process_stats> tempVec;

	switch(mySortOrder){
	case CPU_TIME: // Sort wih respect to CPU_TIME
		// -1 means unitialized
		for (int i = 0; i < data.size(); i++){ // the index of the new vector
			int min = -1;
			int minIndex = -1;
			for (int j = 0; j < data.size(); j++){ // the index checking the current lowest
				if (min == -1) {
					min = data[j].cpu_time;
					minIndex = j;
				}
				else if (data[j].cpu_time < min and data[j].cpu_time != -1) {
					minIndex = j;
				}
			}
			tempVec.push_back(data[minIndex]);
		}
		data = tempVec;
		break;

	case PROCESS_NUMBER: // Sort wih respect to PROCESS_NUMBER
		// -1 means unitialized
		for (int i = 0; i < data.size(); i++){ // the index of the new vector
			int min = -1;
			int minIndex = -1;
			for (int j = 0; j < data.size(); j++){ // the index checking the current lowest
				if (min == -1) {
					min = data[j].process_number;
					minIndex = j;
				}
				else if (data[j].process_number < min and data[j].process_number != -1) {
					minIndex = j;
				}
			}
			tempVec.push_back(data[minIndex]);
		}
		data = tempVec;
		break;

	case START_TIME: // Sort wih respect to START_TIME
		// -1 means unitialized
		for (int i = 0; i < data.size(); i++){ // the index of the new vector
			int min = -1;
			int minIndex = -1;
			for (int j = 0; j < data.size(); j++){ // the index checking the current lowest
				if (min == -1) {
					min = data[j].start_time;
					minIndex = j;
				}
				else if (data[j].start_time < min and data[j].start_time != -1) {
					minIndex = j;
				}
			}
			tempVec.push_back(data[minIndex]);
		}
		data = tempVec;
		break;

	case IO_TIME: // Sort wih respect to IO_TIME
	// -1 means unitialized
		for (int i = 0; i < data.size(); i++){ // the index of the new vector
			int min = -1;
			int minIndex = -1;
			for (int j = 0; j < data.size(); j++){ // the index checking the current lowest
				if (min == -1) {
					min = data[j].io_time;
					minIndex = j;
				}
				else if (data[j].io_time < min and data[j].io_time != -1) {
					minIndex = j;
				}
			}
			tempVec.push_back(data[minIndex]);
		}
		data = tempVec;
		break;
	}
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats myFirst;

	cout << "- - - - - - New getNext() - - - - - -" << endl;

	myFirst.process_number = data[0].process_number;
	myFirst.start_time = data[0].start_time;
	myFirst.cpu_time = data[0].cpu_time;
	myFirst.io_time = data[0].io_time;

	for (int i = 1; i < data.size(); i++) {
		data[i-1] = data[i];
	}
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return data.size();
}


