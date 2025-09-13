#include "genome.hpp"

Genome::Genome()
{

	std::cout<<"init genome"<<std::endl;
	generator = new std::default_random_engine();

	// Create genome
	ConfigReader cr;
	cr.parseGenomeConfig();
	for (int i = 0; i < cr.inputs.size(); i++)
	{
		addNode(cr.inputs[i].name, NodeTypes::Input, cr.inputs[i].mean, cr.inputs[i].standardDeviation);
	}
	for (int i = 0; i < cr.outputs.size(); i++)
	{
		addNode(cr.outputs[i].name, NodeTypes::Output, SquashTypesFromString[cr.outputs[i].squash]);
	}
}

Genome::Genome(const Genome& other)
{
	// For siblings
	root = new Node(*other.root);

	Node* currentNew = root;
	// Copy values

	Node* currentOld = other.root;
	while (currentOld)
	{
		if (currentOld->next)
		{
			currentNew->next = new Node(*currentOld->next);
			// Copy values
		}
		currentNew = currentNew->next;
		currentOld = currentOld->next;
	}
}

Genome::~Genome()
{
	// Remove all connections
	for (Connection* c : connections)
	{
		c = nullptr;
		delete c;
	}
	connections.clear();

	// Destroy all nodes properly
	Node* current = root->next;
	Node* currentNext = current->next;
	while (current)
	{
		removeNode(current);
		current = currentNext;

		if (currentNext && currentNext->next)
			currentNext = currentNext->next;

		if (current == currentNext)
			currentNext = nullptr;
	}
	delete root;
	delete generator;
}

void Genome::update()
{
	// Generate mutations -> For now, add or remove node/connection, should be between generations
	std::uniform_int_distribution<int> d0(0, config.dropout);
	if ((true || d0(*generator) == 0))
	{
		addNodeMutation();
	}
	
	std::uniform_int_distribution<int> d1(0, config.dropout);
	if (d1(*generator) == 0 && size > inputSize + outputSize)
	{
		removeNodeMutation();
	}

	std::uniform_int_distribution<int> d2(0, config.dropout);
	if (true || d2(*generator) == 0)
	{
		addConnectionMutation();
	}

	std::uniform_int_distribution<int> d3(0, config.dropout);
	if (d3(*generator) == 0)
	{
		removeConnectionMutation();
	}
	
	std::uniform_int_distribution<int> d4(0, config.dropout);
	if (d4(*generator) == 0)
	{
		connectionWeightMutation();
	}

	std::uniform_int_distribution<int> d5(0, config.dropout);
	if (d5(*generator) == 0)
	{
		connectionGaterMutation();
	}

	std::uniform_int_distribution<int> d6(0, config.dropout);
	if (d6(*generator) == 0)
	{
		nodeSquashMutation();
	}


	// If shape changed perform some calculations
	if (shapeChanged)
	{
		onShapeChanged();

		// Reset for next step
		shapeChanged = false;
	}

	// Activate
	activate();
}

void Genome::activate()
{
	Node* current = root;
	while (current)
	{
		if (current->type == NodeTypes::Input)
		{
			current->activation = current->state; // Input
		}
		else
		{
			// Self
			if (current->selfConnection && current->selfConnection->gater)
			{
				current->state = current->selfConnection->weight * current->state * current->selfConnection->gater->activation;
			}

			// Incoming
			for (Connection* c : current->incomingConnections)
			{
				if (c->gater)
					current->state += c->weight * c->from->activation * c->gater->activation;
				else
					current->state += c->weight * c->from->activation;
			}

			current->state += current->bias;
			squash(current);
		}

		if (current->type == NodeTypes::Output)
		{
			// Store output
		}
		current = current->next;
	}
}

void Genome::onShapeChanged() 
{
	// Compute node depth for drawing
	computeNodesDepth();
}


void Genome::computeNodesDepth() 
{	
	// Rest output layer depth
	// By design, will be set before reaching output nodes
	outputLayerDepth = 1;
	// Init loop
	Node* current = root;
	// Loop over the nodes: input -> hidden -> output 
	while (current)
	{
		if (current->type == NodeTypes::Input)
		{
			current->depth = 0;
		}
		else if (current->type == NodeTypes::Output)
		{
			current->depth = outputLayerDepth;
		}
		else // Hidden
		{
			int depth{0};
			for (Connection* c : current->incomingConnections)
			{
				depth = std::max(depth, c->from->depth + 1);
			}
			current->depth = depth;
			// Compute outputLayerDepth
			outputLayerDepth = std::max(outputLayerDepth, depth + 1);
		}

		// Increment
		current = current->next;
	}
}

