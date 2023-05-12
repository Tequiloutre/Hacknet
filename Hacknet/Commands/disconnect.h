#pragma once
#include "../Process.h"

class disconnect : public Process
{
public:

	disconnect()
	{
		name = "disconnect";
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
