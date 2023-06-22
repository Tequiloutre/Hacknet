#pragma once

#include <string>
#include <vector>

class Process
{
protected:
	
	std::string name = "process";

public:

	std::string GetName() { return name; }

	Process(const std::string& _name);
	virtual ~Process() = default;
	
	virtual bool Execute(const std::vector<std::string>& _args) = 0;
};
