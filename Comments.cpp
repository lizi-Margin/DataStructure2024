#include "Comments.h"

Comments:: Comments(){
    this -> comments_num = 0;
    this -> node_used = 0;
    this -> nodes = nullptr;
}
Comments :: ~Comments(){

    this -> nodes = nullptr;
}
Comments::Comment_node::Comment_node (){
    this-> main_list = new  std:: string *[NODE_CAPACITY];
    this-> next_comment_node = nullptr ;
}
Comments::Comment_node::Comment_node (Comment_node* next){
    this-> main_list = new  std:: string *[NODE_CAPACITY];
    this-> next_comment_node = next ;
}
void Comments:: add_comment(std::string* content){
    this -> comments_num +=1;
    int index = (this->comments_num) - node_used* NODE_CAPACITY;
    if (index > 0 ){
        this->node_used +=1;
        index -= 1;
        Comment_node *  new_node = new Comment_node(this->nodes);
 
        this->nodes = new_node;
        new_node-> main_list[index] = content;

    }else{
        index +=4 ;
        this->nodes->main_list[index] = content;
    }
}
int Comments::  get_comments_num(){
    return this-> comments_num ;
}
std:: string* Comments :: get_comment(int index){
    if ( index >= this-> comments_num|| index <0 ) { return nullptr;}
    int reminder = index % NODE_CAPACITY;
    int node_index = index / NODE_CAPACITY;
    Comment_node * p = this -> nodes;
    for (int i = 0 ; i < node_index ; i +=1){
        p  = p->next_comment_node;
    }
    return p->main_list[reminder];
} 
