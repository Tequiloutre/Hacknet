#include "File.h"

using namespace nlohmann;

File::File(const std::string& _name)
{
	name = _name;
}

File::File(const std::string& _name, const std::string& _content)
{
	name = _name;
	content = _content;
}

json File::ToJson()
{
	json _json;

	_json["name"] = name;
	_json["content"] = content;

	return _json;
}

File* File::FromJson(const json& _json)
{
	return new File(_json["name"], _json["content"]);
}
