#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<string>
#include "Toursite.h" 
#include "DatabaseIF.h"
#include "File.h"

#define DATABASE_TOURSITE_CAPACITY 200

/*
  Implements of databaseIF.
  Main class of M1 database.
  shc 2024
*/

class Database : public Database_IF{
protected: 
  int toursite_amount ;
  ToursiteRM ** toursite_list; //access with the index
  int * grade_ladder ;//sort all toursite with grade , toursite presented by index
  
  void  init();
  ToursiteRM * get_toursite (int index);
  int get_grade_ladder(int n);
  int * search_toursites_index_sort_by_grade (std::string *str , int n);
  int init_toursite_list (ToursiteProxy * proxy, int len){
		proxy->read_line();
		for ( int i = 0 ; i < len ; i++){
			int index ;
			std:: string * name ;
			std:: string * introduction ;
			int place_num ;
			int likes;
			std:: string * address ;
			proxy->read_colomn(index);	
		proxy->	read_colomn(name);	
			proxy->read_colomn(introduction);	
			proxy->read_colomn(place_num);	
			proxy->read_colomn(likes);	
		proxy->	read_colomn(address);	
			toursite_list[i] = new  ToursiteRM(index,name,introduction,place_num,likes,address);
		}
		return 0 ;
	}
public :
  Database();
  Database(const char*toursite_table_address,int size);
  const  ToursiteRM ** get_toursite_list();
  int load_toursite(int index);
  std::string* get_toursite_name(int index) override ;
  int * get_toursites_index_by_search(std::string str, int n) override;
  
  int * get_recommended_toursites_index(int n)override;
  int get_toursite_amount(void)override; 
   int get_toursite_grade(int index)override;
  std::string* get_toursite_introduction(int index)override;
  ToursiteTopo * get_toursite_topo(int index)override;

  int release_database(void)override; /* 释放内存 */
  int load_database(std :: string relative_address)override; /* 从指定路径导入, 返回值判断是否成功 */
  int load_database(const char*toursite_table_address,int size);
  void  load_all();
};
#endif