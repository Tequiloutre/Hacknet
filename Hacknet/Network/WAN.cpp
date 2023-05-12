#include "WAN.h"

#include "../VM.h"

using namespace std;

Node* WAN::CreateNode()
{
	string _ip = GetRandomIP();
	Node* _node = new Node(_ip, _ip);
	nodes.emplace(_ip, _node);
	VM::Log("Created node : {}", _ip);
	return _node;
}

bool WAN::GetNode(const string& _targetIP, Node** _outNode)
{
	if (!nodes.contains(_targetIP)) return false;
	*_outNode = nodes[_targetIP];
	return true;
}

string WAN::GetRandomIP()
{
	string _newIp = to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255);
	if (!nodes.contains(_newIp)) return _newIp;
	return GetRandomIP();
}
