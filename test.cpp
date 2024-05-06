#include <iostream>
#include "DatabaseIF.h"
#include "shc/Database.h"
#include "shc/util/utils.h"
#include "shc/util/List.h"


/*
3.29.2024 shc
This is a test programme.
这个文件提供了模块1的使用方式, 仅作参考.
*/



int   use_interface(Database_IF * a ){
    
  // a.load_database(std :: string relative_address) = 0; /* 从指定路径导入, 返回值判断是否成功 */
  std:: cout << "景点数： " << a->get_toursite_amount() ;/* 景点数 */
  std:: cout <<   "\n";
  

  std:: cout << "一号景点推荐度： "<<   a->get_toursite_grade(1) ; /* 查询景点推荐度grade, grade或需单独维护 */
  std:: cout <<   "\n";

  
  std:: cout << "一号景点名字： "<<   *a->get_toursite_name(1)  ; 
  std:: cout <<   "\n";

  
  std:: cout << "一号景点介绍： "<<   *a->get_toursite_introduction(1) ; 
  std:: cout <<   "\n";

  
  ToursiteTopo * tp = a->get_toursite_topo(1)   ;
  std:: cout << "一号景点拓扑结构地址： "<< tp   ; /* 索取景点内部拓扑机构 */
  std:: cout <<   "\n";
  utils::print_topo_struct(tp);

  
  std:: cout << "字符串搜索结果： "   ; 
  utils::  print_int_list(  a->get_toursites_index_by_search("北", 10),10); /*search */
  std:: cout << "按推荐度推荐结果： "   ; 
  utils:: print_int_list( a->get_recommended_toursites_index(10),10); /* recommending func */

  //a->release_database() ;/* 释放内存 */

  return 0;
}

void use_int_list(List<int> * list ){
  for (int i = 0 ; i < 20 ; i +=1){
    list->append(i);
  }
  list->print(); 
}
void use_string_list(List<std::string> * list ){
  for (int i = 0 ; i < 20 ; i +=1){
    char s[2] ;
    s[0] = (char)i + 48;
    s[1] = '\0';
    list->append(std::string(s));
  }
  list->print(); 
}




std:: string abs_path =  std::string("C:/Users/33149/Desktop/DS2024/pack/shc/Database/");
const int chunk_size = 5;

int test(){
  std :: cout << "testing"<<std:: endl ;

  Database * db  = new Database();
  db->load_database(abs_path);
  
  use_interface(db);
  
  // ChunkList<std::string> *  cl = new  ChunkList<std::string>(5);
  // use_string_list(cl); 
  // cl->print();

  db->load_all();
  std :: cout << "saving"<<std:: endl ;
  db->save_all();

  db->release_database();
  std :: cout << "test end"<<std:: endl ;
  return 0;
}


int main (){
  test();    
  return 0 ;
}

