#include "headers/command.h"

Command::Command(): standAlone(),parameter(),normal(),description(){}

Command::~Command(){}

Command::Command(Command* pCommand): standAlone(pCommand->standAlone),parameter(pCommand->parameter),normal(pCommand->normal),description(pCommand->description) {}

Command::Command(string pStandAlone, string pParameter, string pNormal, string pDescription): standAlone(pStandAlone),parameter(pParameter),normal(pNormal),description(pDescription) {}

bool Command::isValid(vector<string> pArgParam){
	unused(pArgParam);
    return true;
}

void Command::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	unused(input);
	unused(output);
}

string Command::getStandAlone(){
    return standAlone;
}

string Command::getParameter(){
    return parameter;
}

string Command::getNormal(){
    return normal;
}

string Command::getDescription(){
    return description;
}

void Command::Command::setStandAlone(string pStandAlone){
    standAlone = pStandAlone;
}

void Command::setParameter(string pParameter){
    parameter = pParameter;
}

void Command::setNormal(string pNormal){
    normal = pNormal;
}

void Command::setDescription(string pDescription){
    description = pDescription;
}
