#ifndef DEBLUR_H
#define DEBLUR_H

#define MAX_DIST 30
#define NB_POPULATION 10
#define CROSSOVER 70//% // Probabilité d'enjambement
#define MUTATION 1//% // Probabilité de mutation


#include <cstdlib>
#include "../../structure/headers/command.h"
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "filterFitness.h"
#include "imageProcess.h"

#include "../../structure/headers/data.h"
#include <omp.h>


using namespace std;

class Deblur : public Command
{
    public:
        Deblur();
        Deblur(Deblur* pDeblur);
        Deblur(string pStandAlone, string pParameter, string pNormal, string pDescription);
        Deblur(const Deblur &pDeblur);
        const Deblur &operator =(const Deblur &pDeblur);
        vector<FilterFitness*> getPopulation();
        virtual ~Deblur();
        virtual void run(vector<string> pArgParam,string input, string output);
        void display();
    protected:
    private:
        vector<FilterFitness*> population;
        virtual bool isValid(vector<string> pArgParam);
        ImagePNG* deblur(ImagePNG* img);
        FilterFitness* algoGenetique(ImagePNG* img);
        void createRefImage(ImagePNG* img);
        void generation(const ImagePNG* img);
        void selectionRandom(const ImagePNG* img);
        void selectionAdaptation(const ImagePNG* img);
        void crossover(const ImagePNG* img);
        void mutation(const ImagePNG* img);
        void allUpdate(const ImagePNG* img);
        FilterFitness* bestFilter();
};

#endif
