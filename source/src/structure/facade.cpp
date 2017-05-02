#include "headers/facade.h"

Facade::Facade(): arg(0),listStandAlone(0),listParameter(0),listNormal(0) {}

Facade::Facade(int argc, char const * argv[]): arg(convert(argc,argv)),listStandAlone(0),listParameter(0),listNormal(0) {}

Facade::~Facade(){}

vector<string> Facade::convert(int argc, char const * argv[]){
	vector<string> pArg(0);
	for (int i=1;i<argc;i++) pArg.push_back(argv[i]);
	return pArg;
}

void Facade::runArg(Command* pArg, vector<string> pArgParameter, string pInput, string pOutput){
	pArg->run(pArgParameter,pInput,pOutput);
}

void Facade::parseFlag(){
	parseFlag(false,"","");
}

void Facade::parseFlag(bool run, string input, string output){
	bool error = false;
	vector<string> argParameter = {};
	int nbError = -1;
	for (unsigned int i=0;i<arg.size();i++){
		argParameter.clear();
		if (error == false){
			if (arg[i].substr(0,2) == "--" && isParameter(arg[i].substr(2,arg[i].size()-2))){
				unsigned int j = i+1;
				while (j<arg.size() && arg[j].substr(0,1) != "-" && (j<arg.size()-2 || arg[j].size()<4 || arg[j].substr(arg[j].size()-4,4) != ".png")){
					argParameter.push_back(arg[j]);
					j++;
				}
				if(getListParameter(arg[i].substr(2,arg[i].size()-2))->isValid(argParameter)){
					if (run == true) {
						runArg(getListParameter(arg[i].substr(2,arg[i].size()-2)),argParameter,input,output);
						input = output;
						}
					i = i+argParameter.size();
				}
				else error = true;
			}
			
			else if (arg[i].substr(0,2) == "--" && isStandAlone(arg[i].substr(2,arg[i].size()-2)) && getListStandAlone(arg[i].substr(2,arg[i].size()-2))->isValid(argParameter)){
				if (run == true) {
					runArg(getListStandAlone(arg[i].substr(2,arg[i].size()-2)),argParameter,input,output);
					input = output;
					}
			}
			
			else if (arg[i].substr(0,1) == "-"){
				for (unsigned int k=1;k<arg[i].size();k++){
					if (error == false){
						if (isParameter(arg[i].substr(k,1)) && k == arg[i].size()-1){
							unsigned int j = i+1;
							while (j<arg.size() && arg[j].substr(0,1) != "-" && (j<arg.size()-2 || arg[j].size()<4 || arg[j].substr(arg[j].size()-4,4) != ".png")){
								argParameter.push_back(arg[j]);
								j++;
							}
							if(getListParameter(arg[i].substr(k,1))->isValid(argParameter)){
								if (run == true) {
									runArg(getListParameter(arg[i].substr(k,1)),argParameter,input,output);
									input = output;
									}
								i = i+argParameter.size();
							}
							else error = true;
						}
						else if (isNormal(arg[i].substr(k,1))){
							if (run == true) {
								runArg(getListNormal(arg[i].substr(k,1)),argParameter,input,output);
								input = output;
								}
						}
						else error = true;
					}
				}
			}
			
			else if ((i == arg.size()-1 || i == arg.size()-2) && arg[i].substr(arg[i].size()-4,4) == ".png"){
				if (i == arg.size()-1) {
					input = arg[i];
					output = arg[i];
				}
				else if (i == arg.size()-2) {
					if (arg[i+1].substr(arg[i+1].size()-4,4) == ".png") {
						input = arg[i];
						output = arg[i+1];
					}
					else error = true;
					i++;
				}
				else error = true;
			}
			else error = true;
		if (error == true) nbError = i;
		}
	}
	if (error == false && run == false) parseFlag(true,input,output);
	//else if (error == false && run == true) cout << "Traitement sur l'image " << input << " effectue." << endl;
	else if (error == true) cout << "Erreur: la commande ou les parametres de la commande " << arg[nbError] << " sont incorrects." << endl;
}

