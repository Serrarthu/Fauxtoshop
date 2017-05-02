#ifndef CHRONO_H
#define CHRONO_H

#include "command.h"
#include "data.h"
#include "../../base/headers/image_png.h"

using namespace std;

class Chrono : public Command
{
    public:
        Chrono();
        Chrono(Chrono* pChrono);
        Chrono(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Chrono();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
};

#endif
