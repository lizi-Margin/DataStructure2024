# ifndef LIST_H
# define LIST_H
# define DEFAULT_CHUNKNODE_CAPACITY 100
# include <iostream>
# include<cstring>


/* shc2024 */

template<class type>
class List{
public:
    virtual void append(type stuff)=0;
    virtual type get(int index)=0;
    virtual void set(int index,type value)=0;
    virtual int  length()=0;
    virtual void print()=0;
    virtual void clear()=0;
};




template<class t>
class ChunkListNode{
public:
    t * main_list ;
    ChunkListNode * next ;

//    ChunkListNode ( ){// forbidden
//        main_list = new  t[DEFAULT_CHUNKNODE_CAPACITY];
//        next = nullptr ;
//    }
//    ChunkListNode ( int cap){
//        main_list = new  t[cap];
//        next = nullptr ;
//    }
    ChunkListNode (int cap ,ChunkListNode<t>* n ){
        main_list = new  t[cap];
        next = n ;
    }
//    explicit ChunkListNode(ChunkListNode<t>* copy_target ){

//        for (int i =0 ; i <DEFAULT_CHUNKNODE_CAPACITY ;i +=1){
//            main_list[i] = copy_target->main_list[i];
//        }
//        next = copy_target->next;
//    }
    void copy_main_list (int cap ,const ChunkListNode<t>* copy_target ){
        for (int i =0 ; i <cap ;i +=1){
            main_list[i] = copy_target->main_list[i];
        }
    }

    ~ChunkListNode (){
        delete next;
        delete[]  main_list ;
    }
};

template<class type>
class ChunkList:public List<type>{
    /*
        尾节点块状单链表
        用来替代vector
    */
protected:
    /* info */
    int node_capacity;
    int len ;
    int node_used ; 

    ChunkListNode<type> * first; // it is last actually
 
    type _get(int index){
        if ( index >= len || index <0 ) { return type() ;}
        int reminder = index % node_capacity;
        int node_index =  (index) / node_capacity;
        int rev_node_index = node_used -  node_index -1 ;
        ChunkListNode<type> * p =  first;
        for (int i = 0 ; i < rev_node_index ; i +=1){
            p  = p->next;
        }
        return p->main_list[reminder];
    }

    void _set(int index,type value){
        if ( index >= len || index <0 ) { return ;}
        int reminder = index % node_capacity;
        int node_index =  (index) / node_capacity;
        int rev_node_index = node_used -  node_index -1 ;
        ChunkListNode<type> * p =  first;
        for (int i = 0 ; i < rev_node_index ; i +=1){
            p  = p->next;
        }
        p->main_list[reminder] = value;
    }


public:
    ChunkList(){
        node_capacity = DEFAULT_CHUNKNODE_CAPACITY;
        len = 0;
        node_used = 0;
        first = nullptr;
    }

    explicit  ChunkList(int node_cap){
        if (node_cap <1){
            node_capacity = DEFAULT_CHUNKNODE_CAPACITY;
        }else{
            node_capacity =  node_cap;
        }
        len = 0;
        node_used = 0;
        first = nullptr;
    }

    explicit  ChunkList(const ChunkList<type>* copy_target){
        node_capacity = copy_target ->node_capacity;
        len = copy_target ->len;
        node_used = copy_target->node_used;
        if (node_used>0) {
            first = new ChunkListNode<type>(node_capacity, nullptr);
            first->copy_main_list(node_capacity,copy_target->first);
            ChunkListNode<type> * last = first;
            ChunkListNode<type> * their_p =copy_target->first;
            for (int i = 1; i < node_used; i += 1) {
                their_p = their_p->next;
                last->next = new ChunkListNode<type>(node_capacity, nullptr);
                last = last->next;
                last ->copy_main_list(node_capacity,their_p);
            }
        }
    }

    void clear()override{


        delete first;

        len = 0;
        node_used = 0;
        first = nullptr;
    }

    ~ChunkList(){
        delete first;
        first = nullptr;
    }

    int get_node_capacity(){
        return node_capacity;
    }

    void append(type content)override{
        len +=1;
        if ((len) - node_used* node_capacity> 0 ){
            node_used +=1;
            auto *  new_node = new ChunkListNode<type>(node_capacity,first);
            first = new_node;

            new_node-> main_list[0] = content;

        }else{
            int index = (len-1) % node_capacity;
            //index += node_capacity - 1;
            first->main_list[index] = content;
        }
    }

    void pop_back(){
        if (len <= 0 ){return;}
        len -=1;
        if (!(len - (node_used-1)* node_capacity> 0 )){
            node_used -=1;
            ChunkListNode<type> * last_first = first;
            first = first->next;

            last_first->next = nullptr;
            delete last_first;
        }    
    }

    void append(ChunkList<type> list){
        int list_len = list.length();
        for (int i = 0 ; i < list_len ; i +=1){
            append(list.get(i));
        }
    }

    bool has(type value){
        for (int i = 0 ; i < len ; i +=1){
            if (_get(i) == value) return true;
        }
        return false;
    }    

    type get(int index)override{
        return _get(index);
    }


    void set(int index,type value)override{
        if (index >=0 and index < len){
            _set(index,value);
        }
    }

    int length()override{
        return len ;
    }


    void print()override{
        // print_info();
        for(int i = 0 ; i < len ;i+=1 ){
            std:: cout << _get(i) << " ";
        }
        std:: cout << std::endl;
    }
    void print_info(){
        std::cout << "length :"<<len <<"  ";
        std::cout << "node_used :"<<node_used <<"  ";
        std::cout << "node_capacity :"<<node_capacity <<"\n";
    }
};


#endif 