#pragma once

#include <map>
#include "Network/Node.h"
#include "nlohmann/json.hpp"

class WAN
{
	inline static std::map<std::string, Node*> nodes;

public:

	~WAN();
	
	static bool GetNode(const std::string& _targetIP, Node** _outNode);
	
	static void AddNode(Node* _node);
	static std::string GetRandomIP();

	static nlohmann::json ToJson();
	static WAN FromJson(const nlohmann::json& _json);
};
