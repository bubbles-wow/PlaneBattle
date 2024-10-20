#include <typeinfo>

#include <util/Base.h>

std::string Base::getClassName() const
{
	std::string origin = typeid(*this).name();
	size_t start = origin.find_first_of(' ') + 1;
	return origin.substr(start);
}