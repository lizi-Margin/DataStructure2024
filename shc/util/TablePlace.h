#ifndef TABLEPLACE_H
#define TABLEPLACE_H
#include "Tables.h"
#include "../Place.h"
/*
 * shc 2024
 */

class TablePlace:public TableBase{
public:
    


    // ChunkList<std::string> random_name;
    // ChunkList<std::string> random_intro;
    // ChunkList<std::string> random_label;
    // void load_random(){
    //     random_name.append("一教学楼");
    //     random_name.append("二教学楼");
    //     random_name.append("三教学楼");
    //     random_name.append("四教学楼");
    //     random_name.append("五教学楼");
    //     random_intro.append("一教学楼是新中国第1所邮电高等教学楼。");
    //     random_intro.append("二教学楼是新中国第18所邮电高等教学楼。");
    //     random_intro.append("三教学楼是新中国第114514所邮电高等教学楼。");
    //     random_intro.append("四教学楼是新中国第514所邮电高等教学楼。");
    //     random_intro.append("五教学楼是新中国第114所邮电高等教学楼。");
    //     random_label.append(" 教学楼 ");
    //     random_label.append(" 教学楼 ");
    //     random_label.append(" 教学楼 ");
    //     random_label.append(" 教学楼 ");
    //     random_label.append(" 教学楼 ");

    //     random_name.append("一厕所");
    //     random_name.append("二厕所");
    //     random_name.append("三厕所");
    //     random_name.append("四厕所");
    //     random_name.append("五厕所");
    //     random_intro.append("一厕所是一所厕所。");
    //     random_intro.append("二厕所是厕所。");
    //     random_intro.append("三厕所是厕所。");
    //     random_intro.append("四厕所是新中国第514所邮电高等厕所。");
    //     random_intro.append("五厕所是厕所。");
    //     random_label.append(" 厕所 ");
    //     random_label.append(" 厕所 ");
    //     random_label.append(" 厕所 ");
    //     random_label.append(" 厕所 ");
    //     random_label.append(" 厕所 ");

    //     random_name.append("一食堂");
    //     random_name.append("二食堂");
    //     random_name.append("三食堂");
    //     random_name.append("四食堂");
    //     random_name.append("五食堂");
    //     random_intro.append("一食堂是一所食堂。");
    //     random_intro.append("二食堂是食堂。");
    //     random_intro.append("三食堂是食堂。");
    //     random_intro.append("四食堂是新中国第514所邮电高等食堂。");
    //     random_intro.append("五食堂是食堂。");
    //     random_label.append(" 食堂 ");
    //     random_label.append(" 食堂 ");
    //     random_label.append(" 食堂 ");
    //     random_label.append(" 食堂 ");
    //     random_label.append(" 食堂 ");

    //     random_name.append("一宿舍");
    //     random_name.append("二宿舍");
    //     random_name.append("三宿舍");
    //     random_name.append("四宿舍");
    //     random_name.append("五宿舍");
    //     random_intro.append("一宿舍是一所宿舍。");
    //     random_intro.append("二宿舍是宿舍。");
    //     random_intro.append("三宿舍是宿舍。");
    //     random_intro.append("四宿舍是新中国第514所邮电高等宿舍。");
    //     random_intro.append("五宿舍是宿舍。");
    //     random_label.append(" 宿舍 ");
    //     random_label.append(" 宿舍 ");
    //     random_label.append(" 宿舍 ");
    //     random_label.append(" 宿舍 ");
    //     random_label.append(" 宿舍 ");

    //     random_name.append("小花园");
    //     random_intro.append("小花园是一所啸公园。");
    //     random_label.append(" 花园 ");

    //     random_name.append("小车棚");
    //     random_intro.append("小花园是一所啸车棚子。");
    //     random_label.append(" 车棚 ");

    //     random_name.append("小理发店");
    //     random_intro.append("小花园是一所啸理发店子。");
    //     random_label.append(" 理发店 ");

    //     random_name.append("小快递站");
    //     random_intro.append("小花园是一所啸快递站子。");
    //     random_label.append(" 快递站 ");

    //     random_name.append("小保卫处");
    //     random_intro.append("小花园是一所啸保卫处。");
    //     random_label.append(" 保卫处 ");
    // }

    // void reset_one_row(int n ){
    //     int rand_n = (1*n + 2 + rand()) % random_name.length();
    //     std::string  name = random_name.get( rand_n ) +" id:" + std::to_string(n)  ;
    //     std::string  intro = random_intro.get( rand_n ) +" id:" + std::to_string(n)  ;
    //     std::string  label = random_label.get( rand_n )   ;

    //     ((ChunkList<int>*)columns ->get(0))->set(n,n);
    //     ((ChunkList<std::string>*)columns ->get(1))->set(n,name);
    //     ((ChunkList<std::string>*)columns ->get(2))->set(n,intro);
    //     ((ChunkList<std::string>*)columns ->get(3))->set(n,label);
    //     ((ChunkList<int>*)columns ->get(4))->set(n,2 + rand()%45);
    // }

    // void  reset_random  () {
    //     int len = _get_length();
    //     for(int i = 0 ; i<len ;i+=1){
    //         reset_one_row(i);
    //     }
    // } 

    // int save(std::string &address){
    //     std::cout<<"saving\n";
    //     clear_data();
    //     std::cout<<"cleared\n";

    //     ((ChunkList<int>*)columns ->get(0))->append(0);
    //     ((ChunkList<std::string>*)columns ->get(1))->append("111");
    //     ((ChunkList<std::string>*)columns ->get(2))->append("kkk");
    //     ((ChunkList<std::string>*)columns ->get(3))->append("aaa");
    //     ((ChunkList<int>*)columns ->get(4))->append(114);

    //     std::cout<<"append1\n";
    //     append_to_n_row(100);
    //     std::cout<<"append100\n";
    //     reset_random();
    //     std::cout<<"write\n";
    //     auto csv_writer = new CSVWriter(address.data());
    //     if ( csv_writer == nullptr || !csv_writer->is_open()){return 1 ;}
     
    //     csv_writer->write_row_num(((ChunkList<int>*)(columns->get(0)))->length());
    //     _save_content(csv_writer); 
     
    //     csv_writer->close();
    //     std::cout<<"writeclose\n";
    //     return 0;
    // }




    TablePlace():TableBase(){
        add_int_column("index");
        add_string_column("name");
        add_string_column("instruction");
        add_string_column("label");
        add_int_column("likes");
        // load_random();
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
