#pragma once
#include "Process.h"

class PortHack : public Process
{
public:
	
	PortHack(const std::string& _name) : Process(_name) { }
	bool Execute(const std::vector<std::string>& _args) override;
};
