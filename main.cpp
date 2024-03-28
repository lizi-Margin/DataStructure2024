/*
3.29.2024 shc
This is a test programme.
*/



#include <iostream>
#include "DatabaseIF.h"
#include "Database.h"
int   use_interface(Database_IF * a ){
    
  // a.load_database(std :: string relative_address) = 0; /* 从指定路径导入, 返回值判断是否成功 */
 std:: cout <<   a->get_toursite_amount() ;/* 景点数 */
 std:: cout <<   "\n";
 std:: cout <<   a->get_toursite_grade(1) ; /* 查询景点推荐度grade, grade或需单独维护 */
 std:: cout <<   "\n";
 std:: cout <<   *a->get_toursite_name(1)  ; 
 std:: cout <<   *a->get_toursite_introduction(1) ; 
 std:: cout <<   "\n";
 std:: cout << a->get_toursite_topo(1)   ; /* 索取景点内部拓扑机构 */
 std:: cout <<   "\n";
 std:: cout <<   a->get_toursites_index_by_search("北", 2)[0]; /*search */
 std:: cout <<   "\n";
 std:: cout <<   a->get_recommended_toursites_index(2); /* recommending func */

   a->release_database() ;/* 释放内存 */


    return 0;
}
int main (){
    std :: cout << "testing"<<std:: endl ;
    //Database * db  = new Database("../toursite_table.csv",9);
    Database * db  = new Database();

    use_interface(db);
    
    return 0;
}

