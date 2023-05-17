#include "VM.h"

#include <iostream>

#include "Interpretor.h"
#include "Commands/connect.h"
#include "Commands/disconnect.h"
#include "Commands/say.h"
#include "Commands/shutdown.h"
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

void VM::StartUp()
{
	isOn = true;
	Log("Starting {} v{}...", name, version);

	originNode = WAN::CreateNode();
	activeNode = originNode;
	activeFolder = originNode->GetRoot();
	
	WAN::CreateNode();
	WAN::CreateNode();
	WAN::CreateNode();
	WAN::CreateNode();

	InitCommands();
}

void VM::Update()
{
	if (isBusy) return;
	cout << login << '@' << activeNode->GetIP() << ":" << activeFolder->GetPath() << "/$ ";
	string args;
	getline(cin, args);
	Interpretor::Read(args);
}

void VM::Shutdown()
{
	for (const auto _command : commands)
		delete _command;

	isOn = false;
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
	commands.push_back(new shutdown());
}
