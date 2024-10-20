#pragma once
#ifndef BASE_H
#define BASE_H
#include <string>

class Base
{
public:
	virtual ~Base() = default;

	/**
	 * @brief 获取类名
	 * @return std::string 类名，包含命名空间
	 */
	std::string getClassName() const;
};

#endif // BASE_H
