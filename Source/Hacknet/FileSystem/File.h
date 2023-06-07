#pragma once
#include <string>

class File
{
	std::string name = "";
	std::string content = "";
	
public:

	File(const std::string& _name);
	File(const std::string& _name, const std::string& _content);

	std::string GetName() const { return name; }
	std::string GetContent() const { return content; }

	void SetName(const std::string& _name) { name = _name; }
	void SetContent(const std::string& _content) { content = _content; }
};
