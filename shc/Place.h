#ifndef  _PLACE_H_
#define _PLACE_H_
#include <string>
#include "util/Comments.h"
#include "util/Tables.h"
#include "../DatabaseIF.h"

/*
  Place class for toursites.
  shc 2024
*/

class PlaceRM :public Place {

protected :
  /* info */
  int place_index ;
  int likes;
  std::string * place_name; 
  std::string * place_introduction; 
  std::string * place_label;

  /* struct */
  //Comments * comments;
  TablePlaceComments * place_comment_table;

  
public:
  PlaceRM();
  explicit PlaceRM(PlaceRM * );
  void set_info(int index,std::string*name, std::string*introduction, std::string*label,int likes,TablePlaceComments * table);
 
  int get_index() override;
  std::string* get_name() override;
  std::string* get_introduction() override;
  std::string* get_label() override;
  int get_like_num() override;
  int get_comments_num() override;

  // void set_index(int n); 
  // void set_name(std ::string * name);
  // void set_label(std :: string * lb);


};

#endif