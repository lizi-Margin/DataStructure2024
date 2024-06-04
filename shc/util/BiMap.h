#ifndef BIMAP_H
#define BIMAP_H
#include <string>
#include "List.h"
#include "Queue.h"

/* shc2024 */

template<class tk,class tv>
class BiMap
{
public:
    /* get index */
    virtual tv   get(tk key)=0;
    virtual ChunkList<tk>   get(tv value)=0;
    /* add */
    virtual void  insert (tk key, tv value)= 0;

    virtual bool  has(tk key)=0;
    virtual bool  has(tv value)=0;

    virtual void  remove(tk key)=0;
};






#define TRIE_MAX_INDEX 5000
/* Map: string-int key-value map. */
class StringChunkList:public ChunkList<std::string>{
private:
    /* data */
    bool ac_built = false;
    void _check_ac_build(){
        if (! ac_built){
            _build_ac();
            ac_built = true;
        }
    }
    void _check_ac_rebuild(){
        if (ac_built){
            _rebuild_ac();
            ac_built = false;
        }
    }
    void _rebuild_ac(){
        _init_ac();
        for (int i = 0; i < len; i  +=1 ){
            _insert_ac(_get(i).data(),i);
        } 
    }



    // ChunkList<ChunkList<int>> kmp_next;

    ChunkList<int> _get_kmp_next(std::string str)
    {
        int len = (str).length();               
        ChunkList <int> next;            
        for (int i = 0 ; i <len ; i+=1) next.append(0);
        for(int i = 1; i < len; i+=1)
        {
            int k = next.get(i-1);           
            while(k > 0 && str[i] != str[k]) 
                k = next.get(k-1);
            if(str[i] == str[k])             
                k++;
            next.set(i,k) ;                  
        }
        return next;
    }

    int _kmp_search(std::string target, std::string pattern,ChunkList<int> &next)
    {
        int k = 0;                                  
        int res = -1;                               
        for(int i = 0; i < (int)(target).length(); i++)
        {
            while(k > 0 && target[i] != pattern[k])    
                k = next.get(k - 1);
            if(target[i] == pattern[k])                
                k++;
            if(k == (int)(pattern).length())           
            {
                res = i - k + 1;                     
                k = next.get(k - 1);                   
            }
        }
        return res;
    }




	int trie[TRIE_MAX_INDEX][256];  
	// int pure_trie[TRIE_MAX_INDEX][256];  
	int fail[TRIE_MAX_INDEX];      
	ChunkList<int> trie_end_string_index[TRIE_MAX_INDEX];     
    // ChunkList<int> trie_node_string_index[TRIE_MAX_INDEX];
	int trie_node_index_cnt;        
	


	void _init_ac(){
		trie_node_index_cnt = 0;
		memset(trie, 0, sizeof(trie));
		// memset(pure_trie, 0, sizeof(pure_trie));
		memset(fail, 0, sizeof(fail));
        //  for(int i = 0 ; i < TRIE_MAX_INDEX;i+=1) {
        //      if (trie_node_string_index[i].length()>0) trie_node_string_index[i].clear();
        //  }
	}

	void _insert_ac(char *s,int string_index)  
	{
		int i;
		int len = strlen(s);
		int now = 0;       
		for (i = 0; i < len; i++){
			int v = s[i] + 128;
			if (trie[now][v] == 0){
				trie_node_index_cnt++;
				trie[now][v] = trie_node_index_cnt;
				// pure_trie[now][v] = trie_node_index_cnt;
			}
            // trie_node_string_index[now].append(string_index);
			now = trie[now][v];
		}

        trie_end_string_index[now].append( string_index);
        
	}

	void _build_ac(){
	    Queue<int> q;		   
		int i;
		for (i = 0; i < 256; i++){
			if (trie[0][i] != 0){
				fail[trie[0][i]] = 0;
				q.push(trie[0][i]);
			}
		}
		while (!q.empty()){
			int u = q.front();
			q.pop();
			for (i = 0; i < 256; i++){
				if (trie[u][i] != 0){
					fail[trie[u][i]] = trie[fail[u]][i];
					q.push(trie[u][i]);
				}
				else{
					trie[u][i] = trie[fail[u]][i];
				}
                // trie_node_string_index[trie[u][i]].append(trie_node_string_index[ fail[trie[u][i]] ]);
			}
		}
	}
    
    // ChunkList<int> _get_string_index(int now){
    //     ChunkList<int>  result;
    //     bool visited[TRIE_MAX_INDEX];
    //     memset(visited,0,sizeof(visited));
    //     int e;
    //     std::queue<int> bfs_q;
    //     bfs_q.push(now);//把第一个顶点入队
    //     visited[now] = 1;//标记第一个顶点
        
    //     while (!bfs_q.empty()) {
    //         e = bfs_q.front();
    //         bfs_q.pop();

    //         int i  = 0; 
    //         while (i < 256) {
    //             int p = trie[e][i];

    //             for(int ii = 0;ii< trie_end_count[p];ii +=1){
    //                 if (!result.has(trie_end_string_index[p][ii]))result.append(trie_end_string_index[p][ii]);
    //             }

    //             for (int j = 0 ; j <256 ;j+=1){
    //                 if (!visited[trie[p][j]]) {
    //                     bfs_q.push(trie[p][j]);
    //                     visited[trie[p][j]] = 1;
    //                 }
    //             }
    //             i+=1;
    //         }
    //     }
    //     return result;

    // }

public:    














