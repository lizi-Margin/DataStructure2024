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

int Database::save_toursite(int index){
    if (toursite_amount <=0 || index <0 ) return 1;
    if (toursite_list[index]->get_place_num() <=0)return 1;
    return toursite_list[index]->save();
}

int Database::export_toursite(int index,int from,int to_not_included){
    int ret = 0;
    int this_ret;
    for(int i = from;i<to_not_included;i+=1){
        this_ret=toursite_list[index]->save(i);
        if (this_ret!=0)ret =this_ret ;
    }
    return  ret;
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
  
int Database :: release_database(){
    //save_all();
    delete[] grade_ladder;
    delete[] toursite_list;
    return 0 ;
} /* 释放内存 */
Database::~Database(){
    delete[] grade_ladder;
    delete[] toursite_list;
}



int Database:: load_database(std :: string relative_address){
    auto address = new std::string(relative_address);

    CSVReader proxy((*address +"toursite_table.csv" ).data()) ;
    if (proxy.is_open()){
        int size = proxy.read_row_num();
        std::cout<<"Automatically load database, detected toursite table size: "<<size<<"\n";
        _init_toursite_list( &proxy, size,address);
        toursite_amount = size;
        for (int i= 0 ; i <toursite_amount;i+=1){
            grade_ladder[i]=toursite_list[i]->get_index();
        }
        proxy.close();
        return 0;
    }
    return 1;
} /* 从指定路径导入, 返回值判断是否成功 */

int Database ::load_database(std::string relative_address ,int size){
  auto address = new std::string(relative_address);

  CSVReader proxy((*address +"toursite_table.csv" ).data()) ;
  if (proxy.is_open()){
      proxy.read_line();
      std::cout<<"Manually load database, toursite table size: "<<size<<"\n";
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

int Database:: load_all(){
    int ret_code = 0;
  int i;
  for (i= 0 ; i <toursite_amount;i+=1) {
      if (toursite_list[i]->load() != 0) {
          ret_code = 1;
          std::cout << "Toursite load ERROR, index=" << i << '\n';
      }
  }
  std::cout<<"Toursite load success, all="<<i<<'\n';
    return  ret_code;
}

int Database::save_all(){
    int ret_code = 0;
    int i ;
    for ( i= 0 ; i <toursite_amount;i+=1){
       if (toursite_list[i]->save()!= 0 ) {
           ret_code= 1;
           std::cout<<"Toursite save ERROR, index="<<i<<'\n';
       }
    }
    std::cout<<"Toursite save success, all="<<i<<'\n';
    return  ret_code;
}

void Database::print_all(){
  for (int i= 0 ; i <toursite_amount;i+=1){ 
    toursite_list[i]->print_info();
  }
}




int Database:: get_toursite_place_num(int index)  {
  if (index <0 || index >= toursite_amount)return 0 ;
  return toursite_list[index] ->get_place_num() ;
}

bool Database:: _index_in_range(int index){
    if (index<toursite_amount && index >=0) return true;
    return false;
}
int Database:: get_toursite_comment_num(int index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_comment_num();
    }
    return 0 ;
}  
std::string*  Database:: get_toursite_comment(int index,int comment_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_comment(comment_index);
    }
    return nullptr;
} 
int  Database:: get_toursite_comment_like_num(int index,int comment_index) {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_comment_like_num(comment_index);
    }
    return 0;
}

int  Database:: get_toursite_diary_num(int index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_diary_num();
    }
    return 0;
}
std::string*  Database:: get_toursite_diary(int index,int comment_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_diary(comment_index);
    }
    return nullptr;
} 
int  Database:: get_toursite_diary_like_num(int index,int comment_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_diary_like_num(comment_index);
    }
    return 0;
}

int  Database:: get_place_comment_num(int index , int place_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_place_comment_num(place_index);
    }
    return 0;
}
std::string*  Database:: get_place_comment(int index,int place_index,int comment_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_place_comment(place_index,comment_index);
    }
    return nullptr;
}
int  Database:: get_place_comment_like_num(int index,int place_index,int comment_index)  {
    if (_index_in_range(index)){
        return  toursite_list[index]->get_place_comment_like_num(place_index,comment_index);
    }
    return 0;
}

