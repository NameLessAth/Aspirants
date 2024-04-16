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

class FullStorage : public Exception {
	public:
		const char * what () const throw(){
			return "Penyimpanan sudah penuh.";
		}
};

class InsufficientMoney : public Exception {
	public:
		const char * what () const throw(){
			return "Uang tidak cukup.";
		}
};

class InsufficientItems : public Exception {
	public:
		const char * what () const throw(){
			return "Barang tidak cukup.";
		}
};

class NameNotUnique : public Exception {
	public:
		const char * what () const throw(){
			return "Nama tidak unik.";
		}
};

#endif