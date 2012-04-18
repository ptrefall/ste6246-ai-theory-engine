#include "Loader.h"
#include "StringHelper.h"

#include <fstream>
#include <iostream>

LoaderPtr Loader::singleton;

LoaderPtr Loader::getSingleton()
{
	if(Loader::singleton == nullptr)
		Loader::singleton = std::make_shared<Loader>();
	return Loader::singleton;
}

Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::init(const std::string &path)
{
    this->path = path;
}

void Loader::load(const std::string &filename, std::vector<Perceptron::Data> &input, std::vector<Perceptron::Data> &desired)
{
    std::vector<std::string> lines;
    std::ifstream file(path+"\\"+filename);
	if(file.is_open())
	{
        while(file.good())
        {
	        std::string line;
	        std::getline(file, line);
	        if(line.empty()) // Seperation line
		        continue;
	        if(line[0] == '/' && line[1] == '/') //Comment
		        continue;
	        lines.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "ERROR: FAILED TO LOAD FILE " << filename << "!" << std::endl;
        return;
    }

    //Loop over the rest of the lines and parse the text
	unsigned int parse_index = 0;
	while(parse_index < lines.size())
	{
		//INPUT
		if(StringHelper::toUpper(lines[parse_index], lines[parse_index].size()).find("INPUT") != std::string::npos)
		{
			parse_index++;
			parseInput(lines, parse_index, input);
		}

        //DESIRED
		if(StringHelper::toUpper(lines[parse_index], lines[parse_index].size()).find("DESIRED") != std::string::npos)
		{
			parse_index++;
			parseInput(lines, parse_index, desired);
		}

		//KEEP LOOP ALIVE
		else
		{
			parse_index++;
		}
	}

    return;
}

///////////////////////////////////
// INPUT PARSING
///////////////////////////////////
void Loader::parseInput(const std::vector<std::string> &lines, unsigned int &index, std::vector<Perceptron::Data> &input_vector)
{
	while(index < lines.size())
	{
		//Ignore start bracket
		if(lines[index].find("{") != std::string::npos)
		{
			index++;
			continue;
		}

		//Finish parsing at end bracket
		if(lines[index].find("}") != std::string::npos)
		{
			index++;
			return;
		}

		//Otherwise, we parse the line as a setting
		const std::string &input_line = lines[index++];
        Perceptron::Data data;
        for(unsigned int i = 0; i < input_line.size(); i++)
        {
            char input_char = input_line[i];
            if(input_char == '\t' || input_char == '\n')
                continue;
            unsigned int input = atoi(&input_char);
            if(input != 0 && input != 1)
                std::cout << "ERROR: AN INPUT VALUE IS OUT OF BOUNDS!" << std::endl;
            else
                data.line.push_back(input);
        }
        input_vector.push_back(std::move(data));
	}

	std::cout << "ERROR: OUT OF BOUNDS WHEN PARSING INPUT VECTOR FOR " << lines[0] << "!" << std::endl;
}
