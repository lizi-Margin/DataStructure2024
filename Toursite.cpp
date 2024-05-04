# include "Toursite.h"
#include <iostream>
/*shc 2024*/

ToursiteTopo  * ToursiteRM :: get_topo(){
    _check_and_load();
    ToursiteTopo  *topo = new ToursiteTopo;
    topo->toursite_name = new std:: string();
    topo->toursite_name = toursite_name;
    topo->adjacent_matrix = this->_copy_adjacent_matrix();
    topo->toursite_index = this -> toursite_index;
    topo->place_num = this-> place_num; 
    topo->places = _copy_places();
    return topo;
}
// got problem below
int** ToursiteRM:: _copy_adjacent_matrix(){
    int ** m  =  new int*[TOURSITE_CAPACITY];
    for (int i = this -> place_num -1  ; i >= 0 ; i -=1){
        m [i] = new int [TOURSITE_CAPACITY];
        for ( int j = this -> place_num  -1; j >= 0 ; j -= 1){
            m[i][j] =  this-> adjacent_matrix [i][ j];
        }
    }
    return m ;
  }
Place * *ToursiteRM :: _copy_places(){
    Place ** plcs = new Place*[TOURSITE_CAPACITY];
    for (int i = this-> place_num -1; i >= 0 ; i-= 1){        
        PlaceRM* new_place = (new PlaceRM(places[i])); 
        plcs[i] = (Place*)( new_place);
    }
    return plcs;
}
void ToursiteRM ::_sync_grade(){
    this-> grade = this-> get_like_num() + 2* 0;//this-> get_comments_num();
  }


ToursiteRM :: ToursiteRM(){
  loaded = false;

  toursite_index = -1;
  toursite_name =nullptr;
  introduction = nullptr;
  place_num =  0;
  like_num = 0;   
  address =  nullptr;
  grade = 0; 
  places = nullptr; 
  adjacent_matrix = nullptr; 
  comments = nullptr ;
  
}
void ToursiteRM ::set_info(int index , std:: string *name , std:: string *intro,int place_num  ,int likes , std:: string * add) {
  this->toursite_index = index;
  toursite_name =(name);
  introduction = intro;
  this->place_num =  place_num;
  like_num = likes;
  address = add;
  
}

int ToursiteRM::load(){
  // if (loaded) return 0;
  // if (address->length()<=2) return 1;
    
  ToursiteProxy adj_proxy(std::string(*address+std::to_string(toursite_index)+"/adj_matrix.csv").c_str()) ;
  ToursiteProxy places_proxy(std::string(*address+std::to_string(toursite_index)+"/places.csv").c_str()) ;

  int adj_ret = 1 ;
  int places_ret = 1;

  if (adj_proxy.is_open()){
    adj_ret = _load_adj_matrix(&adj_proxy );    
    adj_proxy.close();
  } 
  
  if (places_proxy.is_open()){
    places_ret = _load_places(&places_proxy );
    places_proxy.close();
  }

  if (!(adj_ret == 0 && places_ret == 0)){return 1 ;}

  loaded = true;
  return 0;
}

int ToursiteRM:: _check_and_load(){
  if (loaded) {return 0;}
  return load();
}

int ToursiteRM:: _load_places(ToursiteProxy * proxy){
    places = new PlaceRM*[place_num];
		proxy->read_line();	
		for ( int i = 0 ; i < place_num ; i++){
			int index ;
			std:: string * name ;
			std:: string * introduction ;
			std:: string * label ;
			int likes;
			
			proxy->read_colomn(index);	
		  proxy->	read_colomn(name);	
			proxy->read_colomn(introduction);	
			proxy->read_colomn(label);	
			proxy->read_colomn(likes);	
			places[i] = new  PlaceRM();		
      
      places[i]->set_info  (index,name,introduction,label,likes);
		}
 
    //////////////////////////debug
		// _print_matrix();

		return 0;
}
int ToursiteRM:: _load_adj_matrix(ToursiteProxy * proxy ){
		proxy->read_line();	
		int n =place_num;	
		int ** m  =  new int*[TOURSITE_CAPACITY];	
		for(int i = 0; i<n;i+=1){
        	m [i] = new int [TOURSITE_CAPACITY];
			for(int j= 0; j<n ;j+=1){
				int route_len;
				proxy->read_colomn(route_len);
				m[i][j] =route_len;
			}
		}
		adjacent_matrix = m;

    //////////////////////////debug
		// _print_matrix();

		return 0;
	}
ToursiteRM :: ~ToursiteRM(){
  delete this -> toursite_name ;
  delete this -> places ;
  delete this -> adjacent_matrix;
  delete comments ;
  delete address ;
  delete introduction ;
} 


  std :: string* ToursiteRM ::get_name(){ 
    return ( ToursiteRM :: toursite_name); }
  int ToursiteRM ::get_index() { 
    return this->toursite_index;}
  int ToursiteRM ::get_like_num (){
    return this-> like_num;}
  int ToursiteRM ::get_comments_num (){
    return this-> comments-> get_comments_num();}
  std :: string* ToursiteRM ::get_comment(int index){
    return this-> comments-> get_comment(index);}
  int ToursiteRM ::get_place_num(){
    return this-> place_num;}
  std::string*  ToursiteRM ::get_introduction ( ){
    return  (  this->introduction); };
  int ToursiteRM ::get_grade(){
    this->_sync_grade();
    return this-> grade;} 
/*
  Place *  get_place ( int index); 
  Place *  get_place ( std :: string name);
  int get_distance(int index1,int index2);             
*/

 
void ToursiteRM ::print_2d_matrix(int** m,int place_n){
		for(int i = 0; i<place_n;i+=1){
			for(int j= 0; j<place_n ;j+=1){
				std::cout<<m[i][j]<<" ";
			}
				std::cout<<"\n";
		}
} 

  void ToursiteRM ::_print_matrix(){
		ToursiteRM::print_2d_matrix(adjacent_matrix,place_num);
  }
  bool ToursiteRM ::name_match_string (std::string* str) /* using BM/KMT algorism */
  {
    if( this-> _brute(this->toursite_name , str) >= 0) return 1;  
    return this-> _brute(str ,this->toursite_name) >= 0;
  }
int ToursiteRM :: _brute(std::string *t, std::string* p) {
    const int m = p->length(), n = t->length();
    int j;
    int i; 

    for (i=0 ; i+n < m; i+=1){
      for(j=0; (*t)[j]==(*p)[i+j];j+=1){
        if (j>= n-1)
          {
            return j;
          }
      }
    }

      
    return -1;
}


  /*setter */
  void ToursiteRM ::add_comment(std:: string* content){
    this-> comments -> add_comment( new std:: string(* content));
  }
  void ToursiteRM ::add_like(){this -> like_num += 1;}

void ToursiteRM::print_info(){
  std::cout<< toursite_index<< "|"<<
  *toursite_name<< "|"<<
  *introduction <<"|"<<
  place_num <<"|"<<
  like_num<<"|"<<
  *address <<std ::endl;
}


