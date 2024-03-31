#include "Place.h"
#include <string>
/*shc 2024*/

int PlaceR :: get_index(){
    return this-> place_index;
}

std::string*  PlaceR:: get_name() {
    return new std:: string(*this -> place_name);
}
std::string* PlaceR :: get_introduction(){
    return new std:: string (*this-> place_introduction);
}
std::string* PlaceR :: get_label(){
    return new std:: string(*this -> place_label);
}
int PlaceR :: get_like_num(){
    return this -> like ;
  }
int PlaceR :: get_comments_num(){
    return this-> comments -> get_comments_num();
  }


std::string*  PlaceRM:: get_name() {
    return (this -> place_name);
}
std::string* PlaceRM :: get_introduction(){
    return (this-> place_introduction);
}
std::string*  PlaceRM:: get_label() {
    return (this -> place_label);
}
void PlaceRM :: set_index(int n){
    this -> place_index = n ;
} 
void PlaceRM :: set_name(std ::string * name){
    this-> place_name = name;
}
void PlaceRM :: set_label(std:: string * lb){
    this-> place_label = lb;
}