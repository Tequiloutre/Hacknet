#pragma once

#include <map>
#include "nlohmann/json.hpp"

class Node;

class WAN
{
	inline static std::map<std::string, Node*> nodes;

public:

	~WAN();
	
	static Node* GetNode(const std::string& _targetIP);
	
	static void AddNode(Node* _node);
	static std::string GetRandomIP();

	static nlohmann::json ToJson();
	static void FromJson(const nlohmann::json& _json);
};
