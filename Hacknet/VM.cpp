#include "VM.h"

#include <iostream>

#include "Interpretor.h"
#include "Commands/say.h"

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
	InitCommands();
}

void VM::Update()
{
	if (isBusy) return;
	cout << "> ";
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

void VM::InitCommands()
{
	commands.push_back(new say());
}
