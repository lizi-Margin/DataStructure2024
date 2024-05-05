#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>
#include "../DatabaseIF.h"
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
    utils::print_2d_matrix(tp->adjacent_matrix,tp->place_num);
    utils::print_places(tp->places,tp->place_num);
}


}
# endif