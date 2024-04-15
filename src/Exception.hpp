#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__


#include <iostream>

class Exception : public std::exception{
	public:
		virtual const char * what () const throw() = 0;
};

class IndexPenyimpananOutOfBounds : public Exception {
    public:
		const char * what () const throw() {
			return "Index Penyimpanan diluar batas!";
		}
};

class FileNotFound : public Exception {
	public:
		const char * what () const throw(){
			return "Lokasi berkas tidak valid.";
		}
};


class InvalidInput : public Exception {
	public:
		const char * what () const throw(){
			return "Input pengguna tidak valid.";
		}
};

#endif