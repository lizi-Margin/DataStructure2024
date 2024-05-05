# include "../Database.h"
# include "../util/utils.h"
/*shc 2024*/

void Database :: _init(){
  toursite_amount = 0;
  toursite_list = new ToursiteRM*[DATABASE_TOURSITE_CAPACITY];
  grade_ladder = new int[DATABASE_TOURSITE_CAPACITY];
}
Database :: Database(){
  _init(); 
}


int Database:: _init_toursite_list (CSVReader * proxy, int len,std::string*relative_address){
		proxy->read_line();
		for ( int i = 0 ; i < len ; i++){
			int index ;
			std:: string * name ;
			std:: string * introduction ;
			int place_num ;
			int likes;
			std:: string * address ;
			proxy->read_colomn(index);	
		  proxy->	read_colomn(name);	
			proxy->read_colomn(introduction);	
			proxy->read_colomn(place_num);	
			proxy->read_colomn(likes);	
      address = relative_address;
			toursite_list[i] = new  ToursiteRM();		
      
      toursite_list[i]->set_info  (index,name,introduction,place_num,likes,address);
		}
  
    return 0 ;

	}


const ToursiteRM ** Database:: get_toursite_list(){
  return (const ToursiteRM**)toursite_list;
}

ToursiteRM * Database :: get_toursite (int index){
    return toursite_list[index];
  }


int *   Database :: _search_toursites_index_sort_by_grade (std::string * str , int n ){
    if ( n > toursite_amount) { n = toursite_amount;}
    int * list = new int[toursite_amount];
    for ( int ii =0 ; ii < n ; ii +=1) list[ii] = -1; 
    int list_num = 0;
    for (int ii = 0 ; ii < toursite_amount ; ii +=1){
      if ( this -> toursite_list[ii]->name_match_string(str)){ 
        int jj =  list_num;
        list[list_num++] = ii;

        while(jj > 0){
          if (toursite_list[(list[jj])]->get_grade ()> toursite_list[(list[jj-1])]->get_grade()){
            int temp = list[jj]; list[jj] = list[jj-1];list[--jj] = temp; 
            
          }else{
            break;
          } 
        }
      }
            
    }

    return list;
  }

int Database::load_toursite(int index){
  if (toursite_amount <=0 || index <0 ) return 1;
  if (toursite_list[index]->get_place_num() <=0)return 1; 
  return toursite_list[index]->load();
}

std::string* Database ::  get_toursite_name(int index) {
    return new std::string (*(this->get_toursite(index)->get_name()));
  }
int * Database:: get_toursites_index_by_search(std::string str, int n) {
  // std:: string * new_str =  new std::string(str);
  return this-> _search_toursites_index_sort_by_grade(&str,  n);
  }

int * Database:: _get_top_toursites_index_in_grade_ladder(int n) {
    int * ret = new int[n]; 
    for (int ii=0; ii < n ; ii +=1) ret [ii] = this->grade_ladder[ii];
    return ret;
  }


void Database::_sync_grade_ladder(){
  /* inset sort */
  int i;
  for (int j = 1; j< toursite_amount ; j+=1){
    i = j;
    while (i>0)
    {
      if(toursite_list[grade_ladder[i]]->get_grade()>toursite_list[grade_ladder[i-1]]->get_grade()) {
        int temp = grade_ladder[i];grade_ladder[i] = grade_ladder[i-1];grade_ladder[--i] =temp;
      }else{
        break;
      }
    }
  } 
  // utils:: print_int_list(grade_ladder,toursite_amount);
} 

int * Database ::  get_recommended_toursites_index(int n){
  _sync_grade_ladder();
  return _get_top_toursites_index_in_grade_ladder(n);
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
    return ( toursite_list[index])->get_topo();
  }
  
int Database :: release_database(void){
  delete[] grade_ladder;
  delete[] toursite_list;
  return 0 ;
} /* 释放内存 */

Database::~Database(){
  release_database();
}



int Database:: load_database(std :: string relative_address){
  return load_database(relative_address,30);
} /* 从指定路径导入, 返回值判断是否成功 */

int Database ::load_database(std::string relative_address ,int size){
  std:: string * address = new std::string(relative_address);

  CSVReader proxy((*address + toursite_table_name).c_str()) ;
  if (proxy.is_open()){
    _init_toursite_list( &proxy, size,address);
      
    toursite_amount = size;
    for (int i= 0 ; i <toursite_amount;i+=1){      
      grade_ladder[i]=toursite_list[i]->get_index();      
    }

    proxy.close();
    return 0;
  }
  return 1;
}

void Database:: load_all(){
    for (int i= 0 ; i <toursite_amount;i+=1){ 
      toursite_list[i]->load();
    }
}

void Database::save_all(){
    for (int i= 0 ; i <toursite_amount;i+=1){ 
      toursite_list[i]->save();
    }
}