#include "Node.h"

Node::Node(const std::string& _name, const std::string& _ip)
{
	name = _name;
	ip = _ip;
	rootFolder = new Folder("");
}

Node::~Node()
{
	delete rootFolder;
}
