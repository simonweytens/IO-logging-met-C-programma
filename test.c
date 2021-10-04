#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "PJ_RPI.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{  

    MYSQL *con = mysql_init(NULL);
    printf("MySQL client version: %s\n", mysql_get_client_info());
    if (con == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "webuser", "secretpassword", 
                "globe_bank", 0, NULL, 0) == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);

    }  

    if (mysql_query(con, "SELECT * FROM subjects"))
    {
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    if(map_peripheral(&gpio) == -1) 
    {
            printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
            return -1;
    }

    if (mysql_query(con, "DROP TABLE IF EXISTS Led")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "CREATE TABLE Led(id INT PRIMARY KEY AUTO_INCREMENT, toestand VARCHAR(255))")) {
      finish_with_error(con);
  }

    // Define gpio 4 as output
    INP_GPIO(4);
    OUT_GPIO(4);
    int i = 0;
     while ((row = mysql_fetch_row(result)))
    {
        // Toggle 4 (blink a led!)
        GPIO_SET = 1 << 4;
        sleep(1);
        if (mysql_query(con, "INSERT INTO Led VALUES(0,'Hoog')")) {
            finish_with_error(con);
        }
        GPIO_CLR = 1 << 4;
        sleep(1);
        
    }


    // while ((row = mysql_fetch_row(result)))
    // {
    //     for(int i = 0; i < num_fields; i++)
    //     {
    //         printf("%s ", row[i] ? row[i] : "NULL");
    //     }
    //     printf("\n");
    // }
    mysql_free_result(result);

  exit(0);
}
