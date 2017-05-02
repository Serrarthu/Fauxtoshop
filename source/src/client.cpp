#include "structure/headers/data.h"
using namespace std;

int main(int argc, char const * argv[])
{

    Facade* facade = new Facade(argc,argv);
    Data::initialize(facade);
    Data::execute(facade);
    
    return 0;
}
