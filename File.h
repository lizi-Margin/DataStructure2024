# ifndef _FILE_H_
# define _FILE_H_
# include<fstream>
# include<sstream>
# include<string>
# include<iostream>

class File
{
protected:
	std::string filename; // 配置文件
public:
	File(const char* fn )
		:filename(fn)
	{
	}
	~File(){
	//////////	delete &filename ; ///排了一夜的bug
		}

	bool is_open(){return 0;}

};
class OFile :public File{
protected:
	std::ofstream *ofs;//定义一个文件流对象
public:
	OFile(const char* fn )
		:File(fn)
	{
		ofs = new std::ofstream(filename);	
	}
	~OFile(){delete &filename ,&ofs;}

	bool is_open(){return ofs->is_open();}
	void close();
    //文本读写
	void write_text(const std:: string* content)
	{
		std::ofstream ofs(filename);//定义一个文件流对象
		ofs << *content;
	}

};

class IFile :public File{
protected:
	std::ifstream *ifs;//定义一个文件流对象
public:
	IFile(const char* fn )
		:File(fn)
	{
		ifs = new std::ifstream(filename);	
	}
	~IFile(){
		close();		
	//	delete &filename ;
		}

	bool is_open(){
		return ifs->is_open();}

	void close(){
		ifs->close();
		//delete &ifs;
		return;
	}

	// // 二进制读写 -- 简单高效，缺点：写到文件中的内容看不懂
	// void write_bin(const char* content)
	// {
	// 	std::ofstream ofs(filename, std:: ios_base::out | std:: ios_base::binary);//定义一个文件流对象
	// 	ofs.write((const char*)&content, sizeof(content));
	// }
	// char * read_bin(int count)
	// {
	// 	std::ifstream ifs(filename, std:: ios_base::in |  std:: ios_base::binary);//定义一个文件流对象
    //     char *s = new char[count+1];
	// 	ifs.read((char*)&s, sizeof(s));
    //     return (s);
	// }



	std::string * read_text(int count)
	{		
        char s[count+1];
        for (int i= 0 ; i< count && !ifs->eof(); i+=1){
		    ifs->get(s[i]) ;
        }
		
        return new std::string(s);
	}

    std::string * read_to_character( const char character   )
    {
		const int buff_size = 100;const int max_len = 200;
		bool init_flag =1;
        char  buff [buff_size+1];
	    for (int i= 0 ; i<= buff_size ; i+=1) buff [i] = '\0';
		std:: string * s = new std::string();
		char ch;
		ifs->get(ch) ;
		// while (init_flag && (ch == character || ch =='\n'))
		// {
		// 	ifs->get(ch) ;
		// }
		
		while(s->length()<max_len){
	        for (int i= 0 ; i< buff_size ; i+=1){ 
				if(ch == character || ch =='\n' || ifs->eof()) {
					s->append(std::string(buff));
					return s;}
				buff[i] = ch;
			    ifs->get(ch) ;
	        }
			s->append(std::string(buff));
		}	
		//delete s;
		//return nullptr;
		return s;
    }       





	std::string * read_line(){
		return read_to_character('\n');
	
	}
    std::string * read_all()
    {
		const int chunk_size = 20;
		std::string* s;
		std::string* res= new std::string();
		do{	
			s = read_text(chunk_size);
			res ->append(*s);
		}while(s->length() == chunk_size);
		return res;
    }       
    

    void read_all_to_cout()
    {
        std::cout<<*read_all()<<std::endl;
    }

};

class ToursiteProxy: public IFile{
public:
	ToursiteProxy(const char* fn ): IFile(fn){}

	std:: string * read_colomn (std:: string * &s){
		s = read_to_character(',');	
		return (s);
	}	
	int read_colomn (int &num){
		std:: string * s = read_to_character(',');
		std::istringstream ss(*s);
		ss >> num ;
		return num ;
	}	





};

# endif