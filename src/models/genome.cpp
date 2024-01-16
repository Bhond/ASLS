#include "genome.h"

Genome::Genome()
{

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
	// Destroy all nodes properly
	Node* current = root->next;
	delete root;
	while (current)
	{
		Node* tmp = current->next;
		delete current;
		if (tmp)
		{
			current = tmp->next;
		}
	}
}

void Genome::update()
{

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
			if (current->selfConnection->gater)
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

void Genome::addNode(const std::string& name, NodeTypes type, SquashTypes squash)
{
	Node* n = new Node(name, type, squash);
	addNode(n);
}

void Genome::addNode(Node* node)
{
	if (!root)
	{
		root = node;
	}
	else
	{
		switch(node->type)
		{
		case NodeTypes::Input:
			addInputNode(node);
			break;
		case Hidden:
			addHiddenNode(node);
			break;
		case Output:
			addOutputNode(node);
			break;
		}
	}
}

void Genome::addInputNode(Node* toInsert)
{
	Node* after = root;
	while (after->next && after->next->type == NodeTypes::Input)
	{
		after = after->next;
	}
	insertNode(toInsert, after);
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
		toInsert->idx = after->next->idx + 1;
	}
}

void Genome::addConnection(Node* from, Node* to)
{
	to->incomingConnections.push_back(new Connection(from, to));
}

void Genome::removeNode(Node* node)
{
	Node* n = root;
	while (n && n != node)
	{
		n=n->next;
	}

	if (n->next)
	{
		if (n->next->next)
		{
			n->next = n->next->next;
			while (n->next)
			{
				n->next->idx = n->idx + 1;
				n = n->next;
			}
		}
	}
	delete node;
}

void Genome::removeConnection(Node* from, Node* to)
{
	std::remove_if(to->incomingConnections.begin(), to->incomingConnections.end(),
		[from](Connection*& connection)
		{
			return connection->from == from;
		}
	);
}