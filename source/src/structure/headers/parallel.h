#ifndef PARALLEL_H
#define PARALLEL_H

#include "command.h"
#include "data.h"
#include "../../base/headers/image_png.h"


using namespace std;

class Parallel : public Command
{
    public:
        Parallel();
        Parallel(Parallel* pParallel);
        Parallel(string pStandAlone, string pParameter, string pNormal, string pDescription);
        virtual ~Parallel();
        virtual void run(vector<string> pArgParam,string input, string output);
    protected:
    private:
        virtual bool isValid(vector<string> pArgParam);
};

#endif
