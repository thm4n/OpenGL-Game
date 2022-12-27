#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "../main.h"

class Exception : public std::exception {
public:
	enum maj_t {
		undefined = 0,
		graphics_error = 1,
		texture_load_error,
		file_dir_open_error,
	};

	Exception(maj_t maj = Exception::undefined, const char* description = "");
	Exception(maj_t maj = Exception::undefined, const std::string description = "");

	const char* maj_tToString() const;

	virtual const char* what() const throw();

private:
	maj_t _maj;
	std::string _description;
};

#endif