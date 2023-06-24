#pragma once

#include <nlohmann/json.hpp>
#include "PortType.h"
#include <string>

class Port
{
	PortType type = PortType::None;
	int number = 0;
	bool isOpened = false;

public:

	Port(PortType _type, int _number, bool _isOpened = false);

	PortType GetType() const { return type; }
	int GetNumber() const { return number; }
	bool IsOpened() const { return isOpened; }

	void Open() { isOpened = true; }

	nlohmann::json ToJson();
	static Port* FromJson(const nlohmann::json& _json);
	static std::string PortToString(PortType _type);
	std::string ToString() const { return PortToString(type); }
};
