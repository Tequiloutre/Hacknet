﻿#pragma once
#include <string>
#include <nlohmann/json_fwd.hpp>

enum PortType
{
	None,
	SSH,
	FTP
};

class Port
{
	PortType type = None;
	int number = 0;
	bool isOpened = false;

public:

	static std::string PortToString(PortType _type);

	PortType GetType() const { return type; }
	int GetNumber() const { return number; }
	bool IsOpened() const { return isOpened; }
	
	Port(const PortType _type, const int _number)
	{
		type = _type;
		number = _number;
	}

	void Open() { isOpened = true; }

	nlohmann::json ToJson();
	static Port FromJson(const nlohmann::json& _json);
	
	std::string ToString() const { return PortToString(type); }
};
