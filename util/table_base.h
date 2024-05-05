#ifndef _TABLE_BASE_H_
#define _TABLE_BASE_H_
#include <string>
#include "File.h"
#include "List.h"


class TableBase {
protected:
    CSVReader * csv_reader;
    CSVWriter * csv_writer;
    ChunkList<void*> * columns;
    ChunkList<std::string> * column_names;
    ChunkList<int> * column_type;/* 0-int 1-string*/


public:
    TableBase(){
        csv_reader = nullptr;
        columns = new ChunkList<void*>(5);
        column_names = new ChunkList<std::string>(5);
        column_type = new ChunkList<int>(5); 
    }
    ~TableBase(){
        csv_reader = nullptr;
        delete  columns ;
        delete column_names ;
        delete column_type ; 
    }
    int init (std:: string* addr){
        csv_reader = new CSVReader(addr->c_str());        
        if (!csv_reader->is_open()){return 1 ;}
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
        column_type->append(0);
        return columns->length()-1;
    }
    int load (int length){
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}
		csv_reader->read_line();
		for ( int i = 0 ; i < length ; i++){
            for(int j =0 ; j < columns->length(); j+=1){
                if (column_type->get(j)!=0){                    
                    std::string* data;
                    csv_reader->read_colomn(data);
                    ChunkList<std::string>* col = (ChunkList<std::string>* )((columns) ->get(j));
                    col->append(*data);
                }else{
                    int data;
                    csv_reader->read_colomn(data);
                    ChunkList<int>* col = (ChunkList<int>* )((columns) ->get(j));
                    col->append(data);
                }
            }
		}
  
    return 0 ;
    }

    int save(){
        std::string addr = csv_reader->get_filename();
        csv_reader->close();
        csv_writer = new CSVWriter(addr.c_str());
    }

};

class TableComments:public TableBase{

};

class TableDiary:public TableBase{

};

#endif