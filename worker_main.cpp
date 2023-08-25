#include "worker_ms.h"



int main(){
    
    DB_worker workers("workers");     // create class workers
    workers.showAllRecord();
    workers.showMenu();

    return 0;
}