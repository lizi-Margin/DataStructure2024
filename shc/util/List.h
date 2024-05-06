# ifndef _LIST_H_
# define _LIST_H_
# define DEFAULT_CHUNKNODE_CAPACITY 5
# include <iostream>

template<class type>
class List{
public:
    virtual void append(type stuff)=0;
    virtual type get(int index)=0;
    virtual int  length()=0;
    virtual void print()=0;
};




template<class t>
class ChunkListNode{
public:
    t * main_list ;
    ChunkListNode * next ;

    ChunkListNode ( ){// forbiden
        main_list = new  t[DEFAULT_CHUNKNODE_CAPACITY];
        next = nullptr ;
    }
    ChunkListNode ( int cap){
        main_list = new  t[cap];
        next = nullptr ;
    }
    ChunkListNode (int cap ,ChunkListNode<t>* n ){
        main_list = new  t[cap];
        next = n ;
    }

    ~ChunkListNode (){
        delete [] main_list ; 
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

    ChunkListNode<type> * first;
 
    type _get(int index){
        if ( index >= len || index <0 ) { return 0;}
        int reminder = index % node_capacity;
        int node_index =  (index) / node_capacity;
        int rev_node_index = node_used -  node_index -1 ;
        ChunkListNode<type> * p =  first;
        for (int i = 0 ; i < rev_node_index ; i +=1){
            p  = p->next;
        }
        return p->main_list[reminder];
    } 


public:
    ChunkList(){
        node_capacity = DEFAULT_CHUNKNODE_CAPACITY ;
        this -> len = 0;
        this -> node_used = 0;
        this -> first = nullptr;
    }

    ChunkList(int node_cap){
        if (node_cap <1){
            node_capacity = DEFAULT_CHUNKNODE_CAPACITY;
        }else{
            node_capacity =  node_cap;
        }
        this -> len = 0;
        this -> node_used = 0;
        this -> first = nullptr;
    }


    
    ~ChunkList(){
        delete[] first;
        first = nullptr;
    }


    void append(type content)override{
        len +=1;
        if ((len) - node_used* node_capacity> 0 ){
            node_used +=1;
            ChunkListNode<type> *  new_node = new ChunkListNode<type>(node_capacity,first); 
            first = new_node;

            new_node-> main_list[0] = content;

        }else{
            int index = (len-1) % node_capacity;
            //index += node_capacity - 1;
            first->main_list[index] = content;
        }
    }


    type get(int index)override{
        return _get(index);
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