#include "Port.h"

#include <nlohmann/json.hpp>

Port::Port(const PortType _type, const int _number, const bool _isOpened)
{
	type = _type;
	number = _number;
	isOpened = _isOpened;
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
		_json["number"],
		_json["isOpened"]
	);
}

std::string Port::PortToString(const PortType _type)
{
	switch (_type)
	{
		case PortType::None: return "None";
		case PortType::SSH: return "SSH";
		case PortType::FTP: return "FTP";
	}
	return "None";
}
