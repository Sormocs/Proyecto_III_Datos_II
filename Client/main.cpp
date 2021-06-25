
#include "Interface.h"

int main(int argc, char *argv[]) {

    SetInstance(new UI(argc, argv));

    Run();

    return 0;
}