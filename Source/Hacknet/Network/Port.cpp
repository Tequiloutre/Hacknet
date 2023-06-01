#include "Port.h"

#include <nlohmann/json.hpp>

std::string Port::GetType() const
{
	switch (type)
	{
		case None: return "None";
		case SSH: return "SSH";
		case FTP: return "FTP";
	}
	return "None";
}

nlohmann::json Port::ToJson()
{
	nlohmann::json _json;

	_json["type"] = type;
	_json["number"] = number;
	_json["isOpened"] = isOpened;

	return _json;
}

Port Port::FromJson(const nlohmann::json& _json)
{
	return
	{
		_json["type"],
		_json["number"]
	};
}
