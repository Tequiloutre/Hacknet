#pragma once
#include "../Process.h"

class ls : public Process
{
public:
	
	ls()
	{
		name = "ls";
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
