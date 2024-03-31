# ifndef _DATABASEIF_H_
# define _DATABASEIF_H_
# include <string>
/* 
  Interface for M1 database.
  ALL definitions here below.
  shc 2024
*/
  const std::string abs_path ="c:/Users/33149/Desktop/pack/"; 
  const std::string toursite_table ="toursite_table.csv"; 
class Place {
public:
  virtual int  get_index();
  virtual std::string* get_name();
  virtual std::string* get_introduction();
  virtual std::string* get_label();
  virtual int get_like_num();
  virtual int get_comments_num();
};
struct ToursiteTopo
{
  int toursite_index ; 
  std :: string * toursite_name ;
  int  place_num;       // 顶点数 
  Place **  places;        // 顶点表
  int** adjacent_matrix;   
};
class  Database_IF{
public:

    virtual int release_database(void) = 0; /* 释放内存 */
    virtual int load_database(std :: string relative_address) = 0; /* 从指定路径导入, 返回值判断是否成功 */
    virtual int get_toursite_amount(void)  = 0;/* 景点数 */
    virtual int get_toursite_grade(int index)  = 0; /* 查询景点推荐度grade, grade或需单独维护 */
    
    virtual std::string* get_toursite_name(int index)  = 0; 
    virtual std::string* get_toursite_introduction(int index)  = 0; 
    virtual ToursiteTopo * get_toursite_topo(int index) = 0; /* 索取景点内部拓扑机构 */
    
    virtual int *  get_toursites_index_by_search(std :: string str, int n)=0; /*search */
    virtual int *  get_recommended_toursites_index(int n)=0; /* recommending func */
};

#endif