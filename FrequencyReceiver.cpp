//
//  FrequencyReceiver.cpp
//  freqreader
//
//  Created by Adam on 8/8/13.
//  Copyright (c) 2013 Adam. All rights reserved.
//

#include "FrequencyReceiver.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

int line_num(char *filename)
{
    FILE *f;
    char c;
    int lines = 0;

    f = fopen(filename, "r");

    if(f == NULL)
        return 0;

    while((c = fgetc(f)) != EOF)
        if(c == '\n')
            lines++;

    fclose(f);

    if(c != '\n')
        lines++;

    return lines;
}



FrequencyReceiver::FrequencyReceiver()
{
    cout << "Starting FrequencyReceiver.." << endl;
    std::string line;
    int numberOfLines = line_num("freqlist.txt");

    std::ifstream freqlist("freqlist.txt");
    int progress = 0;
    while(getline(freqlist, line))
    {
    	++progress;
        line.erase(line.begin()+line.size()-1, line.end());
        addToMemory(line);
        cout << "Loading Memory: " <<  (progress * 100 / numberOfLines) << "%\r";
    }

    freqlist.close();
    /*
    cout << endl << "Finished loading cache! reordering data to make everything faster.." << endl;
    for(int i = 0; i < 5; i++) {
    	cout << "Reordering " << i+1 << "-gram..." << endl;
    	std::sort(vHolder[i].begin(), vHolder[i].end(), FreqComparer());
    }
*/
    cout << "FrequencyReceiver is ready!\a" << endl;
}

FrequencyReceiver::~FrequencyReceiver()
{
	for(int i = 0; i < 5; i++)
		vHolder[i].empty();
}

void FrequencyReceiver::addToMemory(std::string line)
{
    std::istringstream ss(line);
    FrequencyHolder data;
    string freq, phrase;
    getline(ss, freq, '	');
    getline(ss, phrase);
    data.Frequency = atoi(freq.c_str());
    data.Pharse = phrase;
    int count = 0;
    for(std::string::iterator it = phrase.begin(); it != phrase.end(); ++it)
    {
    	char o = (*it);
    	if(o == '	')
    		count++;
    }
    vHolder[count].push_back(data);
}

int FrequencyReceiver::getFrequency(std::string phrase)
{
    int count = 0;
    for(std::string::iterator it = phrase.begin(); it != phrase.end(); ++it)
    {
    	char o = (*it);
    	if(o == '	')
    		count++;
    }
    for(std::vector<FrequencyHolder>::const_iterator itr = vHolder[count].begin(); itr != vHolder[count].end(); ++itr)
    {
        FrequencyHolder h = (*itr);
        if(strcmp(h.Pharse.c_str(),phrase.c_str()) == 0)
            return h.Frequency;
    }
    return -1;
}
