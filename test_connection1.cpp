#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

// test mysql connection only
int main(){
    //init mysql link_
    MYSQL* link_ = mysql_init(NULL);

    int timeout = 3;

    if(link_ != NULL){

        mysql_options(link_,MYSQL_OPT_CONNECT_TIMEOUT,(const char *)&timeout);

        mysql_options(link_,MYSQL_OPT_READ_TIMEOUT,(const char *)&timeout);

        mysql_options(link_,MYSQL_OPT_WRITE_TIMEOUT,(const char *)&timeout);

    }

    const char* host_name = "localhost";
    const char* user_name = "root";             // user_name 
    const char* user_password = "ledgerheath";  // user_password
    const char* server_name = "ledger";         // server_name
    unsigned short host_port = 3306;

    if(!mysql_real_connect(link_,host_name,user_name,user_password,server_name,host_port,NULL,0)){
        
        // unsigned int error_code = mysql_errno(link_);   

        mysql_close(link_);

        printf("Test connection failed : %s\n",mysql_error(link_));

    }
    else{
        printf("Test connection success !\n");
    }

    mysql_close(link_);
    
}



// referrence:(https://dev.mysql.com/doc/dev/mysql-server/latest/mysql_8h_source.html)