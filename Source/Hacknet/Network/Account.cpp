#include "Account.h"

#include "WAN.h"

using namespace nlohmann;

Account::Account(const std::string& _name, const std::string& _username, const std::string& _password, Node* _originNode)
{
	name = _name;
	username = _username;
	password = _password;
	originNode = _originNode;
}

json Account::ToJson()
{
	json _json;
	
	_json["name"] = name;
	_json["username"] = username;
	_json["password"] = password;
	
	return _json;
}

Account Account::FromJson(const json& _json)
{
	Node* _node = nullptr;
	WAN::GetNode(_json["originNodeIP"], &_node);
	return
	{
		_json["name"],
		_json["username"],
		_json["password"],
		_node
	};
}
