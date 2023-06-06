#include "Node.h"

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

Node::Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	rootFolder = new Folder("");
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::Node(const std::string& _name, const std::string& _ip, Folder* _rootFolder, const std::vector<Port*>& _ports,
	int _requiredPorts)
{
	name = _name;
	ip = _ip;
	rootFolder = _rootFolder;
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::~Node()
{
	delete rootFolder;
	for (const auto _port : ports)
		delete _port;
	ports.clear();
}

Port* Node::GetPort(const int _portNumber) const
{
	for (Port* _port : ports)
	{
		if (_port->GetNumber() != _portNumber) continue;
		return _port;
	}
	return nullptr;
}

json Node::ToJson()
{
	json _json;
	
	_json["name"] = name;
	_json["ip"] = ip;
	_json["rootFolder"] = rootFolder->ToJson();
	
	const size_t _portCount = ports.size();
	for (size_t i = 0; i < _portCount; ++i)
		_json["ports"][i] = ports[i]->ToJson();

	_json["requiredPorts"] = requiredPorts;
	
	return _json;
}

Node Node::FromJson(const json& _json)
{
	const vector<json> _portsJson = _json["ports"];
	const size_t _portCount = _portsJson.size();
	
	vector<Port*> _ports;
	for (size_t i = 0; i < _portCount; ++i)
		_ports.push_back(new Port(Port::FromJson(_portsJson[i])));

	return
	{
		_json["name"],
		_json["ip"],
		new Folder(Folder::FromJson(_json["rootFolder"])),
		_ports,
		_json["requiredPorts"]
	};
}
