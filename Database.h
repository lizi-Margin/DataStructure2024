#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<string>
#include "Toursite.h" 
#include "DatabaseIF.h"
#include "util/File.h"

#define DATABASE_TOURSITE_CAPACITY 200

/*
  Implements of databaseIF.
  Main class of M1 database.
  shc 2024
*/

class Database : public Database_IF{
protected: 
  int toursite_amount ;

  /* main list */
  ToursiteRM ** toursite_list; //access with the index
  ToursiteRM * get_toursite (int index);

  /* sorted index list */
  int * grade_ladder ;//sort all toursite with grade , toursite presented by index
  
  void  _init();
  int _init_toursite_list (CSVReader * proxy, int len,std::string*relative_address);
   
  int * _search_toursites_index_sort_by_grade (std::string *str , int n); 
  int * _get_top_toursites_index_in_grade_ladder(int n); 
  void _sync_grade_ladder(); 

public :
  Database();
  
  int load_database(std :: string relative_address)override; /* 从指定路径导入, 返回值判断是否成功 */
  int load_database(std :: string relative_address,int size);
  int load_toursite(int index);
  void  load_all();
  void  save_all();
  void print_all ();
  
  const  ToursiteRM ** get_toursite_list(); 
  std::string* get_toursite_name(int index) override ;

  int get_toursite_amount(void)override; 

  int * get_toursites_index_by_search(std::string str, int n) override;
  int * get_recommended_toursites_index(int n)override; 

  int get_toursite_grade(int index)override;
  std::string* get_toursite_introduction(int index)override;

  ToursiteTopo * get_toursite_topo(int index)override;

  int release_database(void)override; /* 释放内存 */
  ~Database();
};
#endif