#include "Perceptron.h"
#include "Random.h"

#include <iostream>

Perceptron::Perceptron(float threshold)
    : threshold(threshold), total(0.0f)
{
}

Perceptron::~Perceptron()
{
}

void Perceptron::rand_weights(unsigned int num_weights)
{
    weights.clear();
    Random::getSingleton()->randomize();
    for(unsigned int i = 0; i < num_weights; i++)
        weights.push_back(Random::getSingleton()->rand());
}

void Perceptron::train(const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate)
{
    std::cout << "Starting training!" << std::endl;

    if(weights.empty())
    {
        rand_weights(input.size()*input[0].line.size());
        results.resize(input.size());
    }

    bool continue_training = true;
    while(continue_training)
    {
        continue_training = false;

        for(unsigned int i = 0; i < input.size(); i++)
        {
            float result = compute(i, input, desired, learning_rate);

            if( (int)desired[i].line[0] != (int)result )
            {
                continue_training = true;
                for(unsigned int j = 0; j < input[i].line.size(); j++)
                {
                    weights[i] += learning_rate * (desired[i].line[0] - result) * input[i].line[j];
                }
            }
            else
            {
                results[i] = result;
            }
        }
    }
}

void Perceptron::train_N_TO_N(const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate)
{
    std::cout << "Starting training!" << std::endl;

    if(weights.empty())
    {
        rand_weights(input.size()*input[0].line.size());
        results.resize(input.size()*input[0].line.size());
    }

    unsigned int iter = 0;
    bool continue_training = true;
    while(continue_training)
    {
        continue_training = false;

        float result = 0.0f;
        float desired_result = 0.0f;

        for(unsigned int i = 0; i < input.size(); i++)
        {
            for(unsigned int j = 0; j < input[i].line.size(); j++)
            {
                compute_N_TO_N(i, j, input, desired, result, desired_result);
            }
        }
        result /= (input.size()*input[0].line.size());
        desired_result /= (input.size()*input[0].line.size());

        if( (int)desired_result != (int)result )
        {
            continue_training = true;

            if(result < desired_result)
            {
                //weights[i] += learning_rate * (desired_result - result) * input[i].line[j];
                weights[iter] = desired_result - result;
            }
            else
            {
                //weights[i] += learning_rate * (desired_result - result) * input[i].line[j];
                weights[iter] = -result;
            }
        }
        else
        {
            if(result >= 1.0f) result = 1.0f;
            else if(result > 0.0f) result = 0.0f;

            results[iter] = result;
        }
        iter++;
        if(iter >= (input.size()*input[0].line.size()))
            iter = 0;
    }
}

float Perceptron::compute(unsigned int test_index, const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float learning_rate)
{
    float result = 0.0f;
    for(unsigned int i = 0; i < input[test_index].line.size(); i++)
        result += input[test_index].line[i] * weights[i + test_index*input[test_index].line.size()];
    for(unsigned int i = 0; i < desired[test_index].line.size(); i++)
        result += desired[test_index].line[i] * weights[i + test_index*desired[test_index].line.size()];

    if(result >= 1.0f) result = 1.0f;
    else if(result > 0.0f) result = 0.0f;
    return result;
}

void Perceptron::compute_N_TO_N(unsigned int test_index, unsigned int sub_index, const std::vector<Perceptron::Data> &input, const std::vector<Perceptron::Data> &desired, float &result, float &desired_result)
{
    result += input[test_index].line[sub_index] * weights[sub_index + test_index*input[test_index].line.size()];
    desired_result += desired[test_index].line[sub_index];
}

void Perceptron::print(unsigned int test_index)
{
    if(test_index < results.size())
    {
        std::cout << results[test_index];
    }
}
