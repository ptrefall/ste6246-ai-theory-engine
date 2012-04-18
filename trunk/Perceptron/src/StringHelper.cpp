#include "StringHelper.h"

#include <algorithm>

std::string StringHelper::toUpper(const std::string &input, unsigned int num_chars)
{
	std::string output;
	std::transform( input.begin(), input.begin()+num_chars, std::back_inserter(output), up_char );
	output += input.substr(num_chars, input.size() - num_chars);
	return output;
}

std::string::value_type StringHelper::up_char( std::string::value_type input )
{
	return std::use_facet< std::ctype<std::string::value_type> >( std::locale() ).toupper( input );
}

