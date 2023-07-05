#include "worker_ms.h"



int main(){
    
    DB_worker workers("workers");     // 创建成功则go on ,失败则退出程序
    workers.showAllRecord();
    workers.showMenu();

    return 0;
}