#pragma once

#include "Network.h"

class BackPropagation : public Network
{
public:
    BackPropagation(unsigned int num_input_layer_neurons, unsigned int num_hidden_layers, unsigned int num_hidden_layer_neurons, unsigned int num_output_layer_neurons);
    virtual ~BackPropagation();

    std::vector<std::string> start_learning(unsigned int num_cycles, float learning_rate, const std::vector<std::vector<float>> &inputs) override;
    std::vector<std::string> train(float learning_rate, const std::vector<std::vector<float>> &inputs) override;

protected:
    float calculate_error(float result, float desired) override;
    bool check_error_accum(float error);
    std::vector<std::string> generate_output(const std::vector<float> &expected, const std::vector<float> &results, const std::vector<float> &errors, const std::vector<float> &sums);

private:
    LayerPtr input_layer;
	std::vector<LayerPtr> hidden_layers;
    LayerPtr output_layer;
};
typedef std::shared_ptr<BackPropagation> BackPropagationPtr;
