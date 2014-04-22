#ifndef SPLITSTRING_H
#define	SPLITSTRING_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class splitstring : public string
{
    vector<string> flds;
    
    public:
        splitstring() {};
        splitstring(string s) : string(s) { };
        vector<string>& split(char delim, int rep=0); 
};

#endif	/* SPLITSTRING_H */

