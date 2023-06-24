#pragma once

#include <map>
#include "nlohmann/json.hpp"
#include "System/Singleton.h"

class Node;

class WAN : public Singleton<WAN>
{
	std::map<std::string, Node*> nodes;

public:

	~WAN();
	
	Node* GetNode(const std::string& _targetIP);
	
	void AddNode(Node* _node);
	std::string GetRandomIP();

	nlohmann::json ToJson();
	void FromJson(const nlohmann::json& _json);
};
