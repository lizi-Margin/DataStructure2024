# ifndef DATABASEIF_H
# define DATABASEIF_H
# include <string>
/* 
  Interface for M1 database.
  ALL definitions here below.
  shc 2024
*/
/* 全部接口均已完成 2024.5.10 */

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
  /* 路径拥塞程度图 (>=0) */
  int** adjacent_matrix_congestion;
  /* 移动方式可行邻接图 (0/1标识不可行/可行) */
  int** adjacent_matrix_walk;
  int** adjacent_matrix_bike;
  int** adjacent_matrix_ebike;
};

class  Database_IF{
public:
    /* Database interface 已通过测试的接口 */
    /* 释放数据库内存 */
    virtual int release_database() = 0;
    /* 保存一切数据 */
    virtual int save_all() = 0;
    /* 从指定路径导入, 返回值判断是否成功 */
    virtual int load_database(std :: string relative_address) = 0; 
    /* 查询景点数 */
    virtual int get_toursite_amount()  = 0;
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
    virtual std::string* get_toursite_diary(int index,int diary_index)  = 0; 
    /* 查询景点日记点赞数 */ 
    virtual int get_toursite_diary_like_num(int index,int diary_index)  = 0; 


    /* 查询景点美食数 */ 
    virtual int get_toursite_food_num(int index)  = 0;  
    /* 查询景点美食 */ 
    virtual std::string* get_toursite_food_name(int index,int food_index)  = 0; 
    virtual std::string* get_toursite_food_label(int index,int food_index)  = 0; 
    /* 查询景点美食点赞数 */ 
    virtual int get_toursite_food_like_num(int index,int food_index)  = 0; 

    /* 查询场所评价数 */ 
    virtual int get_place_comment_num(int index , int place_index)  = 0;  
    /* 查询场所评价 */ 
    virtual std::string* get_place_comment(int index,int place_index,int comment_index)  = 0; 
    /* 查询场所评价点赞数 */ 
    virtual int get_place_comment_like_num(int index,int place_index,int comment_index)  = 0;
};
#endif