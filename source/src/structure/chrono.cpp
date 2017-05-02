#include "headers/chrono.h"

Chrono::Chrono(): Command("chrono","","","Chrono") {}

Chrono::~Chrono(){}

Chrono::Chrono(Chrono* pChrono): Command(pChrono) {}

Chrono::Chrono(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription) {}

bool Chrono::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) {
	Data::CHRONO = true;
	return true;
}
else {cout <<"pas ok"<<endl; return false;}
}

void Chrono::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	img->save(output);
}
