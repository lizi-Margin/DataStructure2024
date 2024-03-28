# ifndef _FILE_H_
# define _FILE_H_
# include<fstream>
# include<sstream>
# include<string>
# include<iostream>
# include"Toursite.h"

class File
{
private:
	std::string filename; // 配置文件
public:
	File(const char* fn = "file.txt")
		:filename(fn)
	{}
	~File(){delete &filename;}

	// 二进制读写 -- 简单高效，缺点：写到文件中的内容看不懂
	void write_bin(const char* content)
	{
		std::ofstream ofs(filename, std:: ios_base::out | std:: ios_base::binary);//定义一个文件流对象
		ofs.write((const char*)&content, sizeof(content));
	}
	std:: string * read_bin(int count)
	{
		std::ifstream ifs(filename, std:: ios_base::in |  std:: ios_base::binary);//定义一个文件流对象
        char s[count];
		ifs.read((char*)&s, sizeof(s));
        return new std:: string(s);
	}

    //文本读写
	void write_text(const std:: string* content)
	{
		std::ofstream ofs(filename);//定义一个文件流对象
		ofs << *content;
	}
	std::string * read_text(int count)
	{
		std:: ifstream ifs(filename);//定义一个文件流对象
        std:: string * s = new std:: string();
        s->resize(count);
		ifs >> *s;
        return s;
	}
	std::string * read_text(int count)
	{
		std:: ifstream ifs(filename);//定义一个文件流对象
        char * s = new char[count+1];
        for (int i= 0 ; i< count ; i+=1){
		    ifs.get(s[i]) ;
        }
		
        return new std::string(s);
	}

    std::string * read_to_character( const char character   ,const int buff_size = 50,const int max_len = 1e4)
    {
		std:: ifstream ifs(filename);
        char  buff [buff_size+1];
		std:: string * s = new std::string();
		while(s->length()<max_len){
	        for (int i= 0 ; i< buff_size ; i+=1){
				char ch;
			    ifs.get(ch) ;
				if(ch = character || '\n' || '\0') {
					s->append(std::string(buff));
					return s;}
				buff[i] = ch;
	        }
			s->append(std::string(buff));
		}	
		delete s;
		return nullptr;
    }       
	std::string * read_line(){
		return read_to_character('\n');
	}
    
    std::string * read_all()
    {
 	    std:: ifstream ifs(filename);
        std:: string * s = new std:: string();
        ifs>>*s;
        return s;
    }       
    

    void read_all_to_cout()
    {
        std::cout<<*read_all()<<std::endl;
    }
};

class ToursiteProxy: public File{
public:
	ToursiteProxy(const char* fn = "toursite_table.csv"): File(fn){}

	std:: string * read_colomn (std:: string * s){
		s = read_to_character(',');
		return s;
	}	
	int read_colomn (int &num){
		std:: string * s = read_to_character(',');
		std::istringstream ss(*s);
		ss >> num ;
		return num ;
	}	


	int init_toursite_list (const ToursiteRM ** list,const int len){
		read_line();
		for ( int i = 0 ; i < len ; i++){
			int index ;
			std:: string * name ;
			std:: string * introduction ;
			int place_num ;
			int likes;
			std:: string * address ;
			read_colomn(index);	
			read_colomn(name);	
			read_colomn(introduction);	
			read_colomn(place_num);	
			read_colomn(likes);	
			read_colomn(address);	

			list[i] = new  ToursiteRM(index,name,introduction,place_num,likes,address);
		}
		return 0 ;
	}
};

# endif