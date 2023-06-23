#include "Saver.h"

#include <filesystem>
#include <fstream>
#include "Network/Node.h"
#include "Network/WAN.h"
#include "nlohmann/json.hpp"
#include "System/Account.h"
#include "VM.h"

using namespace nlohmann;
using namespace std;

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

void Saver::Init()
{
	InitGameDir();
}

void Saver::SaveNode(Node* _node)
{
	const string _dir = GetSaveDir();
	const string _filePath = _dir + "Node_" + _node->GetName() + ".sav";

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
	const string _filePath = _dir + "Node_" + _name + ".sav";

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

	string _test;
	json _json;
	_file >> _json;
	_file.close();

	Node* _node = Node::FromJson(_json);
	WAN::AddNode(_node);
	return _node;
}

std::vector<string> Saver::GetAccountList()
{
	const string _dir = GetSaveDir();

	vector<string> _accounts;
	for (const auto& _file : filesystem::directory_iterator(_dir))
		_accounts.push_back(_file.path().filename().string());

	return _accounts;
}

void Saver::SaveGame()
{
	Account* _account = VM::GetActiveAccount();
	
	const string _dir = GetSaveDir();
	const string _filePath = _dir + _account->GetUsername() + ".sav";
	
	json _json;
	
	_json["account"] = _account->ToJson();
	_json["wan"] = WAN::ToJson();

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
	_file << setw(4) << _json;
	_file.close();
}

Account* Saver::LoadAccount(const string& _accountName)
{
	const string _dir = GetSaveDir();
	const string _filePath = _dir + _accountName;

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

	json _account = _json["account"];
	return new Account
	(
		_account["name"],
		_account["username"],
		_account["password"],
		_account["originNode"]
	);
}

void Saver::LoadGame(const std::string& _account)
{
	const string _dir = GetSaveDir();
	const string _filePath = _dir + _account + ".sav";
	
	ifstream _file(_filePath);
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

	json _json;
	_file >> _json;
	_file.close();

	WAN::FromJson(_json["wan"]);
}
