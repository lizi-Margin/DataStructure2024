#ifndef TABLE_BASE_H
#define TABLE_BASE_H
#include <string>
#include <iostream>
#include <utility>
#include "File.h"
#include "List.h"


class TableBase {
protected:
    std::string * address;
    ChunkList<void*> * columns;
    ChunkList<std::string> * column_names;
    ChunkList<int> * column_type;/* 0-int 1-string*/

    int _load_content (CSVReader* csv_reader,int length){
        

        
		csv_reader->read_line();
        
		for ( int i = 0 ; i < length ; i++){
            for(int j =0 ; j < columns->length(); j+=1){
        
        
                if (column_type->get(j)!=0){                    
        
                    std::string* data;
        
                    csv_reader->read_colomn(data);
                    auto col = (ChunkList<std::string>* )((columns) ->get(j));
        
                    col->append(*data);
                }else{
        
                    int data;
                    csv_reader->read_colomn(data);
                    auto col = (ChunkList<int>* )((columns) ->get(j));
        
                    col->append(data);
                }
            }
        
		}
   return 0 ;
    }

    int _save_content(CSVWriter* csv_writer){
        int col_num_minus_1 = columns->length() -1 ;
        if (col_num_minus_1 < 0 ) {return 0;}

        int length = ((ChunkList<int>*)(columns->get(0)))->length();                
        for (int j = 0 ; j < col_num_minus_1 ; j+=1){ 
            std::string*s = _get_column_name(j);
            csv_writer ->write_colomn(s);
            delete s;
        }
        std::string* str = _get_column_name(col_num_minus_1);
        csv_writer ->write_last_colomn(str);
        delete str;

		for ( int i = 0 ; i < length ; i++){
            for(int j =0 ; j < col_num_minus_1; j+=1){
                
                if (column_type->get(j)!=0){                    
                    std::string * s =  _get_string(i,j);
                    csv_writer->write_colomn(s);
                    delete s;
                    
                }else{
                    csv_writer->write_colomn(_get_int(i,j));
                }           
            }
            if (column_type->get(col_num_minus_1)!=0){                    
                std::string * s =  _get_string(i,col_num_minus_1);
                csv_writer->write_last_colomn(s);
                delete s;
                
            }else{
                csv_writer->write_last_colomn(_get_int(i,col_num_minus_1));
            }           
		}
  
        return 0 ;
    }

    std::string * _get_string(int row,int col){
        auto c = (ChunkList<std::string>* )((columns) ->get(col));
        auto * s =  new std::string(c -> get(row));
        return s; 
    }
    int  _get_int(int row,int col){
        auto c = (ChunkList<int>* )((columns) ->get(col));
        return (c -> get(row)); 
    }
    std::string * _get_column_name(int col){
        auto * s =  new std::string(column_names -> get(col));
        return s; 
    }
    int _get_length(){
        int length = ((ChunkList<int>*)(columns->get(0)))->length();                
        return length;
    }
public:
    TableBase(){
        address = nullptr;
        columns = new ChunkList<void*>(5);
        column_names = new ChunkList<std::string>(5);
        column_type = new ChunkList<int>(5); 
    }
    ~TableBase(){
        delete address;
        delete  columns ;
        delete column_names ;
        delete column_type ; 
    }
    int init (std:: string addr){
        address  = new std:: string( std::move(addr));
        return 0;
    }
    int add_int_column(const char * col_name){
        column_names ->append (std::string (col_name));
        columns->append(new ChunkList<int>(5));
        column_type->append(0);
        return columns->length()-1;
    }    

    int add_string_column(const char * col_name){
        column_names ->append (std::string (col_name));
        columns->append(new ChunkList<std::string>(5));
        column_type->append(1);
        return columns->length()-1;
    }

    int load(){

        auto csv_reader = new CSVReader(address->data());
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}
 
        
        int row_num = csv_reader->read_row_num();
        _load_content(csv_reader,row_num);

        
        csv_reader -> close();
        // print_table();
        return 0 ;
    }
    int save(){
        auto csv_writer = new CSVWriter(address->data());
        if ( csv_writer == nullptr || !csv_writer->is_open()){return 1 ;}
        
        csv_writer->write_row_num(((ChunkList<int>*)(columns->get(0)))->length());
        _save_content(csv_writer); 

        
        csv_writer->close();
        return 0;
    }
    int get_length(){
        return _get_length();
    }

    void add_rows(TableBase* table){


    }
    void add_row(){

    }



    void print_table(){
        int length = ((ChunkList<int>*)(columns->get(0)))->length();
        std::cout<<"table: ";
        column_names->print(); 
        for (int i = 0 ; i <length ; i +=1){
            
            for (int j = 0 ; j < columns-> length()  ; j +=1){
                if (column_type->get(j)!=0){                    
                    std::string * s =  _get_string(i,j);
                    std::cout<<*s <<" ";
                    delete s;
                    
                }else{
                    std::cout<< (_get_int(i,j))<<" ";
                }           
            } 
            std::cout << "\n";
            
        }
    }
};

class TableComments:public TableBase{
public:
    TableComments():TableBase(){
        add_int_column("index");
        add_string_column("content");
        add_int_column("likes");
    }

    std::string * get_comment(int index){
        return _get_string(index,1);
    }
    int get_comment_like_num(int index){
        return _get_int(index,2);
    }   
};

class TablePlaceComments:public TableBase{
protected:
    int _get_place_comment_index(int index,int comment_index){
        int col_num_minus_1 = columns->length() -1 ;
        int length = _get_length();
        if (col_num_minus_1 < 0 || index >=length) {return -1;}
        int count = 0;
        for ( int i = 0 ; i < length ; i++){
            if (index == _get_int(i, 1)){
                if (count == comment_index){
                    return  i;
                }
                count +=1;
            }
        }
        return -1 ;
    }
public:
    TablePlaceComments():TableBase(){
        add_int_column("index");
        add_int_column("place_index");
        add_string_column("content");
        add_int_column("likes");
    }
    std::string * get_place_comment(int index,int comment_index){
       return _get_string(_get_place_comment_index(index,comment_index),2);
    }
    int get_place_comment_like_num(int index,int comment_index){
        return _get_int(_get_place_comment_index(index,comment_index),3);
    }

    int get_place_comment_num(int index){
        int col_num_minus_1 = columns->length() -1 ;
        if (col_num_minus_1 < 0 ) {return 0;}
        int length = _get_length();
        int count = 0;
        for ( int i = 0 ; i < length ; i++){
             if (index == _get_int(i, 1)){
                 count +=1;
             }
        }
        return count;
    }

};
class TableDiary:public TableBase{
public:
    TableDiary():TableBase(){
        add_int_column("index");
        add_string_column("content");
        add_int_column("likes");
    }

    std::string * get_diary(int index){
        return _get_string(index,1);
    }
    int get_diary_like_num(int index){
        return _get_int(index,2);
    }
};

#endif