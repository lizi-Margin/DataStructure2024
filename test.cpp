#include <iostream>
#include <filesystem>
#include "DatabaseIF.h"
#include "shc/Database.h"
#include "shc/util/utils.h"
#include "shc/util/List.h"
#include "shc/util/BiMap.h"
#include "shc/util/Queue.h"
/*
2024 shc
This is a test programme.
这个文件提供了模块1的使用方式, 仅作参考.
*/



int test(){
  std :: cout << "testing"<<std:: endl ;

  std:: string abs_path =  std::string("C:/Users/33149/Desktop/DS2024/pack/shc/Database/");
  auto db  = new Database();
  db->load_database(abs_path);
  //db->load_all();

  utils::use_interface(db);
  utils::use_interface_extend(db);

  // while (1)
  // {
  //   std::string str;
  //   std::cin>>str;
  //   std::cout<< *db->get_toursites_index_by_search(str,10);
  // }
  

  std :: cout << "saving"<<std:: endl ;
  db->load_all();
  db->save_all();
  db->release_database();
  std :: cout << "test end"<<std:: endl ;
  return 0;
}

int main (){


  // std::cout <<"begin\n";
  test();
  // utils::extend_toursite_table(30,400);
  // utils::reset_toursite_table();      

  

  // IntStringBiMap ac_list; 
  // std::cout <<"init\n";
  // ac_list.append("bcdef");
  // ac_list.append("bcde");
  // ac_list.append("bcd");
  // ac_list.append("bc");
  // ac_list.print_info();
  // ac_list.print();

  // ChunkList<int>  ans = ac_list.search_pattern("abcd");
  // ans.print_info();
  // ans.print();
  // std::cout <<ac_list.get_index("abcd")<<"\n";

  // ChunkList<int> ans1 = ac_list.get("bcde");
  // ans1.print_info();
  // ans1.print();


  // std::cout <<"end\n";
  return 0 ;
}

