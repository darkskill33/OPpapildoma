#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Mylib.h"

bool isPunctuation(char c); //Checking if char is puctuation
bool compareFrequency(const pair<string, int>& a, const pair<string, int>& b); // Sort in descending order of frequency
void ReadWriteFrequency(const string& inputFilePath, const string& outputFilePath); //Finds word frequency and exports it to the file
void FindURL(const string& inputFilePath, const string& outputFilePath); //Finds URL and exports it to the file


#endif