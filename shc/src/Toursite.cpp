# include "../Toursite.h"
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

  comments_table  = nullptr;
  place_comments_table= nullptr;
  diary_table= nullptr;  
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
  if (loaded) return 0;
  // if (address->length()<=2) return 1;
    
  CSVReader adj_proxy(std::string(*address+std::to_string(toursite_index)+"/adj_matrix.csv").data()) ;    
  CSVReader places_proxy(std::string(*address+std::to_string(toursite_index)+"/places.csv").data()) ;

    
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

  comments_table = new  TableComments();
  place_comments_table = new TablePlaceComments () ;
  diary_table = new TableDiary (); 
  comments_table -> init(std::string(*address+std::to_string(toursite_index)+"/comments.csv"));
  place_comments_table -> init(std::string(*address+std::to_string(toursite_index)+"/place_comments.csv"));
  diary_table -> init (std::string(*address+std::to_string(toursite_index)+"/diary.csv"));

  
  int comments_ret = comments_table->load() ;
  int place_comments_ret = place_comments_table -> load();
  int diary_ret = diary_table->load() ;

  if (!(adj_ret == 0 && places_ret == 0)){return 1 ;}

  loaded = true;
  return 0;
}

int ToursiteRM::save(){
  if (!loaded) return 0;
  // if (address->length()<=2) return 1;
    
    
  CSVWriter adj_proxy(std::string(*address+std::to_string(toursite_index)+"/adj_matrix.csv").c_str()) ;
  CSVWriter places_proxy(std::string(*address+std::to_string(toursite_index)+"/places.csv").c_str()) ;

  int adj_ret = 1 ;
  int places_ret = 1;

  if (adj_proxy.is_open()){
    adj_ret = _save_adj_matrix(&adj_proxy );    
    adj_proxy.close();
  } 
  
  if (places_proxy.is_open()){
    places_ret = _save_places(&places_proxy );
    places_proxy.close();
  }

  int comments_ret = comments_table->save() ;
  int place_comments_ret = place_comments_table -> save();
  int diary_ret = diary_table->save() ;


  if (!(adj_ret == 0 && places_ret == 0)){return 1 ;}

  return 0;
}

int ToursiteRM:: _check_and_load(){
  if (loaded) {return 0;}
  return load();
}
int ToursiteRM:: _save_places(CSVWriter * proxy){
  proxy->write_line("index,name,introduction,label,likes #");	
  for ( int i = 0 ; i < place_num ; i++){
    proxy->write_colomn(places[i]->get_index());	
    proxy->write_colomn(places[i]->get_name());	
    proxy->write_colomn(places[i]->get_introduction());	
    proxy->write_colomn(places[i]->get_label());	
    proxy->write_last_colomn(places[i]->get_like_num());	    
  }

  std::cout << "places saved successfully\n";
  return 0;
}
int ToursiteRM:: _save_adj_matrix(CSVWriter * proxy ){
  proxy->write_line("#");	
  int n =place_num;	
  int n_minus_1 =n - 1;	
  for(int i = 0; i<n;i+=1){
    for(int j= 0; j<n_minus_1 ;j+=1){
      proxy->write_colomn(adjacent_matrix[i][j]);
    }
    proxy-> write_last_colomn(adjacent_matrix[i][n_minus_1]);
  }
  std::cout << "adjacent matrix saved successfully\n";
  return 0;
	}

int ToursiteRM:: _load_places(CSVReader * proxy){
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
int ToursiteRM:: _load_adj_matrix(CSVReader * proxy ){
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
  delete address ;
  delete introduction ;

  delete comments_table ;
  delete     place_comments_table;
  delete      diary_table;
}
  std :: string* ToursiteRM ::get_name(){ 
    return ( ToursiteRM :: toursite_name); }
  int ToursiteRM ::get_index() { 
    return this->toursite_index;}
  int ToursiteRM ::get_like_num (){
    return this-> like_num;}

  int ToursiteRM ::get_comments_num (){
    _check_and_load();
    return comments_table->get_length();
    }
  std :: string* ToursiteRM ::get_comment(int index){
    _check_and_load();
    return comments_table->get_comment(index);   
  }
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


