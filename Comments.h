#ifndef _COMMENTS_H_ 
#define _COMMENTS_H_
#define NODE_CAPACITY 5
#include<string>

/*
  A Linked list class for any kind of comment.
  shc 2024
*/

class  Comments {
public:
    int comments_num ;
    int node_used ; 
    class Comment_node{
    public:
      std:: string ** main_list ;
      Comment_node * next_comment_node ;
      Comment_node ();
      Comment_node (Comment_node* next);
      ~Comment_node ();
      };
    Comment_node * nodes;
    Comments();
    ~Comments();
    void add_comment(std::string* content);
    int get_comments_num();
    // 从最新的评论开始拿
    std:: string* get_comment(int index);
    };
#endif // !Comments