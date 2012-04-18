#pragma once

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
    bool load(const std::string &filename, std::vector<std::vector<float>> &inputs);

protected:
    void parseInputs(const std::vector<std::string> &lines, unsigned int &index, std::vector<std::vector<float>> &inputs);
    void parseInput(const std::vector<std::string> &lines, unsigned int &index, std::vector<float> &input);

    static LoaderPtr singleton;
	std::string path;
};
