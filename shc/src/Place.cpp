#include "../Place.h"
#include <string>
/*shc 2024*/

PlaceRM :: PlaceRM(){
    place_index = -1;
    likes = 0;
    place_name = nullptr;    
    place_introduction = nullptr;
    place_label = nullptr;

    place_comment_table = nullptr;
}

PlaceRM :: PlaceRM(PlaceRM * place){
    place_index = place->get_index();
    likes = place->get_like_num();
    place_name = place->get_name();
    place_introduction = place->get_introduction();
    place_label = place->get_label();

    // warining 警告， 可能被其他模块删除
    place_comment_table = place->place_comment_table;

}





int PlaceRM :: get_index(){
    return this-> place_index;
}

std::string*  PlaceRM:: get_name() {
    return new std:: string(*this -> place_name);
}
std::string* PlaceRM :: get_introduction(){
    return new std:: string (*this-> place_introduction);
}
std::string* PlaceRM :: get_label(){
    return new std:: string(*this -> place_label);
}
int PlaceRM :: get_like_num(){
    return this -> likes ;
  }
int PlaceRM :: get_comments_num(){
    return this-> place_comment_table ->get_place_comment_num(place_index);
  }


void PlaceRM::set_info(int index,std::string*name, std::string*introduction, std::string*label,int lks,TablePlaceComments * table){
    place_index = index;
    likes = lks;
    place_name = name;    
    place_introduction = introduction;
    place_label = label;

    place_comment_table = table;
}


// std::string*  PlaceRM:: get_name() {
//     return (this -> place_name);
// }
// std::string* PlaceRM :: get_introduction(){
//     return (this-> place_introduction);
// }
// std::string*  PlaceRM:: get_label() {
//     return (this -> place_label);
// }

// void PlaceRM :: set_index(int n){
//     this -> place_index = n ;
// } 
// void PlaceRM :: set_name(std ::string * name){
//     this-> place_name = name;
// }
// void PlaceRM :: set_label(std:: string * lb){
//     this-> place_label = lb;
// }