#include "VM.h"

#include <iostream>

#include "Interpretor.h"
#include "Commands/connect.h"
#include "Commands/disconnect.h"
#include "Commands/say.h"
#include "Network/WAN.h"

using namespace std;

bool VM::Execute(const std::string& _commandName, const std::vector<std::string>& _args)
{
	const size_t _count = commands.size();
	for (size_t i = 0; i < _count; ++i)
	{
		if (commands[i]->GetName() != _commandName) continue;
		return commands[i]->Execute(_args);
	}
	Log("Unknown command : {}", _commandName);
	return false;
}

void VM::Start()
{
	isOn = true;
	Log("Starting {} v{}...", name, version);

	originNode = WAN::CreateNode();
	activeNode = originNode;
	
	WAN::CreateNode();
	WAN::CreateNode();
	WAN::CreateNode();
	WAN::CreateNode();

	InitCommands();
}

void VM::Update()
{
	if (isBusy) return;
	cout << activeNode->GetIP() << "> ";
	string args;
	getline(cin, args);
	Interpretor::Read(args);
}

void VM::Exit()
{
	const size_t _count = commands.size();
	for (size_t i = 0; i < _count; ++i)
		delete commands[i];
}

void VM::Connect(Node* _node)
{
	activeNode = _node;
}

void VM::Disconnect()
{
	activeNode = originNode;
}

void VM::InitCommands()
{
	commands.push_back(new say());
	commands.push_back(new connect());
	commands.push_back(new disconnect());
}
