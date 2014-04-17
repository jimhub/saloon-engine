/*
 * SaloonHelpers.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: james
 */

#include "SaloonHelpers.h"

string readTextFile(const string& fileName) {

	ifstream file;
	file.open(fileName.c_str());

	string fileText, line;

	if(file.is_open()) {

		while(file.good()) {
			getline(file, line);
			fileText.append(line+"\n");
		}
	}
	else {
		printf("Unable to read file: %s\n", fileName.c_str());
	}

	return fileText;
}
