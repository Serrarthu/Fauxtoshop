#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <iostream>

#define testMin(a, b)  (((a) < (b)) ? (a) : (b))
#define testMax(a, b)  (((a) > (b)) ? (a) : (b))
#define unused(x) ( (void)(x) )

using namespace std;

class Command
{
    public:
        Command();
        Command(Command* pCommand);
        Command(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Command();
        virtual bool isValid(vector<string> pArgParam);
        virtual void run(vector<string> pArgParam,string input, string output);
        string getStandAlone();
        string getParameter();
        string getNormal();
        string getDescription();
        void setStandAlone(string pStandAlone);
        void setParameter(string pParameter);
        void setNormal(string pNormal);
        void setDescription(string pDescription);
    protected:
        string standAlone;
        string parameter;
        string normal;
        string description;
    private:
};

#endif // COMMAND_H