vector<Command*> Facade::getListStandAlone(){
    return listStandAlone;
}

vector<Command*> Facade::getListParameter(){
    return listParameter;
}

vector<Command*> Facade::getListNormal(){
    return listNormal;
}

Command* Facade::getListStandAlone(unsigned int i){
    if (i<listStandAlone.size()) return listStandAlone[i];
    else return NULL;
}

Command* Facade::getListParameter(unsigned int i){
    if (i<listParameter.size()) return listParameter[i];
    else return NULL;
}

Command* Facade::getListNormal(unsigned int i){
    if (i<listNormal.size()) return listNormal[i];
    else return NULL;
}

Command* Facade::getListStandAlone(string str){
    for (unsigned int i=0;i<listStandAlone.size();i++){
        if (listStandAlone[i]->getStandAlone() == str) return listStandAlone[i];
    }
    return NULL;
}

Command* Facade::getListParameter(string str){
    for (unsigned int i=0;i<listParameter.size();i++){
        if (listParameter[i]->getParameter() == str) return listParameter[i];
    }
    return NULL;
}

Command* Facade::getListNormal(string str){
    for (unsigned int i=0;i<listNormal.size();i++){
        if (listNormal[i]->getNormal() == str) return listNormal[i];
    }
    return NULL;
}

void Facade::setLists(vector< vector<Command*> > pLists){
	for (unsigned int i = 0; i < listStandAlone.size(); i ++)
    {
    	listStandAlone.pop_back();
    }
    for (unsigned int i = 0; i < listParameter.size(); i ++)
    {
    	listParameter.pop_back();
    }
    for (unsigned int i = 0; i < listParameter.size(); i ++)
    {
    	listParameter.pop_back();
    }
    
    for (unsigned int i = 0; i < pLists[0].size(); i ++)
    {
    	listStandAlone.push_back(pLists[0][i]);
    }
    for (unsigned int i = 0; i < pLists[1].size(); i ++)
    {
    	listParameter.push_back(pLists[1][i]);
    }
    for (unsigned int i = 0; i < pLists[2].size(); i ++)
    {
    	listNormal.push_back(pLists[2][i]);
    }
}

void Facade::setListStandAlone(vector<Command*> pListStandAlone){
    for (unsigned int i = 0; i < listStandAlone.size(); i ++)
    {
    	listStandAlone.pop_back();
    }
    for (unsigned int i = 0; i < pListStandAlone.size(); i ++)
    {
    	listStandAlone.push_back(pListStandAlone[i]);
    }
}

void Facade::setListParameter(vector<Command*> pListParameter){
    for (unsigned int i = 0; i < listParameter.size(); i ++)
    {
    	listParameter.pop_back();
    }
    for (unsigned int i = 0; i < pListParameter.size(); i ++)
    {
    	listParameter.push_back(pListParameter[i]);
    }
}

void Facade::setListNormal(vector<Command*> pListNormal){
	for (unsigned int i = 0; i < listNormal.size(); i ++)
    {
    	listNormal.pop_back();
    }
    for (unsigned int i = 0; i < pListNormal.size(); i ++)
    {
    	listNormal.push_back(pListNormal[i]);
    }
}

void Facade::addStandAlone(Command* pStandAlone){
	listStandAlone.push_back(pStandAlone);
}

void Facade::addParameter(Command* pParameter){
	listParameter.push_back(pParameter);
}

void Facade::addNormal(Command* pNormal){
	listNormal.push_back(pNormal);
}

bool Facade::isStandAlone(string str){
    for (unsigned int i=0;i<listStandAlone.size();i++){
        if (listStandAlone[i]->getStandAlone() == str) return true;
    }
    return false;
}

bool Facade::isParameter(string str){
    for (unsigned int i=0;i<listParameter.size();i++){
        if (listParameter[i]->getParameter() == str) return true;
    }
    return false;
}

bool Facade::isNormal(string str){
    for (unsigned int i=0;i<listNormal.size();i++){
        if (listNormal[i]->getNormal() == str) return true;
    }
    return false;
  }
