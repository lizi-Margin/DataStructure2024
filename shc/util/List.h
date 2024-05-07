# ifndef LIST_H
# define LIST_H
# define DEFAULT_CHUNKNODE_CAPACITY 5
# include <iostream>

/* shc2024 */

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


    ~ChunkList(){
        delete[] first;
        first = nullptr;
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

/* Map: string-int key-value map. */
class StringChunkList:public ChunkList<std::string>{
private:
    /* data */
public:
    
    explicit StringChunkList(int node_cap ):ChunkList(node_cap){}

    int get_index(std::string s);
    int search_index(std::string s);
};

#endif 