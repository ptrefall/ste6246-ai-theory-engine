#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Random.h"

class Neuron;
typedef std::shared_ptr<Neuron> NeuronPtr;

class Edge
{
public:
    Edge(const NeuronPtr &from, const NeuronPtr &to) : from(from), to(to) { Random::getSingleton()->randomize(); weight = Random::getSingleton()->rand(); }
    Edge(const NeuronPtr &from, const NeuronPtr &to, float weight) : from(from), to(to), weight(weight) {}

    void setWeight(float weight) { this->weight = weight; }
    float getWeight() const { return weight; }

    const NeuronPtr &getFrom() const { return from; }
    const NeuronPtr &getTo() const { return to; }

private:
    NeuronPtr from;
    NeuronPtr to;
    float weight;
};
typedef std::shared_ptr<Edge> EdgePtr;

class Neuron : public std::enable_shared_from_this<Neuron>
{
public:
    Neuron(float value) : value(value) {}

    void set(float value) { this->value = value; }
    float get() const { return value; }
    void add(const NeuronPtr &to) { auto edge = std::make_shared<Edge>(shared_from_this(), to); edges.push_back(edge); }
    const std::vector<EdgePtr> &getEdges() const { return edges; }

    float sumEdges();

    void setCellFunc(std::function<float(float)> &&cell_func)  { this->cell_func = cell_func; }
	void setCellFunc(const std::function<float(float)> &cell_func)  { this->cell_func = cell_func; }
    float cell_function(float result) { return cell_func(result); }

    void setErrorFunc(std::function<void(float, const std::vector<EdgePtr> &)> &&error_func)  { this->error_func = error_func; }
	void setErrorFunc(const std::function<void(float, const std::vector<EdgePtr> &)> &error_func)  { this->error_func = error_func; }
    void propagate_error(float error);

private:
    float value;
    std::vector<EdgePtr> edges;
    std::function<float(float)> cell_func;
    std::function<void(float, const std::vector<EdgePtr> &)> error_func;
};

class Layer;
typedef std::shared_ptr<Layer> LayerPtr;

class Layer
{
public:
    Layer(unsigned int num_neurons)
    {
        for(unsigned int i = 0; i < num_neurons; i++)
            neurons.push_back(std::make_shared<Neuron>(0.0f));
    }
    virtual ~Layer() {}

    void connect_from(const LayerPtr &layer);
    const LayerPtr &getConnectedFromLayer() const { return connected_from; }

    const std::vector<NeuronPtr> &getNeurons() const { return neurons; }

    float sumEdges();

    void setCellFunc(std::function<float(float)> &&cell_func);
	void setCellFunc(const std::function<float(float)> &cell_func);
    float cell_function(float result);

    void setErrorFunc(std::function<void(float, const std::vector<EdgePtr> &)> &&error_func);
	void setErrorFunc(const std::function<void(float, const std::vector<EdgePtr> &)> &error_func);
    void propagate_error(float error);

private:
    std::vector<NeuronPtr> neurons;
    LayerPtr connected_from;
};

class Network
{
public:
    Network() {}
    virtual ~Network() {}

    virtual std::vector<std::string> start_learning(unsigned int num_cycles, float learning_rate, const std::vector<std::vector<float>> &inputs) = 0;
    virtual std::vector<std::string> train(float learning_rate, const std::vector<std::vector<float>> &inputs) = 0;

protected:
    virtual float calculate_error(float result, float desired) = 0;
};