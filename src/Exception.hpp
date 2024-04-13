#include <iostream>
using namespace std;

class Exception : public std::exception{
	public:
		virtual char * what () = 0;
};

class IndexPenyimpananOutOfBounds : public Exception {
    public:
		char * what () {
			return "Index Penyimpanan diluar batas!";
		}
};

class FileNotFound : public Exception {
	public:
		char * what (){
			return "File tidak ditemukan.";
		}
};