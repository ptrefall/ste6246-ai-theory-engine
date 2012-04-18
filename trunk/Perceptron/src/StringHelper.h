#pragma once

#include <string>

class StringHelper
{
public:
	static std::string toUpper(const std::string &input, unsigned int num_chars = 1);

private:
	static std::string::value_type up_char( std::string::value_type input );
};
