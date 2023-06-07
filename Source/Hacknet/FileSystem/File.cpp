#include "File.h"

File::File(const std::string& _name)
{
	name = _name;
}

File::File(const std::string& _name, const std::string& _content)
{
	name = _name;
	content = _content;
}
