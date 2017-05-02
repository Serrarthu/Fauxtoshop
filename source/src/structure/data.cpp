#include "headers/data.h"
#include "time.h"
#include "../deblur/headers/deblur.h"

int Data::NB_THREADS = 1;
bool Data::CHRONO = false;

void Data::initialize(Facade* facade){
    srand(time(NULL));
    
    facade->addStandAlone(new Deblur());
    
    facade->addParameter(new Parallel());
    facade->addStandAlone(new Chrono());
}

void Data::execute(Facade* facade){
	facade->parseFlag();
}

double Data::get_time() {
	struct timeval tv;
	gettimeofday(&tv,0);
	return (double) tv.tv_sec+tv.tv_usec*1e-6;
}
