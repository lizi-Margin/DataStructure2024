#ifndef _TOURSITE_H_
#define _TOURSITE_H_
#include <string>
#include "Place.h"
#include "util/Comments.h"
#include "DatabaseIF.h"
#include "util/File.h"
# define TOURSITE_CAPACITY 100

/*
  Class Toursite.
  shc 2024
*/

class Toursite
{
protected :
  /* info */
  int toursite_index ;
  std :: string * toursite_name ;
  int  place_num;       // 顶点数 

  /* struct */
  PlaceRM **  places;        // 顶点表
  int** adjacent_matrix;                            

};

class ToursiteRM  : public Toursite{
protected:            // 邻接矩阵
  /* info */
  int like_num;     
  int grade;
  std::string * address;
  std::string * introduction;
  bool loaded;

  /* struct */
  Comments * comments ;
  

  int _load_adj_matrix(ToursiteProxy * proxy );
  int _load_places(ToursiteProxy * proxy);

  void _sync_grade();

  int ** _copy_adjacent_matrix();
  Place ** _copy_places();

  void _print_matrix();

  int _brute(std::string*t, std::string*p);
public:

  ToursiteRM();
  
  
  static void print_2d_matrix(int** m,int place_n);
  
  int load();


  
  void add_comment(std:: string*content);
  void add_like();
  void print_info(); 
  
  bool name_match_string (std::string *str); /* using BM/KMT algorism */ 
  ~ToursiteRM();                       // 析构函数

  /* getter */
  ToursiteTopo * get_topo(); 
  std :: string* get_name();
  int get_index();
  int get_like_num ();
  int get_comments_num ();
  std :: string* get_comment(int index);
  std::string*  get_introduction ();
  int get_grade() ;

  int get_place_num(); 
  /* setter*/

  void set_info(int index , std:: string *name , std:: string *intro,int place_num  ,int like_num , std:: string * add); 
};
#endif