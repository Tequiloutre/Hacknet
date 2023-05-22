#include "VM.h"

#include <iostream>

#include "Interpretor.h"
#include "Processes/Commands.h"
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
	activeFolder->AddFolder(new Folder("test"));
	
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
	activeFolder = _node->GetRoot();
}

void VM::Disconnect()
{
	activeNode = originNode;
	activeFolder = originNode->GetRoot();
}

void VM::SetActiveFolder(Folder* _folder)
{
	activeFolder = _folder;
}

void VM::InitCommands()
{
	commands.push_back(new say("say"));
	commands.push_back(new connect("connect"));
	commands.push_back(new disconnect("disconnect"));
	commands.push_back(new shutdown("shutdown"));
	commands.push_back(new ls("ls"));
	commands.push_back(new cd("cd"));
}