    StringChunkList(): ChunkList(){
        _init_ac();
    }
    explicit  StringChunkList(int node_cap): ChunkList( node_cap){
        _init_ac();
    }
    explicit  StringChunkList (const StringChunkList* copy_target): ChunkList(copy_target){ 
        _init_ac();
    }

    
    void append(std::string stuff)override{ 
        _check_ac_rebuild();

        ChunkList::append(stuff);
        _insert_ac(stuff.data(),len-1);
    }
    void set(int index,std::string value)override{
        ChunkList::set(index,value);
        _rebuild_ac(); 
    }
    void clear()override{
        ChunkList::clear();
        _init_ac();
    }
    ~StringChunkList(){
        ChunkList::~ChunkList();
        // delete[] trie;  
        // delete[] fail;      
        // delete[] trie_end_count ;     //结束标志
    }

    // ChunkList<int>* search_target(std::string s){
    //     _check_ac_build();

    //     for(int i = 0 ; i < TRIE_MAX_INDEX;i+=1) {
    //         if (trie_node_string_index[i].length()>0) trie_node_string_index[i].print();
    //     }


	// 	int i, j;
	// 	int slen = s.length();
	// 	int now = 0;
	// 	// int ans_num = 0;
    //     bool solve_mark[TRIE_MAX_INDEX];
    //     memset(solve_mark,0,sizeof(solve_mark));
    //     auto * ans = new ChunkList<int>(40);

    //     for (int i = 0; i < slen; i+=1) {
    //         char symbol = s[i];
    //         while (now && (trie[now][symbol]<=0)) {
    //             now = fail[now];                
    //         }
    //         if ((trie[now][symbol]<=0)) {
    //             now = trie[now][symbol];
    //         } else {
    //             now = 0;
    //         }
    //         if (trie_node_string_index[now].length()>0) {
    //             ans->append(trie_node_string_index[now]);
    //         }
    //     }

	// 	return ans;
        
    // }

    // ChunkList<int>* search_target(std::string s){
    //     _check_ac_build();
        
    //      for(int i = 0 ; i < TRIE_MAX_INDEX;i+=1) {
    //        trie_node_string_index[i].print();
    //      }
	// 	int i, j;
	// 	int slen = s.length();
	// 	int now = 0;
	// 	// int ans_num = 0;
    //     bool solve_mark[TRIE_MAX_INDEX];
    //     memset(solve_mark,0,sizeof(solve_mark));
    //     auto * ans = new ChunkList<int>(40);
    //     for (int i = 0; i < slen; i+=1) {
    //         char symbol = s[i];
    //         while (now && (pure_trie[now][symbol]<=0)) {
    //             now = fail[now];                
    //         }
    //         if ((trie[now][symbol]>0)) {
    //             now = trie[now][symbol];
    //             ans->append(trie_node_string_index[now]);
    //         } else {
    //             now = 0;
    //         }
            
    //     }
	// 	return ans;
    // }


    ChunkList<int> search_target(std::string s){
        // _check_ac_build();
        ChunkList<int> pattern_next = _get_kmp_next(s);
        ChunkList<int> reselt(400);
        for (int i = 0 ; i < len ;i+=1){
            if (_kmp_search(_get(i),s,pattern_next )>=0){
                reselt.append(i);
            }
        }
        return reselt;
    }



    ChunkList<int> search_pattern(std::string s){
        _check_ac_build();

		int i, j;
		int slen = s.length();
		int now = 0;
		// int ans_num = 0;
        bool solve_mark[TRIE_MAX_INDEX];
        memset(solve_mark,0,sizeof(solve_mark));
        ChunkList<int> ans (400);

		for (i = 0; i < slen; i++){
			now = trie[now][s[i] + 128];
			for (j = now; j && !solve_mark[j]; j = fail[j]){
                if (trie_end_string_index[j].length()>0){
				    // ans_num = ans_num + trie_end_count[j];
                    for(int ii = trie_end_string_index[j].length()-1 ; ii>=0 ; ii-=1){
                        ans.append(trie_end_string_index[j].get(ii));
                    }
                }
                solve_mark[j] = 1;
			}
		}        
		return ans;
    }

    int get_index(std::string s){      
        _check_ac_build();

		int i, j;
		int slen = s.length();
		int now = 0;
		// int ans_num = 0;
        bool solve_mark[TRIE_MAX_INDEX];
        memset(solve_mark,0,sizeof(solve_mark));
        auto * ans = new ChunkList<int>(40);
        int slen_minus_one = slen -1;
		for (i = 0; i < slen_minus_one; i++){
			now = trie[now][s[i] + 128];
			for (j = now; j && !solve_mark[j]; j = fail[j]){
                solve_mark[j] = 1;
			}
		}

		now = trie[now][s[i] + 128];
		for (j = now; j && !solve_mark[j]; j = fail[j]){
            if (trie_end_string_index[j].length()>0){
                for(int ii = trie_end_string_index[j].length()-1 ; ii>=0 ; ii-=1){
                    if (_get( trie_end_string_index[j].get(ii)).length() == slen ){
                        return trie_end_string_index[j].get(ii);
                    }
                }
            }
            solve_mark[j] = 1;
        }      
		return -1;
    }
};







class IntStringBiMap:public StringChunkList{
public:

    IntStringBiMap (): StringChunkList(400){}
    explicit  IntStringBiMap (int node_cap): StringChunkList( node_cap){}
    
    ChunkList<int>   get(std::string value){
        ChunkList<int> res_pattern = search_pattern(value);
        ChunkList<int> res_target = search_target(value);
        int len_res_pattern = res_pattern.length();
        for (int i= 0 ; i< len_res_pattern ;i +=1){
            int this_ind = res_pattern.get(i);
            if (! res_target.has(this_ind)){
                res_target.append(this_ind);
            }
        }

        return res_target;
    }
};








# endif