#include "headers/parallel.h"

Parallel::Parallel(): Command("","parallel","","Parallel") {}

Parallel::~Parallel(){}

Parallel::Parallel(Parallel* pParallel): Command(pParallel) {}

Parallel::Parallel(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Parallel::isValid(vector<string> pArgParam){
	unused(pArgParam);
	if (pArgParam.size() == 1 && atoi(pArgParam[0].c_str()) >= 0) {
		Data::NB_THREADS = atoi(pArgParam[0].c_str());
		return true;
	}
	else return false;
}

void Parallel::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	img->save(output);
}
