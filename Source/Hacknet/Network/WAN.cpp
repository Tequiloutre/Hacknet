#include "WAN.h"

#include "Network/Node.h"
#include "System/VM.h"

using namespace nlohmann;
using namespace std;

WAN::~WAN()
{
	for (const auto& _node : nodes)
		delete _node.second;
	nodes.clear();
}

Node* WAN::GetNode(const string& _targetIP)
{
	if (!nodes.contains(_targetIP)) return nullptr;
	return nodes[_targetIP];
}

void WAN::AddNode(Node* _node)
{
	const string _ip = _node->GetIP();
	nodes.emplace(_ip, _node);
	VM::Log("Added node : {}", _ip);
}

string WAN::GetRandomIP()
{
	string _newIp = to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255);
	if (!nodes.contains(_newIp)) return _newIp;
	return GetRandomIP();
}

json WAN::ToJson()
{
	json _json;

	int _index = 0;
	for (const auto& _node : nodes)
	{
		_json["nodes"][_index] = _node.second->ToJson();
		++_index;
	}

	return _json;
}

void WAN::FromJson(const json& _json)
{
	const vector<json>& _nodes = _json["nodes"];
	const size_t _nodeCount = _nodes.size();
	for (size_t i = 0; i < _nodeCount; ++i)
		AddNode(Node::FromJson(_nodes[i]));
}
