# ifndef QUEUE_H
# define QUEUE_H
//65
#include <string>
#include "List.h"


template<class type>
class Queue:public ChunkList<type>{
public:
    Queue():ChunkList<type>(40){}
    Queue(int cap):ChunkList<type>(cap){}

    bool empty(){
        return ChunkList<type>:: len <=0;
    }
    type front(){
        return ChunkList<type>::_get(ChunkList<type>::len -1 );
    }

    void push(type value){
        ChunkList<type>::append(value);
    }

    void pop(){
        ChunkList<type>::pop_back();
    }

};




#endif