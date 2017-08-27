#ifndef FOLLOWGENERATOR_H
#define FOLLOWGENERATOR_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Symbol.h"

using namespace std;

class FollowGenerator
{
    public:
        FollowGenerator(unordered_map< string, vector< vector< Symbol* > > >, unordered_map<string, vector< string >>);
        unordered_map<string, vector< string >> get_follow_set();
        virtual ~FollowGenerator();
    protected:
    private:
        unordered_map< string, vector< vector< Symbol* > > > productions;
        unordered_map< string, vector< string > > first_set;
        unordered_map< string, vector< string > > follow_set;

};

#endif // FOLLOWGENERATOR_H
