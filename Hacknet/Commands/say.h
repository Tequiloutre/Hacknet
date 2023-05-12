#pragma once
#include "../Process.h"

class say : public Process
{
public:

	say()
	{
		name = "say";
	}

	bool Execute(const std::vector<std::string>& _args) override;
};
