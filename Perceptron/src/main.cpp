
#include "Loader.h"
#include "Perceptron.h"

#include <iostream>

#include <iostream>
#include <filesystem>

int main(int /*argc*/, char** argv)
{
	//Convert to string, then trim away the executable filename and the build type directory (Debug/MinSizeRel/Release/etc)
	std::string argv_dir(argv[0]);
	argv_dir = argv_dir.substr(0, argv_dir.find_last_of("\\"));
	argv_dir = argv_dir.substr(0, argv_dir.find_last_of("\\"));
    Loader::getSingleton()->init(argv_dir);

    std::cout << "Welcome to the perceptron pattern recognition genious application!" << std::endl;
    bool running = true;
    while(running)
    {
        std::cout << "------------------------------------------------------------------" << std::endl;
        std::cout << "Do you want to 1) learn the AND operator, 2) learn the OR operator, 3) recognize the T character, or else specify a file to load." << std::endl;
        std::string choice;
        std::getline(std::cin, choice);

        std::vector<float> input;
        std::vector<float> desired;
        if(choice == "1")
            Loader::getSingleton()->load("AND.dat", input, desired);
        else if(choice == "2")
            Loader::getSingleton()->load("OR.dat", input, desired);
        else if(choice == "3")
            Loader::getSingleton()->load("T.dat", input, desired);
        else
            Loader::getSingleton()->load(choice, input, desired);

        std::cout << "Which learning rate do you want?" << std::endl;
        std::string learning_rate_string;
        std::getline(std::cin, learning_rate_string);
        float learning_rate = ::atof(learning_rate_string.c_str());

        std::cout << "How many iterations do you want? [1 -> N>." << std::endl;
        std::string iter_str;
        std::getline(std::cin, iter_str);
        unsigned int iter = ::atoi(iter_str.c_str());

        if(input.empty())
        {
            std::cout << "INPUT VECTOR IS EMPTY!" << std::endl;
            return -1;
        }
        else if(desired.empty())
        {
            std::cout << "DESIRED VECTOR IS EMPTY!" << std::endl;
            return -1;
        }
        else
        {
            std::cout << "Loaded following input vector:" << std::endl;
            std::cout << "{" << std::endl;
            for(unsigned int i = 0; i < input.size(); i++)
                std::cout << input[i] << " ";
            std::cout << std::endl << "}" << std::endl << std::endl;
            std::cout << "Loaded following desired vector:" << std::endl;
            std::cout << "{" << std::endl;
            for(unsigned int i = 0; i < desired.size(); i++)
                std::cout << desired[i] << " ";
            std::cout << std::endl << "}" << std::endl << std::endl;
        }

        auto perceptron = std::make_shared<Perceptron>(input);
        perceptron->start_learning(iter);


         /*   if(N_TO_N)
                perceptron->train(input, desired, learning_rate);
            else
                perceptron->train(input, desired, learning_rate);

            unsigned int size = input.size();
            if(N_TO_N)
                size *= input[0].line.size();

            for(unsigned int i = 0; i < size; i++)
            {
                if(choice == "1")
                {
                    for(unsigned int j = 0; j < input[i].line.size(); j++)
                    {
                        if(j != input[i].line.size()-1)
                            std::cout << input[i].line[j] << " AND ";
                        else
                            std::cout << input[i].line[j];
                    }
                    std::cout << " = ";
                }
                if(choice == "2")
                {
                    for(unsigned int j = 0; j < input[i].line.size(); j++)
                    {
                        if(j != input[i].line.size()-1)
                            std::cout << input[i].line[j] << " OR ";
                        else
                            std::cout << input[i].line[j];
                    }
                    std::cout << " = ";
                }
                perceptron->print(i);
                std::cout << std::endl;
            }
        }*/

        std::cout << std::endl << "Run again? 1) yes or 2) no." << std::endl;
        std::string again;
        std::getline(std::cin, again);
        if(again != "1")
            running = false;
    }
}
