#pragma once

#include <string>
#include <vector>

class Interpretor
{
public:

	static void Read(const std::string& _line);

private:
	static std::vector<std::string> GetArgs(const std::string& _line);
};
