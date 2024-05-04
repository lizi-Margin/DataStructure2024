# include "List.h"

template<class type>
ChunkList<type>:: ChunkList(){
    node_capacity = DEFAULT_CHUNKNODE_CAPACITY ;
    this -> len = 0;
    this -> node_used = 0;
    this -> first = nullptr;
}
template<class type>
ChunkList<type>:: ChunkList(const int node_cap){
    if (node_cap <1){
        node_capacity = DEFAULT_CHUNKNODE_CAPACITY;
    }else{
        node_capacity =  node_cap;
    }
    this -> len = 0;
    this -> node_used = 0;
    this -> first = nullptr;
}
template<class type>
ChunkList<type>:: ~ChunkList(){
    delete[] first;
    first = nullptr;
}


template<class type>
ChunkListNode<type>::ChunkListNode (){
    main_list = new  type[DEFAULT_CHUNKNODE_CAPACITY];
    next = nullptr ;
}template<class type>
ChunkListNode<type>::ChunkListNode (const int cap){
    main_list = new  type[cap];
    next = nullptr ;
}
template<class type>
ChunkListNode<type>::ChunkListNode (const int cap,ChunkListNode<type>* n ){
    main_list = new  type[cap];
    next = n ;
}
template<class type>
ChunkListNode<type>::~ChunkListNode ( ){
    delete [] main_list ; 
}


template<class type>
void ChunkList<type>:: append(type content){
    len +=1;
    int index = (len) - node_used* node_capacity;
    if (index > 0 ){
        node_used +=1;
        index -= 1;
        ChunkListNode<type> *  new_node = new ChunkListNode<type>(node_capacity,first);
 
        first = new_node;
        new_node-> main_list[index] = content;

    }else{
        index +=4 ;
        first->main_list[index] = content;
    }
}
template<class type>
int ChunkList<type>::  length(){
    return len ;
}
template<class type>
type ChunkList<type> :: get(int index){
    if ( index >= len || index <0 ) { return 0;}
    int reminder = index % node_capacity;
    int node_index = index / node_capacity;
    ChunkListNode<type> * p =  first;
    for (int i = 0 ; i < node_index ; i +=1){
        p  = p->next;
    }
    return p->main_list[reminder];
} 
