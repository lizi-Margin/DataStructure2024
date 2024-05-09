#ifndef TABLE_BASE_H
#define TABLE_BASE_H
#include <string>
#include <iostream>
#include <utility>
#include "File.h"
#include "List.h"

/* shc2024 */

class TableBase {
protected:
    ChunkList<void*> * columns;
    ChunkList<std::string> * column_names;
    ChunkList<int> * column_type;/* 0-int 1-string*/

    int _load_content (CSVReader* csv_reader,int length){
        if (!csv_reader->is_open()){return  1;}
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

    int _load_matrix_content(CSVReader* csv_reader,int row_num){
        if (!csv_reader->is_open()){return  1;}
        for ( int i = 0 ; i < row_num ; i++){
            add_int_column("matrix_int_col");
        }
       return _load_content(csv_reader,row_num) ;
    }

    int _save_content(CSVWriter* csv_writer){
        int col_num_minus_1 = columns->length() -1 ;
        if (col_num_minus_1 < 0 ) {return 0;}
        if (! csv_writer->is_open() ) {return 1;}

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

    int _get_max_int(int column_index){
        if (column_index>= columns->length() || column_index <0||_get_length()<=0||column_type->get(column_index)!=0) {return -1;}
        int max_int = _get_int(0,column_index);
        for (int i = 1 ; i<_get_length(); i+=1){
            int this_int = _get_int(i,column_index);
            if(this_int >max_int){
                max_int = this_int;
            }
        }
        return  max_int;
    }

    /*return max int row index */
    int _get_max_int_index(int column_index){
        if (column_index>= columns->length() || column_index <0||_get_length()<=0||column_type->get(column_index)!=0) {return -1;}
        int max_int = _get_int(0,column_index);
        int max_int_index = 0;
        for (int i = 1 ; i<_get_length(); i+=1){
            int this_int = _get_int(i,column_index);
            if(this_int >max_int){
                max_int = this_int;
                max_int_index = i;
            }
        }
        return  max_int_index;
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



    int _get_nst_value_index(int value,int value_col,int n){
        int col_num_minus_1 = columns->length() -1 ;
        int length = _get_length();
        if (col_num_minus_1 < 0 || value >=length) {return -1;}
        int count = 0;
        for ( int i = 0 ; i < length ; i++){
            if (value == _get_int(i, value_col)){
                if (count == n){
                    return  i;
                }
                count +=1;
            }
        }
        return -1 ;
    }




public:
    TableBase(){
        columns = new ChunkList<void*>(5);
        column_names = new ChunkList<std::string>(5);
        column_type = new ChunkList<int>(5); 
    }


















    explicit TableBase(const TableBase* table){
        column_names = new ChunkList<std::string>((ChunkList<std::string>)table->column_names) ;
        column_type = new ChunkList<int>((ChunkList<int>)table->column_type) ;
        columns = new ChunkList<void*>();
        for (int i = 0 ;i < table->columns->length();i+=1){
            if (column_type->get(i)==0){
                columns->append(new ChunkList<int>((ChunkList<int>*)table->columns->get((i)))) ;
            }else{
                columns->append(new ChunkList<std::string>((ChunkList<std::string>*)table->columns->get((i)))) ;
            }
        }
    };


    void clear(){

        columns->clear();
        column_type->clear();
        column_names->clear();
    }


    void clear_data(){
        for(int i = 0 ; i < columns->length();i += 1){
            if (column_type->get(i) == 0){
                auto column = (ChunkList<int>*) columns->get(i);
                column->clear();
            }else{
                auto column = (ChunkList<std::string>*) columns->get(i);
                column->clear();
            }
        }
    }

    ~TableBase(){
        delete  columns ;
        delete column_names ;
        delete column_type ; 
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


    int load(std::string &address,int row_num){
        auto csv_reader = new CSVReader(address.data());
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}
        csv_reader->read_line();//read column
        _load_content(csv_reader,row_num);
        csv_reader -> close();
        // print_table();
        return 0 ;
    }

    int load(std::string &address){
        auto csv_reader = new CSVReader(address.data());
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}
        int row_num = csv_reader->read_row_num();
        csv_reader->read_line();//read column
        _load_content(csv_reader,row_num);
        csv_reader -> close();
        // print_table();
        return 0 ;
    }

    int save(std::string &address){
        auto csv_writer = new CSVWriter(address.data());
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
        for (int i = 0 ; i <length ; i +=1) {

            for (int j = 0; j < columns->length(); j += 1) {
                if (column_type->get(j) != 0) {
                    std::string *s = _get_string(i, j);
                    std::cout << *s << " ";
                    delete s;

                } else {
                    std::cout << (_get_int(i, j)) << " ";
                }
            }
            std::cout << "\n";

        }
    }

    void print(){print_table();}
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

        return _get_nst_value_index(index, 1, comment_index);
    }
public:
    TablePlaceComments():TableBase(){
        add_int_column("index");
        add_int_column("place_index");
        add_string_column("content");
        add_int_column("likes");
    }
    explicit  TablePlaceComments(TablePlaceComments* tb):TableBase(tb){}
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

class TableToursite:public TableBase{
public:
    TableToursite():TableBase(){
        add_int_column("index");
        add_string_column("name");
        add_string_column("introduction");
        add_int_column("place_num");
        add_int_column("likes");
    }
    void append_one_row(){
        auto col = ((ChunkList<int>*)columns->get(0));
        col ->append(col ->get(col->length()-1)+1);
        for(int i = 1 ; i< columns->length();i+=1){
            if (column_type->get(i) == 0){
                col = ((ChunkList<int>*)columns->get(i));
                col ->append(col ->get(col->length()-1));
            }else{
                auto cols = ((ChunkList<std::string>*)columns->get(i));
                cols ->append(cols ->get(cols->length()-1));
            }
        }
    }
    void append_n_row(int n){
        for(int i = 0; i<n ;i +=1){
            append_one_row();
        }
    }
};

class TableRoute:public  TableBase{
protected:
//    int[][]  _get_int2d_matrix_with_value(int column_index,int default_value = 0){
//        if (column_index>= columns->length() || column_index <0) {return nullptr;}
//        int a = _get_max_int(1);
//        int b = _get_max_int(2);
//        int matrix_side_length = std::max(a,b);
//        auto matrix = new int*[matrix_side_length];
//        for (int i = 0 ;i < matrix_side_length; i+=1){
//            matrix[i] = new int[matrix_side_length];
//            for (int j=0 ; j<matrix_side_length ;j+=1){
//                matrix[i][j] = default_value;
//            }
//        }
//        for (int i = 0 ;i < _get_length(); i+=1){
//            int from = _get_int(i,1);
//            int to = _get_int(i,2);
//            int value = _get_int(i,column_index);
//            matrix[from][to] = value;
//            matrix[to][from] = value;
//        }
//        return matrix;
//    }
    int ** _get_intxx_matrix_with_value(int column_index,int default_value = 0,bool use_default_self_value = false,int default_self_value = 0){
        if (column_index>= columns->length() || column_index <0) {return nullptr;}
        int a = _get_max_int(1);
        int b = _get_max_int(2);
        int matrix_side_length = std::max(a,b)+1;
        auto matrix = new int*[matrix_side_length];
        for (int i = 0 ;i < matrix_side_length; i+=1){
            matrix[i] = new int[matrix_side_length];
            for (int j=0 ; j<matrix_side_length ;j+=1){
                matrix[i][j] = default_value;
            }
        }
        if (use_default_self_value){
            for (int i = 0 ;i < matrix_side_length; i+=1){
                matrix[i][i] = default_self_value;
            }
        }
        for (int i = 0 ;i < _get_length(); i+=1){
            int from = _get_int(i,1);
            int to = _get_int(i,2);
            int value = _get_int(i,column_index);
            matrix[from][to] = value;
            matrix[to][from] = value;
        }

        return matrix;
    }
public:
    TableRoute():TableBase(){
        add_int_column("index");
        add_int_column("from_place_index");
        add_int_column("to_place_index");
        add_int_column("length");
        add_int_column("congestion");
        add_int_column("walk_access");
        add_int_column("bike_access");
        add_int_column("ebike_access");
    }

    explicit  TableRoute(TableRoute* tb):TableBase((TableBase*)tb){}

    int ** get_intxx_adj_matrix(){
        return _get_intxx_matrix_with_value(3,1000, true,0);
}
    int ** get_intxx_congestion_matrix(){
        return _get_intxx_matrix_with_value(4,0);
    }
    int ** get_intxx_walk_matrix(){
        return _get_intxx_matrix_with_value(5,1);
    }
    int ** get_intxx_bike_matrix(){
        return _get_intxx_matrix_with_value(6,0);
    }
    int ** get_intxx_ebike_matrix(){
        return _get_intxx_matrix_with_value(7,0);
    }


    void add_route(int from,int to , int length , int cong ,int walk_access,int bike_access,int ebike_access){
        ((ChunkList<int>*)columns->get(0)      ) ->append(_get_length());
        ((ChunkList<int>*)columns->get(1)      ) ->append(from);
        ((ChunkList<int>*)columns->get(2)      ) ->append(to);
        ((ChunkList<int>*)columns->get(3)      ) ->append(length);
        ((ChunkList<int>*)columns->get(4)      ) ->append(cong);
        ((ChunkList<int>*)columns->get(5)      ) ->append(walk_access);
        ((ChunkList<int>*)columns->get(6)      ) ->append(bike_access);
        ((ChunkList<int>*)columns->get(7)      ) ->append(ebike_access);
    }
};


class TableMatrixRoute:public  TableBase{
protected:
public:
    TableMatrixRoute():TableBase(){}

    explicit  TableMatrixRoute(TableMatrixRoute* tb):TableBase((TableBase*)tb){}


    int load_matrix(std::string &address) {
        auto csv_reader = new CSVReader(address.data());
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}
        clear();
        int row_num = csv_reader->read_row_num();
        csv_reader->read_line();
        int ret=  _load_matrix_content(csv_reader,row_num);
        csv_reader->close();
        return  ret;
    }

    int load_matrix(std::string &address,int row_num) {
        auto csv_reader = new CSVReader(address.data());
        if ( csv_reader == nullptr || !csv_reader->is_open()){return 1 ;}



        clear();

        csv_reader->read_line();

        int ret= _load_matrix_content(csv_reader,row_num);
        csv_reader->close();
        return  ret;
    }

    TableRoute* get_route_table(){
            auto new_tb = new TableRoute();
            for (int j = 0;j< columns->length();j+=1){
                for(int i=j+1; i<columns->length();i+=1){
                    new_tb->add_route(i,j, _get_int(i,j),2,1,1,0);
                }
            }
            return  new_tb;
    }

};
#endif