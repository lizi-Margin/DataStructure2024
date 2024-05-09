#include <iostream>
#include "DatabaseIF.h"
#include "shc/Database.h"
#include "shc/util/utils.h"
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

  std :: cout << "saving"<<std:: endl ;
  db->load_all();
  db->save_all();
  db->release_database();
  std :: cout << "test end"<<std:: endl ;
  return 0;
}

int main (){
  test();
  //utils::extend_toursite_table(30,400);
  return 0 ;
}

