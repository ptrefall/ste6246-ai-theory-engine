#include "Perceptron.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

Perceptron::Perceptron(unsigned int num_input_layer_neurons)
{
    input_layer = std::make_shared<Layer>(num_input_layer_neurons);

    output_layer = std::make_shared<Layer>(1);
    output_layer->connect_from(input_layer);    //Connect the neurons of input_layer with the output_layer neuron
    output_layer->setCellFunc([](float result)          //Define the cell function of the output_layer neuron
    {
        return (result >= 1.0f) ? 1.0f : 0.0f;
    });
    input_layer->setErrorFunc([](float error, const std::vector<EdgePtr> &edges)          //Define the error function of the output_layer neuron
    {
        std::for_each(begin(edges), end(edges), [&](const EdgePtr &edge)
        {
            edge->setWeight(edge->getWeight() + (error * edge->getFrom()->get()));
        });
    });
}

Perceptron::~Perceptron()
{
}

std::vector<std::string> Perceptron::start_learning(unsigned int num_cycles, float learning_rate, const std::vector<std::vector<float>> &inputs)
{
    std::vector<std::string> results;
    for(unsigned int i = 0; i < num_cycles; i++)
    {
        std::vector<std::string> r = train(learning_rate, inputs);
        results.insert(end(results), begin(r), end(r));
    }
    
    return results;
}

std::vector<std::string> Perceptron::train(float learning_rate, const std::vector<std::vector<float>> &inputs) 
{
    std::vector<float> expected;
    std::vector<float> results;
    std::vector<float> errors;
    std::vector<float> sums;

    //Iterate num cycles through the net and improve our understanding of the input data
    std::for_each(begin(inputs), end(inputs), [&](const std::vector<float> &input)
    {
        for(unsigned int i = 0; i < input_layer->getNeurons().size(); i++)
            input_layer->getNeurons()[i]->set(input[i]);
        
        float desired = input[input.size()-1];
        float SUM = output_layer->sumEdges();               //Only one neuron who's edges are connected from all the input_layer's neurons
        float result = output_layer->cell_function(SUM);          //We can call the cell_function directly on the output layer, since we know it only has a single neuron
        float error = calculate_error(result, desired); //The last index of input vector is expected to be the desired result value
        float correction = error * learning_rate;
        input_layer->propagate_error(correction);               //Propagate errors into the edges between the layers

        expected.push_back(desired);
        results.push_back(result);
        errors.push_back(error);
        sums.push_back(SUM);

        if(check_error_accum(error) == false)
            return;
    });

    return generate_output(expected, results, errors, sums);
}

float Perceptron::calculate_error(float result, float desired)
{
    return desired - result;
    /*if(result == desired)
        return 0.0f;

    if(result < 1.0f)
        return 1.0f - result;
    else if(result > 1.0f)
        return result - 1.0f;
    else
        return 0.0f;*/
}

bool Perceptron::check_error_accum(float error)
{
    static float last_error = 0.0f;
    static float error_accum = 0.0f;
    static unsigned int num_error_accum = 0;

    float delta_error = error - last_error;             //If our delta is negative, then our error is getting smaller, which is good!
    last_error = error;

    error_accum += delta_error;
    if((int)(error_accum*1000000.0f) == 0)
        num_error_accum++;
    else
        error_accum = 0.0f;

    //If we have gone 4 iterations,
    //but none were changing the error delta
    //then we're not making progress on this
    //input data.
    if(num_error_accum > 4)
        return false;

    return true;
}

std::vector<std::string> Perceptron::generate_output(const std::vector<float> &expected, const std::vector<float> &results, const std::vector<float> &errors, const std::vector<float> &sums)
{
    std::vector<std::string> results_string;
    for(unsigned int i = 0; i < results.size(); i++)
    {
        std::stringstream ss;
        std::cout.unsetf(std::ios::floatfield);            // floatfield not set
        std::cout.precision(10);
        ss << "Expected: " << std::setprecision(5) << expected[i] << "\t\tResult: " << results[i] << "\t\tError: " << errors[i] << "\t\tSums: " << sums[i] << std::fixed;
        results_string.push_back(ss.str());
        std::cout.setf(std::ios::fixed,std::ios::floatfield);
    }
    return results_string;
}






























/*#include "Random.h"

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
*/