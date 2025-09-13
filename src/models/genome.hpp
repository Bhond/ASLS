#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <map>

#include "../main/configreader.hpp"

class Genome
{
public:
	enum NodeTypes{ Input, Hidden, Output};
	enum SquashTypes{ Identity, Inverse, Sinusoide, Tanh, Sigmoid, Logistic};
	std::map<std::string, SquashTypes> SquashTypesFromString{
		{ "Identity", SquashTypes::Identity },
		{ "Inverse", SquashTypes::Inverse },
		{ "Sinusoide", SquashTypes::Sinusoide},
		{ "Tanh", SquashTypes::Tanh }, 
		{ "Sigmoid", SquashTypes::Sigmoid },
		{ "Logistic", SquashTypes::Logistic }
	};


	struct Config
	{
	public:
		const int dropout{ 100 };
		const double initMean{ 0.0 };
		const double initStDev{ 1.0 };
		const double Min{ 0.0 };
		const double Max{ 0.0 };
		const double MutationRate{ 0.2 };
	};

	struct Node;
	struct Connection
	{
	public:
		Node* from{ nullptr };
		Node* to{ nullptr };
		Node* gater{ nullptr };
		double weight{ 0.0 };

	private:
		std::default_random_engine* generator{ nullptr };

	public:
		Connection(Node* f, Node* t)
			: from(f), to(t)
		{
			generator = new std::default_random_engine();
			std::normal_distribution<double> d(0.0, 1.0);
			weight = d(*generator);
		}
		
		~Connection()
		{
			delete generator;
		}
	};

	struct Node
	{
	public:
		int pos2DX { 0 };
		int pos2DY { 0 };
		int idx { 0 };
		std::string name{ "" };
		Node* next{ nullptr };
		NodeTypes type{ NodeTypes::Input };
		SquashTypes squash{ SquashTypes::Logistic };
		double bias{ 0.0 };
		double state{ 0.0 };
		double activation{ 0.0 };
		std::vector<Connection*> incomingConnections;
		Connection* selfConnection{ nullptr };
		int depth{0};

	private:
		std::default_random_engine* generator{ nullptr };

	public:
		Node(const std::string& n, NodeTypes t)
			: name(n), type(t)
		{
			squash = static_cast<SquashTypes>(std::rand() % SquashTypes::Logistic + 1);
		}

		Node(const std::string& n, NodeTypes t, const double& mean, const double& standardDeviation)
			: name(n), type(t)
		{
			generator = new std::default_random_engine();
			std::normal_distribution<double> d0(mean, standardDeviation);
			bias = d0(*generator);
			squash = static_cast<SquashTypes>(std::rand() % SquashTypes::Logistic + 1);
		}

		Node(const std::string& n, NodeTypes t, SquashTypes s)
			: name(n), type(t), squash(s)
		{
		}

		Node(const Node& other) = default;

		~Node()
		{
			next = nullptr;
			delete selfConnection;
			delete generator;
		}
	};
	

public:
	Config config{};
	Node* root{ nullptr };
	std::vector<Connection*> connections;
	int inputSize{ 0 };
	int outputSize{ 0 };
	int outputLayerDepth {1};
	
private:
	bool shapeChanged { false };
	std::default_random_engine* generator{ nullptr };
	int size{ 0 };

public:
	Genome();
	Genome(const Genome& other);
	~Genome();
	
public:
	void update();
	void addNode(const std::string& name, NodeTypes type, SquashTypes squash);
	void addNode(const std::string& name, NodeTypes type, const double& mean, const double& standardDeviation);
	void addNode(const std::string& name, NodeTypes type);

private:
	void activate();
	void squash(Node* n);
	void onShapeChanged();
	void computeNodesDepth();

	void addNode(Node* n);
	void addNodeMutation();
	void removeNodeMutation();
	void addInputNode(Node* toInsert);
	void addHiddenNode(Node* toInsert);
	void addOutputNode(Node* toInsert);
	void insertNode(Node* toInsert, Node* after);
	Connection* addConnection(Node* from, Node* to);
	void addConnectionMutation();
	void connectionWeightMutation();
	void connectionGaterMutation();
	void nodeSquashMutation();
	bool areConnected(Node* n0, Node* n1);
	void removeNode(Node* n);
	void removeConnection(Connection* connection);
	void removeConnectionMutation();

};