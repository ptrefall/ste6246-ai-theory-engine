#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class Perceptron
{
public:
    class Data
    {
    public:
        std::vector<unsigned int> line;
        unsigned int threshold;
        unsigned int desired;
        void print() const 
        { 
            std::cout << "\t"; 
            std::for_each(begin(line), end(line), [](unsigned int value) { std::cout << value << " "; }); 
            std::cout << std::endl; 
        }
    };

    Perceptron(float threshold = 1.0);
    ~Perceptron();

    void rand_weights(unsigned int num_weights);
    void train(const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate = 1.0f);
    void train_N_TO_N(const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate = 1.0f);

    void print(unsigned int test_index);

private:
    float compute(unsigned int test_index, const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate);
    void compute_N_TO_N(unsigned int test_index, unsigned int sub_index, const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float &result, float &desired_result);
    std::vector<float> weights;
    float threshold;
    float total;
    std::vector<float> results;
};
typedef std::shared_ptr<Perceptron> PerceptronPtr;
