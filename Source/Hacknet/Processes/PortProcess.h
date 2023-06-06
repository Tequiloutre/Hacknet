#pragma once
#include "Network/Port.h"
#include "Processes/Process.h"

class PortProcess : public Process
{
	PortType targetType = SSH;

public:

	PortProcess(const std::string& _name, const PortType _portType) : Process(_name)
	{
		targetType = _portType;
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
