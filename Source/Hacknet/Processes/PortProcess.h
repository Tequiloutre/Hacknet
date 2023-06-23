#pragma once

#include "Network/PortType.h"
#include "Processes/Process.h"

class PortProcess : public Process
{
	PortType targetType = PortType::SSH;

public:

	PortProcess(const std::string& _name, PortType _portType);

	bool Execute(const std::vector<std::string>& _args) override;
};
