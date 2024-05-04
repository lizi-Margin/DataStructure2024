# ifndef _LIST_H_
# define _LIST_H_

template<class type>
class List{
public:
    virtual void append(type stuff)=0;
    virtual type get(int index)=0;
    virtual int  length()=0;
};


# define DEFAULT_CHUNKNODE_CAPACITY 5

template<class type>
class ChunkListNode{
public:
    type ** main_list ;
    ChunkListNode * next ;
    ChunkListNode ( );// FORBIDEN!!!
    ChunkListNode ( const int cap);
    ChunkListNode (const int cap ,ChunkListNode<type>* n );
    ~ChunkListNode ();
};

template<class type>
class ChunkList:public List<type>{
public:

    /* info */
    int node_capacity;
    int len ;
    int node_used ; 

    ChunkListNode<type> * first;

    ChunkList();
    ChunkList(const int node_capacity);
    ~ChunkList();

    void append(type content)override;
    type get(int index)override;
    int length()override; 

};


#endif 