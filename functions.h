#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "avl_map.h"
#include "Data.h"

using namespace std;

void printHelp();
bool validCommand(string line);
void evalCommand(string line);
void bootStrap();

void parseCSVfile(avl_map<string, Data>& inventoryMap);
void listInventoryByCategory(string category);
void findInventoryById(string inventoryID);

#endif