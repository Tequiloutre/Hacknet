#include "Account.h"

using namespace nlohmann;

Account::Account(const std::string& _name, const std::string& _username, const std::string& _password, const std::string& _originNode)
{
	name = _name;
	username = _username;
	password = _password;
	originNode = _originNode;
}

json Account::ToJson() const
{
	json _json;
	
	_json["name"] = name;
	_json["username"] = username;
	_json["password"] = password;
	_json["originNode"] = originNode;
	
	return _json;
}

Account Account::FromJson(const json& _json)
{
	return
	{
		_json["name"],
		_json["username"],
		_json["password"],
		_json["originNode"]
	};
}
