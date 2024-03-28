# include "Database.h"

void Database :: init(){
  toursite_amount = 0;
  toursite_list = new ToursiteRM*[DATABASE_TOURSITE_CAPACITY];
  grade_ladder = new int[DATABASE_TOURSITE_CAPACITY];
}
Database :: Database(){
  init();
  load_database((abs_path+toursite_table).c_str(),5);
  load_all();
}
Database :: Database(const char*toursite_table_address,int size){
  init();
  load_database(toursite_table_address,size);
  load_all();
}

const ToursiteRM ** Database:: get_toursite_list(){
  return (const ToursiteRM**)toursite_list;
}

ToursiteRM * Database :: get_toursite (int index){
    return toursite_list[index];
  }

int Database :: get_grade_ladder(int n){return grade_ladder[n];};

int *   Database :: search_toursites_index_sort_by_grade (std::string * str , int n ){
    if ( n > this->get_toursite_amount()) { n = this->get_toursite_amount();}
    int * list = new int[this->get_toursite_amount()];
    for ( int ii =0 ; ii < n ; ii +=1) list[ii] = -1; 
    int list_num = 0;
    for (int ii = 0 ; ii < this->get_toursite_amount() ; ii +=1){
      if ( this -> get_toursite(ii)->name_has_substring(str)){ 
        int jj =  list_num;
        list[list_num++] = ii;

        while(jj > 0){
          if (this-> get_toursite(list[jj]) > this->get_toursite(list[jj-1])){
            int temp = list[jj]; list[jj] = list[jj-1];list[--jj] = temp; 
          } 
        }
      }
    }

    return list;
  }

int Database::load_toursite(int index){
  if (toursite_amount <=0 || index <0 ) return -1;
  if (toursite_list[index]->get_place_num() <=0)return -1; 
  return toursite_list[index]->load();
}

std::string* Database ::  get_toursite_name(int index) {
    return new std::string (*(this->get_toursite(index)->get_name()));
  }
int * Database:: get_toursites_index_by_search(std::string str, int n) {
    return this-> search_toursites_index_sort_by_grade(&str,  n);
  }

int * Database ::  get_recommended_toursites_index(int n){
    int * ret = new int[n]; 
    for (int ii=0; ii < n ; ii +=1) ret [ii] = this->get_grade_ladder(ii);
    return ret;
  };
int Database::  get_toursite_amount(void){
    return this-> toursite_amount;
  }/* 景点数 */

int Database:: get_toursite_grade(int index)  {
    return this-> get_toursite(index)-> get_grade();
  } /* 查询景点推荐度grade, grade或需单独维护 */
std::string* Database::  get_toursite_introduction(int index){
    return new std:: string(*this-> get_toursite(index)->get_introduction()) ;} 
ToursiteTopo * Database::  get_toursite_topo(int index) {
    return ( this->get_toursite(index))->get_topo();
  }
  
int Database :: release_database(void){} /* 释放内存 */
int Database:: load_database(std :: string relative_address){
  return load_database(relative_address.c_str(),5);
} /* 从指定路径导入, 返回值判断是否成功 */

int Database ::load_database(const char*toursite_table_address,int size){
  ToursiteProxy proxy(toursite_table_address) ;
      
  if (proxy.is_open()){
    init_toursite_list( &proxy, size);
      
    toursite_amount =size;
    for (int i= 0 ; i <toursite_amount;i+=1){
      
      grade_ladder[i]=toursite_list[i]->get_index();  
    
      toursite_list[i]->print_all();
    
      //toursite_list[i]->load();
    }
  }
  proxy.close();
  
  return 0;
}

void Database:: load_all(){
    for (int i= 0 ; i <toursite_amount;i+=1){ 
      toursite_list[i]->load();
    }
}