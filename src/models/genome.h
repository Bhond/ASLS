#pragma once

#include <iostream>
#include <vector>
#include <random>

class Genome
{
public:
	enum NodeTypes{ Input, Hidden, Output};
	enum SquashTypes{ Identity, Inverse, Sinusoide, Tanh, Logistic };

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

	private:
		std::default_random_engine* generator{ nullptr };

	public:
		Node(const std::string& n, NodeTypes t, SquashTypes s)
			: name(n), type(t), squash(s)
		{
			generator = new std::default_random_engine();
			std::normal_distribution<double> d0(0.0, 1.0);
			bias = d0(*generator);
			squash = static_cast<SquashTypes>(std::rand() % SquashTypes::Logistic + 1);
		}

		Node(const Node& other) = default;

		~Node()
		{
			// Next is handled by genome -> bad?
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

private:
	std::default_random_engine* generator{ nullptr };
	int size{ 0 };

public:
	Genome();
	Genome(const Genome& other);
	~Genome();
	
public:
	void update();
	void addNode(const std::string& name, NodeTypes type, SquashTypes squash);

private:
	void activate();
	void squash(Node* n);

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