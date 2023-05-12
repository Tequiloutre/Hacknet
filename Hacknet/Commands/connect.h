#pragma once
#include "../Process.h"

class connect : public Process
{
public:

	connect()
	{
		name = "connect";
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
