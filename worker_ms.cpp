#include "worker_ms.h"

#include<mysql/mysql.h>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>



void show_star_lines(){
    for (int j = 0; j < 65; j++){
        std::cout << "☆";
    }
}

DB_worker::DB_worker(const char* tb){

    strcpy(tableName,tb);
    // when createConnection() returning 0;
    if(!createConnection()){
        std::cout<<"Database connected failed!Please check later and then try to connect"<<std::endl;
        system("pause");
        exit(-1);
    }
}

DB_worker::~DB_worker(){
    
    mysql_free_result(res);   // free mysql result
    mysql_close(conn);        // close mysql 

}

void DB_worker::showMenu(){
    char c = 1;
    while (c != '0') {
        show_star_lines();
        std::cout << std::endl;
        std::cout << "\t\t\t\t\t\t\t1.Add a worker\n\t\t\t\t\t\t\t2.Delete a worker\n\t\t\t\t\t\t\t"
             "3.Search\n\t\t\t\t\t\t\t4.Modify\n\t\t\t\t\t\t\t"
             "5.Display all\n\t\t\t\t\t\t\t6.Exit" << std::endl;
        show_star_lines();

        std::cout << std::endl;
        std::cout << "Please select one choice: ";
        std::cin>>c;
        puts("");
        while(c > '0' && c < '6'){
            switch (c) {
                case '1':
                    addRecord();
                    break;
                case '2':
                    deleteRecord();
                    break;
                case '3':
                    searchRecord();
                    break;
                case '4':
                    modifyRecord();
                    break;
                case '5':
                    showAllRecord();
                    break;
                case '0':
                    break;
            }
            showMenu();
            std::cout<<"Please select one choice: ";
            std::cin>>c;
            puts("");
        }
        std::cout << std::endl;
    }
}
// sql : INSERT INTO `workers` VALUES ('001', 'A', 'M', '1993.2', '1', 'Bacherlor', 'manual', 'Shanghai', '010-1111111');
void DB_worker::addRecord()
{
    sprintf(query, "insert into %s values ('", tableName);
    std::cout << "Please enter: " << column[0] << ": ";
    std::cin >> info[0];
    strcat(query, info[0]);
    for (int i = 1; i < num_fields; i++) {
        std::cout << "Please enter: " << column[i] << ": ";
        std::cin >> info[i];
        strcat(query, "','");
        strcat(query, info[i]);
    }
    strcat(query, "')");
    if (mysql_query(conn, query)) {     //执行SQL语句
        printf("Adding failed! (%s)\n", mysql_error(conn));
    } else {
        puts("Adding success!!\n");
    }
    return;
}
// sql: DELETE FROM `stu` WHERE ID = '001';
void DB_worker::deleteRecord()
{
    std::cout << "Please choose to delete which one (enter " << column[0] << "): ";
    std::cin >> info[0];
    sprintf(query, "delete from %s where %s='%s'", tableName,column[0], info[0]);

    if (!mysql_query(conn,query)){
        puts("Deleting success!!!\n");
    }
    else{
        printf("Deleting failture\n (%s)\n", mysql_error(conn));
    }
}
// sql: SELECT * FROM `stu` WHERE SEX_ = F;
void DB_worker::searchRecord()
{
    std::cout << "Please choose a  searching item:\n";
    for (int i = 0; i < num_fields; i++)
        std::cout << i + 1 << "." << column[i] << "  ";
    puts("");
    char c ;
    std::cin>>c;
    if (c > 48 && c < 49 + num_fields) {
        std::cout << "\nPlease enter :" << column[c - 49] << ": "<<std::endl;
        std::cin >> info[0];

        sprintf(query, "select * from %s where %s='%s'",tableName, column[c - 49], info[0]);
        mysql_query(conn,query);

        res = mysql_store_result(conn);
        int row_lines = (int)mysql_num_rows(res);
        MYSQL_FIELD* fd = NULL;
        MYSQL_ROW row;
        for( ; fd = mysql_fetch_field(res);){
            printf("%-10s\t",fd->name);     //%-10s   左对齐并且占10个位置
        }
        //print like this -->
        //(Sno             Sname           Ssex            Sage            Sdept )

        puts("");


        //打印获取的数据
        while (row = mysql_fetch_row(res)) {    //获取下一行
            for(int i=0; i<mysql_num_fields(res); i++)
                printf("%-10s\t",row[i]);
            puts("");
        }
    }
}
void DB_worker::modifyRecord()
{   
    char choice;
    char temp[20];               // char* temp doesn't work
    char id [10];                // id* doesn't work
    std::cout<<"Please enter the Id"<<std::endl;
    std::cin >> id;
    for(int i = 0; i < num_fields; i++)
        std::cout << i + 1 << "." << column[i] << "  ";
    puts("");
    std::cout<<"please enter the choice:";
    std::cin>>choice;
    std::cout<<"please enter the updated attribute:";
    std::cin>>temp;

    // std::cout<<"temp= " << temp<<"ID="<<id<<"choice = "<<choice;
    if(choice > '0' && choice < '1' + num_fields){
        std::cout<<"Please enter the attribute you wanna update"<<std::endl;
        sprintf(query,"update %s set %s='%s' where %s=%s",tableName,column[choice-49],temp,column[0],id);
        printf("%s\n",query);
        mysql_query(conn,query);
    }

}