void Genome::squash(Node* n)
{
	switch (n->squash)
	{
	case Inverse:
		n->activation = - n->state;
		break;
	case Sinusoide:
		n->activation = std::sin(n->state);
		break;
	case Tanh:
		n->activation = std::tanh(n->state);
		break;
	case Logistic:
		n->activation = 1 / (1 + std::exp( - n->state)); // For now, sigmoid only...
		break;
	default: // Identity
		n->activation = n->state;
		break;
	}
}

void Genome::connectionWeightMutation()
{
	// Select random connection
	if (connections.size() > 0)
	{
		std::uniform_int_distribution<int> d0(0, connections.size() - 1);
		Connection* connection = connections[d0(*generator)];

		// Mutate: Develop on that, too easy for now...
		std::normal_distribution<double> d1(0.0, 1.0);
		connection->weight += d1(*generator);
	}
}

void Genome::connectionGaterMutation()
{
	// Select random connection if exists
	if (connections.size() > 0)
	{
		std::uniform_int_distribution<int> d0(0, connections.size() - 1);
		Connection* connection = connections[d0(*generator)];

		// Mutate: Develop on that, too easy for now...
		if (!connection->gater)
		{
			// Select random node
			std::uniform_int_distribution<int> d1(0, size - 1);
			int target = d1(*generator);
			Node* current = root;
			while (current && current->idx != target)
			{
				current = current->next;
			}
			if (current)
			{
				connection->gater = current;
			}
		}
	}
}

void Genome::nodeSquashMutation()
{
	// Select random node
	std::uniform_int_distribution<int> d1(0, size - 1);
	int target = d1(*generator);
	Node* current = root;
	while (current && current->idx != target)
	{
		current = current->next;
	}
	if (current)
	{
		current->squash = static_cast<SquashTypes>(rand() % SquashTypes::Logistic + 1);
	}
}

void Genome::addNode(const std::string& name, NodeTypes type, SquashTypes squash)
{
	Node* n = new Node(name, type, squash);
	addNode(n);
}

void Genome::addNode(const std::string& name, NodeTypes type, const double& mean, const double& standardDeviation)
{
	Node* n = new Node(name, type, mean, standardDeviation);
	addNode(n);
}

void Genome::addNode(const std::string& name, NodeTypes type)
{
	Node* n = new Node(name, type);
	addNode(n);
}

void Genome::addNode(Node* node)
{
	if (!root)
	{
		root = node;
		inputSize++;
		size++;
	}
	else
	{
		switch(node->type)
		{
		case NodeTypes::Input:
			addInputNode(node);
			node->depth = 0;
			break;
		case Hidden:
			addHiddenNode(node);
			break;
		case Output:
			addOutputNode(node);
			break;
		}
	}
	// Set shape changed
	shapeChanged = true;
}

void Genome::addNodeMutation()
{
	// Select a connection
	if (connections.size() > 0)
	{
		// Create node
		Node* node = new Node("", NodeTypes::Hidden, SquashTypes::Identity);
		addHiddenNode(node);

		std::uniform_int_distribution<int> d0(0, connections.size() - 1);
		Connection* connection = connections[d0(*generator)];
		// Get the gater
		Node* gater = connection->gater;

		// Select properly the index of the new node
		int idx = std::min(connection->to->idx, size - outputSize);

		// Create two new connexions
		Connection* c0 = addConnection(connection->from, node);
		c0->weight = 1.0;
		Connection* c1 = addConnection(node, connection->to);
		c1->weight = connection->weight;

		if (gater)
		{
			std::uniform_int_distribution<int> d1(0, 2);
			if (d1(*generator))
				c0->gater = gater;
			else
				c1->gater = gater;
		}
		removeConnection(connection);
	}

	// Set shape changed
	shapeChanged = true;
}

