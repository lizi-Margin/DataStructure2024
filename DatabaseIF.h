# ifndef _DATABASEIF_H_
# define _DATABASEIF_H_
# include <string>
/* 
  Interface for M1 database.
  ALL definitions here below.
  shc 2024
*/

class Place {
public:
  virtual int  get_index()=0;
  virtual std::string* get_name()=0;
  virtual std::string* get_introduction()=0;
  virtual std::string* get_label()=0;
  virtual int get_like_num()=0;
  virtual int get_comments_num()=0;
};

struct ToursiteTopo
{
  int toursite_index ; 
  std :: string * toursite_name ;
  int  place_num;       // 顶点数 
  Place **  places;        // 顶点表
  int** adjacent_matrix;   

  int** adjacent_matrix_walk;   
  int** adjacent_matrix_bicicle;   
  int** adjacent_matrix_ebycicle;   

  int** adjacent_matrix_congestion;   
};

class  Database_IF{
public:
    /* 释放数据库内存 */
    virtual int release_database(void) = 0; 
    /* 从指定路径导入, 返回值判断是否成功 */
    virtual int load_database(std :: string relative_address) = 0; 
    /* 查询景点数 */
    virtual int get_toursite_amount(void)  = 0;
    /* 查询景点推荐度*/
    virtual int get_toursite_grade(int index)  = 0; 
    /* 查询景点名称 */ 
    virtual std::string* get_toursite_name(int index)  = 0; 
    /* 查询景点介绍 */ 
    virtual std::string* get_toursite_introduction(int index)  = 0; 
    /* 查询景点内场所数 */ 
    virtual int get_toursite_place_num(int index )  = 0;  
    /* 查询景点内部拓扑机构 */
    virtual ToursiteTopo * get_toursite_topo(int index) = 0; 
    /* 搜索: 使用字符串搜索景点, 返回景点索引 */
    virtual int *  get_toursites_index_by_search(std :: string str, int n)=0; /*search */
    /* 查询推荐的景点, 返回景点索引 */
    virtual int *  get_recommended_toursites_index(int n)=0; /* recommending func */

    /* 查询景点评价数 */ 
    virtual int get_toursite_comment_num(int index)  = 0;  
    /* 查询景点评价 */ 
    virtual std::string* get_toursite_comment(int index,int comment_index)  = 0; 
    /* 查询景点评价点赞数 */ 
    virtual int get_toursite_comment_like_num(int index,int comment_index)  = 0; 

    /* 查询景点日记数 */ 
    virtual int get_toursite_diary_num(int index)  = 0;  
    /* 查询景点日记 */ 
    virtual std::string* get_toursite_diary(int index,int comment_index)  = 0; 
    /* 查询景点日记点赞数 */ 
    virtual int get_toursite_diary_like_num(int index,int comment_index)  = 0; 

    /* 查询场所评价数 */ 
    virtual int get_place_comment_num(int index , int place_index)  = 0;  
    /* 查询场所评价 */ 
    virtual std::string* get_place_comment(int index,int place_index,int comment_index)  = 0; 
    /* 查询场所评价点赞数 */ 
    virtual int get_place_comment_like_num(int index,int place_index,int comment_index)  = 0; 
};

#endif