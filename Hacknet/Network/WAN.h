#pragma once

#include <map>
#include "Node.h"

class WAN
{
	inline static std::map<std::string, Node*> nodes;

public:

	~WAN();
	
	static bool GetNode(const std::string& _targetIP, Node** _outNode);
	
	static void AddNode(Node* _node);
	static std::string GetRandomIP();
};
