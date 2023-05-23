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

	originNode = new Node
	(
		"Youen-PC",
		WAN::GetRandomIP(),
		vector<Port*>
		{
			new Port(SSH, 22),
			new Port(FTP, 21)
		},
		5
	);
	WAN::AddNode(originNode);
	activeNode = originNode;
	activeFolder = originNode->GetRoot();
	activeFolder->AddFolder(new Folder("test"));

	WAN::AddNode(new Node
	(
		"Nassim-PC",
		WAN::GetRandomIP(),
		vector<Port*>
		{
			new Port(SSH, 22),
			new Port(FTP, 21)
		},
		1
	));

	WAN::AddNode(new Node
	(
		"Thomas-PC",
		WAN::GetRandomIP(),
		vector<Port*>
		{
			new Port(SSH, 22),
			new Port(FTP, 21)
		},
		2
	));
	
	InitCommands();
}

void VM::Update()
{
	if (isBusy) return;
	cout << endl << login << '@' << activeNode->GetName() << ":" << activeFolder->GetPath() << "/$ ";
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
	commands.push_back(new probe("probe"));
}
