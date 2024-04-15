#include <iostream>

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
			return "Lokasi berkas tidak valid.";
		}
};

class InvalidInput : public Exception {
	public:
		char * what (){
			return "Input pengguna tidak valid.";
		}
};