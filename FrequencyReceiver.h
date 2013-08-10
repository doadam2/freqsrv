/*
 * FrequencyReceiver.h
 *
 *  Created on: Aug 8, 2013
 *      Author: adam
 */

#ifndef FREQUENCYRECEIVER_H_
#define FREQUENCYRECEIVER_H_


#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct FrequencyHolder
{
    std::string Pharse;
    int Frequency;
    int Length;
};

class FrequencyReceiver
{
public:
    FrequencyReceiver();
    ~FrequencyReceiver();
    int getFrequency(std::string phrase);
private:
    void addToMemory(std::string line);
    std::vector<FrequencyHolder> vHolder[5];
};



#endif /* FREQUENCYRECEIVER_H_ */
