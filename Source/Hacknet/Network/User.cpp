#include "User.h"

using namespace nlohmann;

User::User(const std::string& _name, const std::string& _username, const std::string& _password, const UserLevel _level)
{
	name = _name;
	username = _username;
	password = _password;
	level = _level;
}

json User::ToJson() const
{
	json _json;

	_json["name"] = name;
	_json["username"] = username;
	_json["password"] = password;
	_json["level"] = level;

	return _json;
}

User* User::FromJson(const json& _json)
{
	return new User
	(
		_json["name"],
		_json["username"],
		_json["password"],
		_json["level"]
	);
}
