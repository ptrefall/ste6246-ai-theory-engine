#include "Network.h"
#include <algorithm>
void Layer::connect_from(const LayerPtr &layer)
{ 
    connected_from = layer; 
    auto &from_layer_neurons = connected_from->getNeurons();

    for(unsigned int local = 0; local < neurons.size(); local++)
    {
        for(unsigned int external = 0; external < from_layer_neurons.size(); external++)
        {
            from_layer_neurons[external]->add(neurons[local]);
        }
    }
}

float Layer::sumEdges()
{
    float SUM = 0.0f;
    std::for_each(begin(connected_from->getNeurons()), end(connected_from->getNeurons()), [&](const NeuronPtr &neuron)
    {
        SUM += neuron->sumEdges();
    });
    return SUM;
}

void Layer::setCellFunc(std::function<float(float)> &&cell_func)
{
    std::for_each(begin(neurons), end(neurons), [&](const NeuronPtr &neuron)
    {
        neuron->setCellFunc(std::move(cell_func));
    });
}

float Layer::cell_function(float result)
{
    //You would probably only call this for convenience if you know this layer only has one neuron...
    float SUM = 0.0f;
    std::for_each(begin(neurons), end(neurons), [&](const NeuronPtr &neuron)
    {
        SUM += neuron->cell_function(result);
    });
    return SUM;
}

void Layer::setErrorFunc(std::function<void(float, const std::vector<EdgePtr> &)> &&error_func)
{
    std::for_each(begin(neurons), end(neurons), [&](const NeuronPtr &neuron)
    {
        neuron->setErrorFunc(std::move(error_func));
    });
}
void Layer::propagate_error(float error)
{
    std::for_each(begin(neurons), end(neurons), [&](const NeuronPtr &neuron)
    {
        neuron->propagate_error(error);
    });
}

float Neuron::sumEdges()
{
    float SUM = 0.0f;
    std::for_each(begin(edges), end(edges), [&](const EdgePtr &edge)
    {
        SUM += value * edge->getWeight();
    });
    return SUM;
}

void Neuron::propagate_error(float error)
{
    error_func(error, edges);
}
