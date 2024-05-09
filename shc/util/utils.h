#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include "../../DatabaseIF.h"
#include "List.h"

/*
    shc2024
*/

namespace  utils{

void static print_int_list (int* list ,int n){
    n = n-1;
    for (int i = 0 ;i < n ; i +=1){
        std:: cout << list[i]<<" ";
    }
    std:: cout << list[n]<<std:: endl;
}
void static print_places(Place** places,int n){
    for(int i = 0 ; i < n ; i+=1){
    std::cout<<"place_index: "<<places[i]->get_index();
    std::cout<<"   place_name: "<<*places[i]->get_name();
    std::cout<<"   place_like_num: "<<places[i]->get_like_num();
    std::cout<<"   place_comment_num: "<<places[i]->get_comments_num();
    std::cout<<"   place_introduction: "<<*places[i]->get_introduction()<<std::endl;
    }
}

void static print_2d_matrix(int** m,int place_n){
		for(int i = 0; i<place_n;i+=1){
			for(int j= 0; j<place_n ;j+=1){
				std::cout<<m[i][j]<<" ";
			}
				std::cout<<"\n";
		}
} 
void static print_topo_struct(ToursiteTopo * tp){
    std::cout<<"tousite_index: "<<tp->toursite_index;
    std::cout<<"   tousite_name: "<<*tp->toursite_name;
    std::cout<<"   place_num: "<<tp->place_num<<std::endl;
    std::cout<<" adj_matrix: "<<tp->place_num<<std::endl;
    utils::print_2d_matrix(tp->adjacent_matrix,tp->place_num);
    std::cout<<" congestion_matrix: "<<tp->place_num<<std::endl;
    utils::print_2d_matrix(tp->adjacent_matrix_congestion,tp->place_num);
    std::cout<<" walk_matrix: "<<tp->place_num<<std::endl;
    utils::print_2d_matrix(tp->adjacent_matrix_walk,tp->place_num);
    std::cout<<" bike_matrix: "<<tp->place_num<<std::endl;
    utils::print_2d_matrix(tp->adjacent_matrix_bike,tp->place_num);
    std::cout<<" ebike_matrix: "<<tp->place_num<<std::endl;
    utils::print_2d_matrix(tp->adjacent_matrix_ebike,tp->place_num);
    utils::print_places(tp->places,tp->place_num);
}
void static test_route_table(){
    std :: cout << "test routeTable start"<<std:: endl ;
    auto tb = new  TableMatrixRoute();
    std::string si = "C:/Users/33149/Desktop/DS2024/pack/shc/Database/0/adj_matrix.csv";
    std::string so = "C:/Users/33149/Desktop/DS2024/pack/shc/Database/1/routes.csv";

    tb ->load_matrix(si,6);
    auto rtb = tb ->get_route_table();
    rtb ->save(so);
    std :: cout << "test end"<<std:: endl ;
}



    int static use_interface(Database_IF * a ){

        // a.load_database(std :: string relative_address) = 0; /* 从指定路径导入, 返回值判断是否成功 */
        std:: cout << "景点数： " << a->get_toursite_amount() ;/* 景点数 */
        std:: cout <<   "\n";
        std:: cout << "一号景点推荐度： "<<   a->get_toursite_grade(1) ; /* 查询景点推荐度grade, grade或需单独维护 */
        std:: cout <<   "\n";
        std:: cout << "一号景点名字： "<<   *a->get_toursite_name(1)  ;
        std:: cout <<   "\n";
        std:: cout << "一号景点介绍： "<<   *a->get_toursite_introduction(1) ;
        std:: cout <<   "\n";
        std:: cout << "一号景点场所数： "<<   a->get_toursite_place_num(1) ;
        std:: cout <<   "\n";
        ToursiteTopo * tp = a->get_toursite_topo(399)   ;

        std:: cout << "399号景点拓扑结构地址： "<< tp   ; /* 索取景点内部拓扑机构 */
        std:: cout <<   "\n";
        utils::print_topo_struct(tp);
        std:: cout << "字符串搜索结果： "   ;
        utils::  print_int_list(  a->get_toursites_index_by_search("北", 20),20); /*search */
        std:: cout << "按推荐度推荐结果： "   ;
        utils:: print_int_list( a->get_recommended_toursites_index(20),20); /* recommending func */
        //a->release_database() ;/* 释放内存 */
        return 0;
    }

    int  static use_interface_extend(Database_IF * a ){
        std:: cout << "一号景点场所数： "<<   a->get_toursite_place_num(1) <<"\n";
        std:: cout << "一号景点日记数： "<<   a->get_toursite_diary_num(1) <<"\n";
        std:: cout << "一号景点日记0： "<<   *a->get_toursite_diary(1,0) <<"\n";
        std:: cout << "一号景点日记0点赞数： "<<   a->get_toursite_diary_like_num(1,0) <<"\n";
        std:: cout << "一号景点评论数： "<<   a->get_toursite_comment_num(1) <<"\n";
        std:: cout << "一号景点评论3： "<<   *a->get_toursite_comment(1,3) <<"\n";
        std:: cout << "一号景点评论3点赞数： "<<   a->get_toursite_comment_like_num(1,3) <<"\n";
        std:: cout << "一号景点1号场所评论数： "<<   a->get_place_comment_num(1,1) <<"\n";
        std:: cout << "一号景点1号场所评论0： "<<   *a->get_place_comment(1,1,0) <<"\n";
        std:: cout << "一号景点1号场所评论0点赞数： "<<   a->get_place_comment_like_num(1,1,0) <<"\n";
        return 0;
    }

    void static use_int_list(List<int> * list ){
        for (int i = 0 ; i < 20 ; i +=1){
            list->append(i);
        }
        list->print();
    }
    void static use_string_list(List<std::string> * list ){
        for (int i = 0 ; i < 20 ; i +=1){
            char s[2] ;
            s[0] = (char)i + 48;
            s[1] = '\0';
            list->append(std::string(s));
        }
        list->print();
    }

    void static extend_toursite_table(int from, int to ) {
        std::string abs_path = std::string("C:/Users/33149/Desktop/DS2024/pack/shc/Database/toursite_table.csv");
        TableToursite tb;
        tb.load(abs_path, from);
        tb.append_n_row(to-from);
        tb.save(abs_path);

    }

}
# endif