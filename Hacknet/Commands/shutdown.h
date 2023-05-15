#pragma once
#include "../Process.h"

class shutdown : public Process
{
public:
	
	shutdown()
	{
		name = "shutdown";
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
