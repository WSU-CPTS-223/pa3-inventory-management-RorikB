#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "avl_map.h"
#include "Data.h"
#include "functions.h"

using namespace std;  

int main(int argc, char const *argv[])
{
    avl_map<string, Data> inventoryMap;

    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
