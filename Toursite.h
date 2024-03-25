#ifndef _TOURSITE_H_
#define _TOURSITE_H_
#include <string>
#include "Place.h"
#include "Comments.h"
#include "DatabaseIF.h"
# define TOURSITE_CAPACITY 100

class Toursite
{
protected :
  int toursite_index ;
  std :: string * toursite_name ;
  int  place_num;       // 顶点数 
  Place **  places;        // 顶点表
  int** adjacent_matrix;                            

};

class ToursiteRM  : public Toursite{
protected:            // 邻接矩阵

  int like_num;   
  Comments * comments ;
  int grade;
  std::string * introduction;
  void sync_grade();
  int ** copy_adjacent_matrix();
  Place ** copy_places();
  int brute(std::string*t, std::string*p);
public:
  ToursiteTopo * get_topo(); 
  ToursiteRM();
  ToursiteRM(int index , std:: string * name ,int place_num , Place ** places,int** adjacent_matrix) ;
  ~ToursiteRM();                       // 析构函数
  /* 需要用到的 getter */
  std :: string* get_name();
  int get_index();
  int get_like_num ();
  int get_comments_num ();
  std :: string* get_comment(int index);
  int get_place_num();
//Place * get place (int index);
  std::string*  get_introduction ( ){return this->introduction; };
  int get_grade(){this->sync_grade();return this-> grade;} 
/*
  Place *  get_place ( int index); 
  Place *  get_place ( std :: string name);
  int get_distance(int index1,int index2);             
*/
  void printMatrix();
  bool name_has_substring (std::string *str); /* using BM/KMT algorism */
  /*setter */
  void add_comment(std:: string*content);
  void add_like();
};
#endif