#ifndef MAP_H
#define MAP_H
#include <string>
#include "List.h"


template<class tk,class tv>
class Map
{
public:
    virtual void  init(List<tk>* key_list,List<tv>* value_list)=0;
    /* get index */
    virtual int   get(tk key)=0;
    /* add */
    virtual void  insert (tk key, tv value)= 0;

    virtual bool  has(tk key)=0;
    virtual void  remove(tk key)=0;
};

class StringIntMap:public Map<std::string,int>
{
public:

};


# endif