void Genome::removeNodeMutation()
{
	// Select node
	std::uniform_int_distribution<int> d(inputSize, size - outputSize - 1);
	int idx = d(*generator);
	Node* current = root;
	while (current && current->idx != idx)
	{
		current = current->next;
	}

	// Remove it 
	removeNode(current);

	// Set shape changed
	shapeChanged = true;
}

void Genome::addInputNode(Node* toInsert)
{
	Node* after = root;
	while (after->next && after->next->type == NodeTypes::Input)
	{
		after = after->next;
	}
	insertNode(toInsert, after);
	inputSize++;
}

void Genome::addHiddenNode(Node* toInsert)
{
	Node* after = root;
	while (after->next && after->next->type != NodeTypes::Output)
	{
		after = after->next;
	}
	insertNode(toInsert, after);
}

void Genome::addOutputNode(Node* toInsert)
{
	// Insert at the end
	Node* current = root;
	while (current->next)
	{
		current = current->next;
	}
	outputSize++;
	insertNode(toInsert, current);
}

void Genome::insertNode(Node* toInsert, Node* after)
{
	if (after->next)
	{
		toInsert->next = after->next;
		toInsert->idx = after->next->idx;
		after->next = toInsert;

		Node* current = toInsert;
		while (current->next)
		{
			current->next->idx = current->idx + 1;
			current = current->next;
		}
	}
	else
	{
		after->next = toInsert;
		toInsert->idx = after->idx + 1;
	}
	size++;
}

void Genome::addConnectionMutation()
{	
	if (root->next)
	{
		std::vector<std::pair<Node*, Node*>> pairs;
		Node* cursor0 = root;
		Node* cursor1 = root->next;

		while (cursor0)
		{
			while (cursor1)
			{
				if ((cursor0->type == NodeTypes::Input && cursor1->type != NodeTypes::Input)
					&& !areConnected(cursor0, cursor1))
				{
					pairs.push_back(std::pair<Node*, Node*>(cursor0, cursor1));
				}
				cursor1 = cursor1->next;
			}

			cursor0 = cursor0->next;
			if(cursor0)
				cursor1 = cursor0->next;
		}

		std::uniform_int_distribution<int> d(0, pairs.size() - 1);
		std::pair<Node*, Node*> p = pairs[d(*generator)];
		addConnection(p.first, p.second);

		// Set shape changed
		shapeChanged = true;
	}
	
}

void Genome::removeConnectionMutation()
{
	if (connections.size() > 0)
	{
		std::uniform_int_distribution<int> d(0, connections.size() - 1);
		removeConnection(connections[d(*generator)]);

		// Set shape changed
		shapeChanged = true;
	}
}

bool Genome::areConnected(Node* n0, Node* n1)
{
	bool connected = false;
	for (Connection* c : connections)
	{
		if ((c->from == n0 && c->to == n1)
			|| c->from == n1 && c->to == n0)
		{
			connected = true;
			break;
		}
	}
	return connected;
}

Genome::Connection* Genome::addConnection(Node* from, Node* to)
{
	// Create connection
	Connection* c = new Connection(from, to);
	to->incomingConnections.push_back(c);
	connections.push_back(c);
	return c;
}

void Genome::removeNode(Node* node)
{
	// Find node in the list
	Node* n = root;
	while (n && n->next != node)
	{
		n=n->next;
	}

	// n->next is the searched node in the list if not nullptr
	if (n)
	{
		if (n->next)
		{
			// Remove connexions
			std::vector<Connection*> connectionsToRemove;
			for (Connection* c : connections)
			{
				if (c->from == node || c->to == node)
					connectionsToRemove.push_back(c);
			}
			for (Connection* c : connectionsToRemove)
			{
				removeConnection(c);
			}

			// Jump the removed node if necessary
			if (n->next->next)
			{
				n->next = n->next->next;
				while (n)
				{
					if (n->next)
						n->next->idx = n->idx + 1;
					n = n->next;
				}
			}			
		}
	}
	delete node;
	size--;
}

void Genome::removeConnection(Connection* connection)
{
	// Remove in the node's incoming connections
	connection->to->incomingConnections.erase(std::remove_if(connection->to->incomingConnections.begin(), connection->to->incomingConnections.end(),
		[connection](Connection*& c)
		{
			return c == connection;
		}
	));
	// Remove from dictionnary
	connections.erase(std::remove(connections.begin(), connections.end(), connection), connections.end());
	delete connection;
	connection = nullptr;
}