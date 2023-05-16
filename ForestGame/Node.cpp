#include "Node.h"

namespace Engine
{
	// node implementation
	Node::Node(std::string name, Node* parent)
	{
		this->name = name;
		this->parent = parent;
	}

	void Node::update(double& deltaTime) 
	{
		for (Node node: nodes)
			node.update(deltaTime);
	}

	void Node::render(sf::RenderWindow& window)
	{
		for (Node node: nodes)
			node.render(window);
	}

	const std::string& Node::getName() const
	{
		return this->name;
	}

	const Node* Node::getParent() const {
		return this->parent;
	}

	void Node::setParent(Node* parent) {
		this->parent = parent;
	}

	bool operator==(const Node& a, const Node& b)
	{
		return !strcmp(a.name.c_str(), b.name.c_str());
	}

	bool operator!=(const Node& a, const Node& b)
	{
		return !(a == b);
	}

	bool operator<(const Node& a, const Node& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) < 0;
	}

	bool operator>(const Node& a, const Node& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) > 0;
	}

	bool operator<=(const Node& a, const Node& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) <= 0;
	}

	bool operator>=(const Node& a, const Node& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) >= 0;
	}


	// event implementation
	Event::Event(std::string name)
	{
		this->name = std::move(name);
	}

	void Event::addAction(ActionSignature action)
	{
		actions.push_back(action);
	}

	void Event::removeAction(std::list<ActionSignature>::iterator& it)
	{
		actions.erase(it);
	}

	void Event::invoke()
	{
		invoke(nullptr);
	}

	void Event::invoke(void* data)
	{
		for (auto& action : actions)
			action(name, data);
	}

	bool operator==(const Event& a, const Event& b)
	{
		return !strcmp(a.name.c_str(), b.name.c_str());
	}

	bool operator!=(const Event& a, const Event& b)
	{
		return !(a == b);
	}

	bool operator<(const Event& a, const Event& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) < 0;
	}

	bool operator>(const Event& a, const Event& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) > 0;
	}

	bool operator<=(const Event& a, const Event& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) <= 0;
	}

	bool operator>=(const Event& a, const Event& b)
	{
		return strcmp(a.name.c_str(), b.name.c_str()) >= 0;
	}
}
