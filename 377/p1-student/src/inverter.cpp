#include <map>
#include <queue>
#include <set>
#include <string>
#include <cctype>

#include "inverter.h"

using namespace std;

void printl(string s) {
    cout << s << endl;
}

queue<string> getInputFiles(string filename) {
    queue<string> inputFiles;
    ifstream file;
    file.open(filename);
    string line;

    if(file.is_open()) {
        while(getline(file, line)) {
            inputFiles.push(line);
        }
        file.close();
    } else {
        printl("Could not open file specified.");
    }
    return inputFiles;
}

void updateIndex(map<string, set<int>>& index, ifstream& file, int numFile) {
    char c;
    string token;
    while(!file.eof()) {
        file >> noskipws >> c;
        if(isalpha(c)) token.append(1, c);
        else if (token.length() > 0) {
            index[token].insert(numFile);
            token = "";
        }
    }
    if(token.length() != 0) index[token].insert(numFile);
}

string buildOutput(map<string, set<int>>& index) {
    string output = "";
    for(auto it = index.begin(); it != index.end(); ++it) {

        string line = "";
        line.append(it->first);
        line.append(":");
        set<int> apps = it->second;

        for(auto init = apps.begin(); init != apps.end(); ++init) {
            line.append(" ");
            line.append(to_string(*init));
        }

        output.append(line);
        output.append("\n");
    }

    return output;
}

string build_inverted_index(string filename) { 

    queue<string> inputFiles = getInputFiles(filename);
    map<string, set<int>> index;

    int i = 0;
    ifstream file;

    while(!inputFiles.empty()) {
    
        file.open(inputFiles.front());
        inputFiles.pop();

        if(file.is_open()) {
            updateIndex(index, file, i++);
        }
        
        file.close();
    }

    return buildOutput(index);

}

