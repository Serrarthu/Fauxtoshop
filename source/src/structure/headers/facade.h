#ifndef FACADE_H
#define FACADE_H

#include <vector>
#include <string>
#include <iostream>
#include "command.h"

using namespace std;

class Facade
{
    public:
        Facade();
        Facade(int argc, char const * argv[]);
        virtual ~Facade();
        vector<Command*> getListStandAlone();
        vector<Command*> getListParameter();
        vector<Command*> getListNormal();
        Command* getListStandAlone(unsigned int i);
        Command* getListParameter(unsigned int i);
        Command* getListNormal(unsigned int i);
        Command* getListStandAlone(string str);
        Command* getListParameter(string str);
        Command* getListNormal(string str);
        void setLists(vector< vector<Command*> > pLists);
        void setListStandAlone(vector<Command*> pListStandAlone);
        void setListParameter(vector<Command*> pListParameter);
        void setListNormal(vector<Command*> pListNormal);
        void addStandAlone(Command* pStandAlone);
        void addParameter(Command* pParameter);
        void addNormal(Command* pNormal);
        void parseFlag();
    protected:
    private:
        vector<string> arg;
        vector<Command*> listStandAlone;
        vector<Command*> listParameter;
        vector<Command*> listNormal;
        void parseFlag(bool run, string input, string output);
        bool isStandAlone(string str);
        bool isParameter(string str);
        bool isNormal(string str);
        vector<string> convert(int argc, char const * argv[]);
        void runArg(Command* pArg, vector<string> pArgParameter, string pInput, string pOutput);
};

#endif // FACADE_H
