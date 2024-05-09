#ifndef TABLEPLACE_H
#define TABLEPLACE_H
#include "Tables.h"
#include "../Place.h"
/*
 * shc 2024
 */

class TablePlace:public TableBase{
public:
    TablePlace():TableBase(){
        add_int_column("index");
        add_string_column("name");
        add_string_column("instruction");
        add_string_column("label");
        add_int_column("likes");
    }

    std::string * get_name(int index){
        return _get_string(index,1);
    }
    std::string * get_instruction(int index){
        return _get_string(index,2);
    }
    std::string * get_label(int index){
        return _get_string(index,3);
    }
    int get_like_num(int index){
        return _get_int(index,4);
    }

    PlaceRM * get_placeRM(int index,TablePlaceComments* table){
        auto place = new PlaceRM();
        place->set_info(index,get_name(index), get_instruction(index), get_label(index), get_like_num(index), table);
        return  place;
    }
};

#endif //TABLEPLACE_H
