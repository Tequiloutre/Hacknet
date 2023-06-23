#include "Node.h"

#include "FileSystem/Folder.h"
#include "Network/Port.h"
#include "Network/User.h"

using namespace nlohmann;
using namespace std;

Node::Node(const std::string& _name, const std::string& _ip, const std::vector<Port*>& _ports, const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	rootFolder = new Folder("");
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::Node(const std::string& _name, const std::string& _ip, Folder* _rootFolder, const std::vector<Port*>& _ports,
	const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	rootFolder = _rootFolder;
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::Node(const std::string& _name, const std::string& _ip, const std::vector<User*>& _users,
	const std::vector<Port*>& _ports, const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	users = _users;
	rootFolder = new Folder("");
	ports = _ports;
	requiredPorts = _requiredPorts;
}

Node::Node(const std::string& _name, const std::string& _ip, const std::vector<User*>& _users,
			Folder* _rootFolder, const std::vector<Port*>& _ports, const int _requiredPorts)
{
	name = _name;
	ip = _ip;
	users = _users;
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
	
	for (const auto _user : users)
		delete _user;
	users.clear();
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

void Node::AddUser(User* _user)
{
	for (const User* _tempUser : users)
		if (_tempUser->GetUsername() == _user->GetUsername()) return;
	users.push_back(_user);
}

User* Node::Login(const std::string& _username, const std::string& _password) const
{
	for (User* _user : users)
	{
		if (_user->GetUsername() != _username) continue;
		if (_user->GetPassword() != _password) return nullptr;
		return _user;
	}
	return nullptr;
}

UserLevel Node::GetUserLevel(const std::string& _username) const
{
	for (const User* _user : users)
	{
		if (_user->GetUsername() != _username) continue;
		return _user->GetLevel();
	}
	return UserLevel::Guest;
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

	const size_t _userCount = users.size();
	for (size_t i = 0; i < _userCount; ++i)
		_json["users"][i] = users[i]->ToJson();
	
	return _json;
}

Node* Node::FromJson(const json& _json)
{
	vector<Port*> _ports;
	if (_json.contains("ports"))
	{
		const vector<json> _portsJson = _json["ports"];
		const size_t _portCount = _portsJson.size();
	
		for (size_t i = 0; i < _portCount; ++i)
			_ports.push_back(Port::FromJson(_portsJson[i]));
	}
	
	vector<User*> _users;
	if (_json.contains("users"))
	{
		const vector<json> _usersJson = _json["users"];
		const size_t _userCount = _usersJson.size();

		for (size_t i = 0; i < _userCount; ++i)
			_users.push_back(User::FromJson(_usersJson[i]));
	}

	return new Node
	(
		_json["name"],
		_json["ip"],
		_users,
		Folder::FromJson(_json["rootFolder"]),
		_ports,
		_json["requiredPorts"]
	);
}
