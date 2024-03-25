#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<string>
#include "Toursite.h" 
#include "DatabaseIF.h"

class Database : public Database_IF{
protected: 
  int toursite_amount ;
  ToursiteRM ** toursite_list; //access with the index
  int * grade_ladder ;//sort all toursite with grade , toursite presented by index
  
  ToursiteRM * get_toursite (int index);
  int get_grade_ladder(int n);
  int * search_toursites_index_sort_by_grade (std::string *str , int n);
  
public :
  std::string* get_toursite_name(int index) override ;
  int * get_toursites_index_by_search(std::string str, int n) ;
  
  int * get_recommended_toursites_index(int n);
  int get_toursite_amount(void); 
   int get_toursite_grade(int index);
  std::string* get_toursite_introduction(int index);
  Toursite * get_toursite_topo(int index);

  int release_database(void)override; /* 释放内存 */
  int load_database(std :: string relative_address)override; /* 从指定路径导入, 返回值判断是否成功 */
};
#endif