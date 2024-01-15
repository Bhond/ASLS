#pragma once

#include <iostream>
#include <vector>

class Genome
{
public:
	enum NodeTypes{ Input, Hidden, Output};
	enum SquashTypes{ Identity, Inverse, Sinusoide, Logistic };

private:
	struct Connection
	{
	public:
		int from{ -1 };
		int to{ -1 };
		int gater{ -1 };
		double weight{ 0.0 };
	};

	struct Node
	{
	public:
		std::string name{ "" };
		Node* next{ nullptr };
		NodeTypes type{ NodeTypes::Input };
		SquashTypes squash{ SquashTypes::Logistic };
		int idx{ 0 };
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
	

private:
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
	Node* getNodeAt(const int& idx);

	void addNode(Node* n);
	void addInputNode(Node* toInsert);
	void addHiddenNode(Node* toInsert);
	void addOutputNode(Node* toInsert);
	void insertNode(Node* toInsert, Node* after);
	void addConnection();
	void removeNode();
	void removeConnection();

};