#pragma once

#include "Perceptron.h"

#include <string>
#include <vector>
#include <memory>

class Loader;
typedef std::shared_ptr<Loader> LoaderPtr;

class Loader
{
public:
	static LoaderPtr getSingleton();
	Loader();
	~Loader();

	void init(const std::string &path);
    void load(const std::string &filename, std::vector<Perceptron::Data> &input, std::vector<Perceptron::Data> &desired);

protected:
    void parseInput(const std::vector<std::string> &lines, unsigned int &index, std::vector<Perceptron::Data> &input_vector);

    static LoaderPtr singleton;
	std::string path;
};
