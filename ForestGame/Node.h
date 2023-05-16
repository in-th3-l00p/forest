#pragma once

#include <string>
#include <vector>
#include <set>
#include <functional>
#include <list>
#include <cstring>
#include <SFML/Graphics.hpp>

namespace Engine {
	// an event is used by a node
	// it simply has an identifier (a name) and functions that are call onced it is invoked
	class Event {
		using ActionSignature = std::function<void(std::string&, void*)>;

	private:
		std::string name;
		std::list<ActionSignature> actions;

	public:
		explicit Event(std::string name);
		void addAction(ActionSignature action);
		void removeAction(std::list<ActionSignature>::iterator& it);
		void invoke(); // simply calls all the actions
		void invoke(void* data);

		// used for storing it in a set
		friend bool operator==(const Event& a, const Event& b);
		friend bool operator!=(const Event& a, const Event& b);
		friend bool operator<(const Event& a, const Event& b);
		friend bool operator>(const Event& a, const Event& b);
		friend bool operator<=(const Event& a, const Event& b);
		friend bool operator>=(const Event& a, const Event& b);
	};

	/*
		The game engine is based off a node system
		A node can be basically every component of the game
		It will mainly be used as something rendered on the screen
		that handles events
		Also, a node is a tree that contains more nodes
	*/
	class Node
	{
	private:
		std::string name;
		Node* parent;
		std::set<Event> events;
		std::set<Node> nodes;

	public:
		Node(std::string name, Node* parent = nullptr);

		// both functions are running in the game loop, one handles logics and the other rendering
		virtual void update(double& deltaTime);
		virtual void render(sf::RenderWindow& window);

		const std::string& getName() const;
		const Node* getParent() const;
		void setParent(Node* parent);

		void addNode(Node& node); // adds a node to the tree
		void removeNode(Node& node);
		std::set<Node>::iterator begin() {
			return nodes.begin();
		}
		std::set<Node>::iterator end() {
			return nodes.end();
		}

		// used for storing it in a set
		friend bool operator==(const Node& a, const Node& b);
		friend bool operator!=(const Node& a, const Node& b);
		friend bool operator<(const Node& a, const Node& b);
		friend bool operator>(const Node& a, const Node& b);
		friend bool operator<=(const Node& a, const Node& b);
		friend bool operator>=(const Node& a, const Node& b);
	};
}

