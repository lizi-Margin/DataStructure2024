# DS2024 - shc 
| 这个版本包含M1的所有文件,基本可用 (评价功能除外)。

## Test.cpp
<center><img src="./assets/test-0.png" alt="png" >
<p><span style="font-size: 8px;">test.cpp</span></p></center>

## Bugs
* 文件读取字符串过长会失败，暂时不支持更长的景点介绍。
* 评价功能未加入。
---
<center>DEBUGINGGG...</center>

## Development Log

### 2024.5.4 
* 新增自动加载景点信息功能，以实现动态加载。
* 修改了导致编译器'warning'的代码。
* 新增List和ChunkList。

### 2024.5.5 
* 新增数据结构ChunkList<>用于替代vector<>
* 新增TableBase用于加载关系型数据库表格
* 将开发: TableComments & TableDiary 用于加载评价表格和日记表格
* 正在开发: 将数据保存硬盘