#ifndef WORKER_MS_H
#define WORKER_MS_H

#include<mysql/mysql.h>

class DB_worker{
    public:
        DB_worker(const char* tb);
        ~DB_worker();

        void showMenu();

        void addRecord();
        void deleteRecord();
        void searchRecord();
        void modifyRecord();

        void showAllRecord();

    private:
        bool createConnection();

    public:
        char column[20][30];
        char info[10][50];
        MYSQL *conn;
        MYSQL_RES *res;
        int num_fields;
        char query[1024];
        char tableName[20];
};

#endif