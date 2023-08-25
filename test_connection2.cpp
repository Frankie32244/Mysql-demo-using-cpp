#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h> 

// test connection and get all the data from mysql database 
int main(){
    // mysql init
    MYSQL* mysql_ = mysql_init(NULL);
    // mysql init
    mysql_init(mysql_);

    int timeout = 3;

    // set timeout = 3 
    if(mysql_ !=NULL){
        mysql_options(mysql_ ,MYSQL_OPT_CONNECT_TIMEOUT,(const char *)&timeout);
        mysql_options(mysql_ ,MYSQL_OPT_READ_TIMEOUT,(const char *)&timeout);
        mysql_options(mysql_ ,MYSQL_OPT_WRITE_TIMEOUT,(const char *)&timeout);
    }


    const char host_name[20] = "localhost";
    const char user_name[20] = "root";                   // user_name 
    const char user_password[20] = "ledgerheath";       // user_password
    const char server_name[20] = "ledger";             // server_name
    unsigned short host_port = 3306;

    int row_lines = 0;
    char sqlText[100] = "";                        // sql text example: select * from stu; 
    MYSQL_RES* res = NULL;
    MYSQL_FIELD* fd = NULL;
    MYSQL_ROW row;

    
    // connecting mysql failed !!
    if(!mysql_real_connect(mysql_,host_name,user_name,user_password,server_name,host_port,NULL,0)){
        printf("Conecting faied!!\n");

        printf("Error connection : %s\n",mysql_error(mysql_));

        mysql_close(mysql_);
    }
    else{  // connecting mysql success !!
        puts("Connecting database success!!\n");
        sprintf(sqlText,"select * from %s ","stu");
        printf("%s\n",sqlText);

        if(!mysql_query(mysql_,sqlText)){         // excute mysqlText
            res = mysql_store_result(mysql_);
            row_lines = (int)mysql_num_rows(res);

            printf("Query : %s \n ",sqlText);
            printf("%d records found:\n",row_lines);

            //print field name 
            for( ; fd = mysql_fetch_field(res);){
                printf("%-*s",50/mysql_num_fields(res),fd->name);
            }
            //print like this -->
            //(Sno             Sname           Ssex            Sage            Sdept )

            puts("");


            
            MYSQL_ROW row; 
            while (row = mysql_fetch_row(res)) {  
                for(int i=0; i<mysql_num_fields(res); i++)
                    printf("%-*s",50/mysql_num_fields(res),row[i]);
                puts("");                    // line break
            }
            //print like this-->
            // 121031323 Lori      m         21        cs        
            // 121031324 Nancy     F         21        cs        
            // 121031325 Paul      m         22        cs        
            // 121031326 Messi     m         22        cs        
            // 121031329 Ding      m         20        cs
            mysql_free_result(res);
        }
        else{
            printf("Querying error:%s!!\n",mysql_error(mysql_));
            mysql_close(mysql_);
            return false;
        }
    }
    mysql_close(mysql_);
    return true;
}

