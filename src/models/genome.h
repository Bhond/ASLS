#pragma once

#include <iostream>
#include <vector>

class Genome
{
public:
	enum NodeTypes{ Input, Hidden, Output};
	enum SquashTypes{ Identity, Inverse, Sinusoide, Tanh, Logistic };

	struct Node;
	struct Connection
	{
	public:
		Node* from{ nullptr };
		Node* to{ nullptr };
		Node* gater{ nullptr };
		double weight{ 0.0 };

	public:
		Connection(Node* f, Node* t)
			: from(f), to(t)
		{

		}
	};

	struct Node
	{
	public:
		int idx { 0 }; // For graphics
		std::string name{ "" };
		Node* next{ nullptr };
		NodeTypes type{ NodeTypes::Input };
		SquashTypes squash{ SquashTypes::Logistic };
		double bias{ 0.0 };
		double state{ 0.0 };
		double activation{ 0.0 };
		std::vector<Connection*> incomingConnections;
		Connection* selfConnection{ nullptr };

	public:
		Node(const std::string& n, NodeTypes t, SquashTypes s)
			: name(n), type(t), squash(s)
		{}

		Node(const Node& other) = default;

		~Node()
		{
			// Next is handled by genome -> bad?
			next = nullptr;
			delete selfConnection;
		}
	};
	

public:
	Node* root{ nullptr };

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
	void addInputNode(Node* toInsert);
	void addHiddenNode(Node* toInsert);
	void addOutputNode(Node* toInsert);
	void insertNode(Node* toInsert, Node* after);
	void addConnection(Node* from, Node* to);
	void removeNode(Node* n);
	void removeConnection(Node* from, Node* to);

};