void DB_worker::showAllRecord()
{   
    MYSQL_RES* res = NULL;
    MYSQL_FIELD* fd = NULL;
    MYSQL_ROW row;

    sprintf(query,"select * from %s",tableName);
    mysql_query(conn,query);
    res = mysql_store_result(conn);
    int row_lines = (int)mysql_num_rows(res);

    printf("Query : %s \n ",query);
    printf("%d records found:\n",row_lines);
    puts("");
    for( ; fd = mysql_fetch_field(res);){
        printf("%-10s\t",fd->name);     //%-10s   左对齐并且占10个位置
    }
    //print like this -->
    //(Sno             Sname           Ssex            Sage            Sdept )

    puts("");


    //打印获取的数据
    while (row = mysql_fetch_row(res)) {    //获取下一行
        for(int i=0; i<mysql_num_fields(res); i++)
            printf("%-10s\t",row[i]);
        puts("");
    }
    
}
//连接数据库
bool DB_worker::createConnection()
{
    int result = 1;
    conn = mysql_init(0);
    if (!mysql_real_connect(conn, "localhost", "root", "ledgerheath", "ledger", 0, NULL, 0)) {
        printf( "Error connecting to database:%s\n", mysql_error(conn));
        result = 0;
    } else {
        printf("Connected successful\n");
        int timeout =  30;      //设置查询超时时长
        if (conn != NULL) {
            //设置链接超时时间.
            mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&timeout);
            //设置查询数据库(select)超时时间
            mysql_options(conn, MYSQL_OPT_READ_TIMEOUT, (const char *)&timeout);
            //设置写数据库(update,delect,insert,replace等)的超时时间。
            mysql_options(conn, MYSQL_OPT_WRITE_TIMEOUT, (const char *)&timeout);
        }

        mysql_query(conn, "set names 'GBK'"); //设置字符集，防止中文无法正常显示
        sprintf(query, "select * from %s ", tableName);
        mysql_query(conn, query);

        res = mysql_store_result(conn);
        //必须对返回的指针进行校验，否则如果没有这个表，会导致程序崩溃！！
        //必须养成校验返回值的习惯，特别是对返回的是指针的情况
        if (res != NULL) {
            num_fields = mysql_num_fields(res);
            //获取各字段的表头名称
            for (int i = 0; i < num_fields; i++){
                strcpy(column[i], mysql_fetch_field(res)->name);
            }
                
            puts("");
        }
    }
    puts("————————————————————\n");
    return result;
}
