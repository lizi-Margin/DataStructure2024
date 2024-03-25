# include "Toursite.h"

ToursiteTopo  * ToursiteRM :: get_topo(){
    ToursiteTopo  *topo = new ToursiteTopo;
    topo->adjacent_matrix = this->copy_adjacent_matrix();
    topo->toursite_index = this -> toursite_index;
    topo->place_num = this-> place_num; 
    topo->places = this->copy_places();
}
// got problem below
int** ToursiteRM:: copy_adjacent_matrix(){
    int ** m  =  new int*[TOURSITE_CAPACITY];
    for (int i = this -> place_num -1  ; i >= 0 ; i -=1){
        m [i] = new int [TOURSITE_CAPACITY];
        for ( int j = this -> place_num  -1; j >= 0 ; j -= 1){
            m[i][j] =  this-> adjacent_matrix [i][ j];
        }
    }
    return m ;
  }
Place * *ToursiteRM :: copy_places(){
    Place ** plcs = new Place*[TOURSITE_CAPACITY];
    for (int i = this-> place_num -1; i >= 0 ; i-= 1){
        plcs[i] = this-> places[i];
    }
    return plcs;
}
void ToursiteRM ::sync_grade(){
    this-> grade = this-> get_like_num() + 2* this-> get_comments_num();
  }

ToursiteRM ::ToursiteRM(int index , std:: string *name ,int place_num , Place ** places,int** adjacent_matrix) {
    this-> toursite_index = index;
    this -> toursite_name =(name);
    this -> place_num =  place_num;
    this -> places = places;
    this -> adjacent_matrix = adjacent_matrix;
}

ToursiteRM :: ~ToursiteRM(){} 

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
    this->sync_grade();
    return this-> grade;} 
/*
  Place *  get_place ( int index); 
  Place *  get_place ( std :: string name);
  int get_distance(int index1,int index2);             
*/
  void ToursiteRM ::printMatrix(){}
  bool ToursiteRM ::name_has_substring (std::string* str) /* using BM/KMT algorism */
  {
    if( this-> brute(this->toursite_name , str) >= 0) return 1;  
    return this-> brute(str ,this->toursite_name) >= 0;
  }
int ToursiteRM :: brute(std::string *t, std::string* p) {
    const int m = p->length(), n = t->length();
    int align; // 模式串的对齐位置
    int i; // 模式串中的下标

    // 循环执行以下步骤，直到全部字符比对成功或模式串的右边界超过了文本串的右边界
    for (align = 0; align + i < n && i >= 0; align++) {
        // 从右向左逐个比对，直到全部字符比对成功或某个字符比对失败
        for (i = m - 1; i >= 0 && t[align + i] == p[i]; i--);
        // 如果全部字符比对成功，则退出循环，否则就将模式串向右移动一个字符
        if (i < 0) break;
    }

    return i < 0 // 如果比对成功的话
           ? align // 就返回模式串的对齐位置
           : -1; // 否则就返回-1
}


  /*setter */
  void ToursiteRM ::add_comment(std:: string* content){
    this-> comments -> add_comment( new std:: string(* content));
  }
  void ToursiteRM ::add_like(){this -> like_num += 1;}



