#ifndef DATABASE_H
#define DATABASE_H
#include<string>
#include <filesystem>
#include "Toursite.h" 
#include "../DatabaseIF.h"
#include "util/File.h"
#include "util/BiMap.h"

#define DATABASE_TOURSITE_CAPACITY 400

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
  IntStringBiMap toursite_names;

  /* sorted index list */
  int * grade_ladder ;//sort all toursite with grade , toursite presented by index
  bool grade_ladder_synced = false;
  
  void  _init();
  int _init_toursite_list (CSVReader * proxy, int len,std::string*relative_address);
   
  int * _search_toursites_index_sort_by_grade (std::string *str , int n); 
  int * _get_top_toursites_index_in_grade_ladder(int n); 
  void _sync_grade_ladder(); 

  bool _index_in_range(int index);
  std::string*  _check_get_database_address(std::string* address);
  std::filesystem::path _find_database(const std::filesystem::path& startPath, const std::string& folderName);

public :
  Database();
  
  int load_database(std :: string relative_address)override; /* 从指定路径导入, 返回值判断是否成功 */
  int load_database(std :: string relative_address,int size);
  int load_toursite(int index);
  int save_toursite(int index);
  int export_toursite(int index,int from,int to_not_included);
//  int export_toursite(int index,std::string &addr);
  int  load_all();
  int  save_all()override;
  void print_all ();
  
  const  ToursiteRM ** get_toursite_list(); 
  std::string* get_toursite_name(int index) override ;

  int get_toursite_amount()override;

  int * get_toursites_index_by_search(std::string str, int n) override;
  int * get_recommended_toursites_index(int n)override; 

  int get_toursite_grade(int index)override;
  std::string* get_toursite_introduction(int index)override;

  ToursiteTopo * get_toursite_topo(int index)override;



  int get_toursite_place_num(int index ) override;  


  int get_toursite_comment_num(int index)  override;
  std::string* get_toursite_comment(int index,int comment_index)  override;
  int get_toursite_comment_like_num(int index,int comment_index)  override;

  int get_toursite_diary_num(int index)  override;  
  std::string* get_toursite_diary(int index,int comment_index)  override; 
  int get_toursite_diary_like_num(int index,int comment_index)  override; 

  int get_place_comment_num(int index , int place_index)  override;  
  std::string* get_place_comment(int index,int place_index,int comment_index)  override; 
  int get_place_comment_like_num(int index,int place_index,int comment_index)  override; 




  int release_database()override; /* 释放内存 */
  ~Database();
};
#endif