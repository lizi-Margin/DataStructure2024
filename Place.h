#ifndef  _PLACE_H_
#define _PLACE_H_
#include <string>
#include "Comments.h"
#include "DatabaseIF.h"

class PlaceR :public Place {

protected :
  int place_index ;
  std::string * place_name; 
  std :: string * place_label;

  Comments * comments;
  int like;
public:
  int get_index() override;
  std::string* get_name() override;
  std::string* get_label() override;
  int get_like_num() override;
  int get_comments_num() override;


};

class PlaceRM :public PlaceR {


public:
  std::string* get_name() override;
  std::string* get_label() override;
  void set_index(int n); 
  void set_name(std ::string * name);
  void set_label(std :: string * lb);

};
#endif