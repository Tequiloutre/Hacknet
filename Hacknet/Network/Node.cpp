#include "Node.h"

using namespace std;

Node::Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	rootFolder = new Folder("");
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::~Node()
{
	delete rootFolder;
	std::vector<Port*>().swap(ports);
}
