#include "WAN.h"

#include "System/VM.h"

using namespace std;

WAN::~WAN()
{
	for (const auto& _node : nodes)
		delete _node.second;
	nodes.clear();
}

bool WAN::GetNode(const string& _targetIP, Node** _outNode)
{
	if (!nodes.contains(_targetIP)) return false;
	*_outNode = nodes[_targetIP];
	return true;
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
