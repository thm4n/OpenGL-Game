#include "Exception.h"

Exception::Exception(maj_t maj, const char* description) {
	this->_maj = maj;
	this->_description = description;
}

Exception::Exception(maj_t maj, const std::string description) {
	this->_maj = maj;
	this->_description = description;
}

const char* Exception::maj_tToString() const {
	switch((int)(this->_maj)) {
	case maj_t::graphics_error:
		return "Graphics Error";
	case maj_t::texture_load_error:
		return "texture load error";
	case maj_t::file_dir_open_error:
		return "file or directory open error";
	}
	return "Undefined Error";
}

const char* Exception::what() const throw() {
	std::cout << maj_tToString() << ": " << this->_description;
	return "";
}
