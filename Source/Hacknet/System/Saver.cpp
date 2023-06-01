#include "Saver.h"

#include <fstream>

#include "VM.h"
#include "Network/Node.h"
#include "Network/WAN.h"
#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

void Saver::Init()
{
	InitGameDir();
}

void Saver::SaveNode(Node* _node)
{
	const string _dir = GetSaveDir();
	const string _filePath = _dir + "Node_" + _node->GetName() + ".json";

	VM::Log("[Saver] Saving node at : {}", _filePath);
	
	ofstream _file(_filePath);
	if (_file.bad())
	{
		VM::Log("[Saver] Incorrect path : {}", _filePath);
		return;
	}
	if(!_file.is_open())
	{
		VM::Log("[Saver] Unable to open file : {}", _filePath);
		return;
	}
	_file << setw(4) << _node->ToJson();
	_file.close();
}

Node* Saver::LoadNode(const std::string& _name)
{
	const string _dir = GetSaveDir();
	const string _filePath = _dir + "Node_" + _name + ".json";

	VM::Log("[Saver] Loading node at : {}", _filePath);

	ifstream _file(_filePath);
	if (_file.bad())
	{
		VM::Log("[Saver] Incorrect path : {}", _filePath);
		return nullptr;
	}
	if(!_file.is_open())
	{
		VM::Log("[Saver] Unable to open file : {}", _filePath);
		return nullptr;
	}

	json _json;
	_file >> _json;
	_file.close();

	Node* _node = new Node(Node::FromJson(_json));
	WAN::AddNode(_node);
	return _node;
}

void Saver::InitGameDir()
{
	char* _buffer;
	size_t _length;
	if (_dupenv_s(&_buffer, &_length, "USERPROFILE")) return;

	gameDir = string(_buffer);
	ranges::replace(gameDir, '\\', '/');
	gameDir += "/Documents/My Games/ReHacknet/";

	delete _buffer;
}
