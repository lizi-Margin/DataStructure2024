# ifndef _FILE_H_
# define _FILE_H_
# include<fstream>
# include<sstream>
# include<string>
# include<iostream>

/*
	File IO 
	shc 2024
*/

class File
{
protected:
	std::string filename; // 配置文件
public:
	File(const char* fn ){	
		filename = std::string(fn);	
	}
	~File(){}
	
	std::string get_filename(){
		return filename;
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
	~OFile(){
		close();
		delete ofs;
	}

	bool is_open(){return ofs->is_open();}
	void close(){
		ofs->close();
	}
    //文本读写
	void write_text( std:: string* content)
	{
		*ofs << *content;
	}
	void write_text( std:: string content)
	{
		*ofs << content;
	}
	void write_line(std:: string * content){
		*ofs << *content<<"\n";
	}
	void write_line(std:: string  content){
		*ofs << content<<"\n";
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
		delete ifs;
		}

	bool is_open(){
		return ifs->is_open();}

	void close(){
		ifs->close();
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

class CSVReader: public IFile{
public:
	CSVReader(const char* fn ): IFile(fn){
	}

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

	int read_row_num(){
		int row_num = 0;
		read_text(2);
		read_colomn(row_num);
		return row_num;
	}



};
class CSVWriter: public OFile{
public:
	CSVWriter(const char* fn ): OFile(fn){}

	void write_colomn (std:: string * s){
		write_text(s);
		write_text(",");
	}	
	void write_colomn (int num){
		write_text(std::to_string(num));
		write_text(",");
	}	
	void write_last_colomn (std:: string * s){
		write_line(s);
	}	
	void write_last_colomn (int num){
		write_line(std::to_string(num));
	}

	void write_row_num(int num){
		write_text("# ");
		write_line(std::to_string(num));
	}
};


# endif