
#define QUERYLENGTH 100
#define PCRE2_CODE_UNIT_WIDTH 8
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <pcre2.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

void fetch_and_print_reselts(MYSQL *con){
  MYSQL_RES *result = mysql_store_result(con);
  
    if (result == NULL) 
      {
        finish_with_error(con);
      }

      int num_fields = mysql_num_fields(result);

      MYSQL_ROW row;
          
      while ((row = mysql_fetch_row(result))) 
        { 
          for(int i = 0; i < num_fields; i++) 
            { 
              printf("%s ", row[i] ? row[i] : "NULL"); 
            } 
              printf("\n"); 
        }
  }


int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);
  char query[QUERYLENGTH];


  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "root", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

  while(fgets(query, QUERYLENGTH , stdin) != NULL)
    {
       if (mysql_query(con, query)) 
        {
          fprintf(stderr, "%s\n", mysql_error(con));
          mysql_close(con);
          exit(1);
        }
        printf("%s\n", query);
        
        fetch_and_print_reselts(con);
    }
  mysql_close(con);
  exit(0);
}