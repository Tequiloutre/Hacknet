#include "Port.h"

#include <nlohmann/json.hpp>

Port::Port(const PortType _type, const int _number)
{
	type = _type;
	number = _number;
}

nlohmann::json Port::ToJson()
{
	nlohmann::json _json;

	_json["type"] = type;
	_json["number"] = number;
	_json["isOpened"] = isOpened;

	return _json;
}

Port* Port::FromJson(const nlohmann::json& _json)
{
	return new Port
	(
		_json["type"],
		_json["number"]
	);
}

std::string Port::PortToString(const PortType _type)
{
	switch (_type)
	{
		case None: return "None";
		case SSH: return "SSH";
		case FTP: return "FTP";
	}
	return "None";
}
