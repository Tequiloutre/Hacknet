#include "VM.h"

#include "FileSystem/File.h"
#include "FileSystem/Folder.h"
#include <iostream>
#include "System/Account.h"
#include "Network/Node.h"
#include "Network/Port.h"
#include "Network/WAN.h"
#include "Processes/Commands.h"
#include "Processes/PortProcess.h"
#include "Saver.h"
#include "Network/User.h"
#include "Processes/PortHack.h"
#include "System/Interpretor.h"

#include <iostream>
#include <conio.h>

using namespace std;

VM::~VM()
{
	for (const Account* _account : accounts)
		delete _account;
	accounts.clear();
 }

int VM::GetChNoBlock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

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

std::string VM::GetCommandStartingWith(const std::string& _input)
{
	if (_input.empty()) return "";
	for (Process* _command : commands)
	{
		const size_t _inputLength = _input.length();
		string _commandName = _command->GetName();
		if (_commandName.size() < _inputLength) continue;
		const string _prefix = string(_commandName.begin(), _commandName.begin() + _inputLength);
		if (_prefix != _input) continue;
		return _commandName;
	}
	return _input;
}

void VM::StartUp()
{
	Log("Starting {} v{}...", name, version);

	LoadAccounts();
	ShowMainScreen();

	InitCommands();
	isOn = true;
}

void VM::Update()
{
	if (isBusy) return;
	cout << endl << activeAccount->GetUsername() << '@' << activeNode->GetName() << ":" << activeFolder->GetPath() << "/$ ";

	input = "";

	int _input = -1;
	while (_input != '\r')
	{
		switch (_input)
		{
			case -1:
				break;
			case '\t':
				for (size_t i = 0; i < input.size(); ++i)
					cout << '\b' << ' ' << '\b';
				
				input = GetCommandStartingWith(input);
				cout << input;
				break;
			case '\b':
				if (input.empty()) break;
				cout << '\b' << ' ' << '\b';
				input.erase(input.end() - 1);
				break;
			case 224:
				switch (_getch())
				{
					case 72:
						if (historyIndex == 0) break;
						for (size_t i = 0; i < input.size(); ++i)
							cout << '\b' << ' ' << '\b';
						--historyIndex;
						input = inputHistory[historyIndex];
						cout << input;
						break;
					case 80:
						cout << "down";
						break;
					default: break;
				}
				break;
			default:
				const char _char = static_cast<char>(_input);
				cout << _char;
				input.push_back(_char);
				break;
		}

		_input = GetChNoBlock();
	}

	inputHistory.push_back(input);
	historyIndex = inputHistory.size();

	cout << endl;
	Interpretor::Read(input);
}

void VM::Shutdown()
{
	Log("Shutting down...");
	
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
	activeNode = WAN::GetNode(activeAccount->GetOriginNode());
	activeFolder = activeNode->GetRoot();
}

void VM::SetActiveFolder(Folder* _folder)
{
	activeFolder = _folder;
}

void VM::InitCommands()
{
	commands.push_back(new cat("cat"));
	commands.push_back(new cd("cd"));
	commands.push_back(new connect("connect"));
	commands.push_back(new disconnect("disconnect"));
	commands.push_back(new ip("ip"));
	commands.push_back(new ls("ls"));
	commands.push_back(new mkdir("mkdir"));
	commands.push_back(new PortHack("PortHack"));
	commands.push_back(new PortProcess("SSHCrack", PortType::SSH));
	commands.push_back(new PortProcess("FTPBounce", PortType::FTP));
	commands.push_back(new probe("probe"));
	commands.push_back(new rm("rm"));
	commands.push_back(new rmdir("rmdir"));
	commands.push_back(new save("save"));
	commands.push_back(new say("say"));
	commands.push_back(new shutdown("shutdown"));
	commands.push_back(new touch("touch"));
}

void VM::LoadAccounts()
{
	const vector<string> _accountNames = Saver::GetAccountList();
	for (const string& _accountName : _accountNames)
	{
		Account* _account = Saver::LoadAccount(_accountName);
		if (!_account) continue;
		accounts.push_back(_account);
	}
}

bool VM::AccountExist(const std::string& _username)
{
	for (const Account* _account : accounts)
	{
		if (_account->GetUsername() != _username) continue;
		return true;
	}
	return false;
}

void VM::CreateAccount(const std::string& _name, const std::string& _username, const std::string& _password)
{
	Node* _node = new Node
	(
		_name + "-PC",
		WAN::GetRandomIP(),
		vector<User*>
		{
			new User(_name, _username, _password, UserLevel::Admin)
		},
		vector<Port*>
		{
			new Port(PortType::SSH, 22),
			new Port(PortType::FTP, 21)
		},
		5
	);
	WAN::AddNode(_node);

	Account* _account = new Account(_name, _username, _password, _node->GetIP());
	accounts.push_back(_account);
	activeAccount = _account;

	Connect(_node);
	Folder* _testFolder = new Folder("test");
	_testFolder->AddFile(new File("test.txt", "gg you find this test file"));
	activeFolder->AddFolder(_testFolder);
	activeFolder->AddFile(new File("x-system.sys", "boup bip boup"));
	
	Node* _nassimNode = new Node
	(
		"Nassim-PC",
		WAN::GetRandomIP(),
		vector<Port*>
		{
			new Port(PortType::SSH, 22),
			new Port(PortType::FTP, 21)
		},
		1
	);
	WAN::AddNode(_nassimNode);
	Folder* _sysFolder = new Folder("sys", UserLevel::Admin);
	_sysFolder->AddFile(new File("x-system.sys"));
	_nassimNode->GetRoot()->AddFolder(_sysFolder);
	
	WAN::AddNode(new Node
	(
		"Thomas-PC",
		WAN::GetRandomIP(),
		vector<Port*>
		{
			new Port(PortType::SSH, 22),
			new Port(PortType::FTP, 21)
		},
		2
	));

	Saver::SaveGame();
}

bool VM::LoadAccount(const std::string& _username, const std::string& _password)
{
	for (Account* _account : accounts)
	{
		if (_account->GetUsername() != _username) continue;
		if (_account->GetPassword() != _password) break;
		activeAccount = _account;
		Saver::LoadGame(activeAccount->GetUsername());
		Connect(WAN::GetNode(activeAccount->GetOriginNode()));
		return true;
	}
	return false;
}

void VM::ShowMainScreen()
{
	Log("Welcome.");
	Log("1. Create account");
	Log("2. Load account");
	Log("3. Quit");

	int _choice = -1;
	while (_choice < 1 || _choice > 3)
	{
		string _input;
		getline(cin, _input);
		_choice = stoi(_input);
	}

	switch (_choice)
	{
		case 1: ShowCreateAccountScreen(); break;
		case 2: ShowLoadAccountScreen(); break;
		case 3: Shutdown(); break;
		default: break;
	}
}

void VM::ShowCreateAccountScreen()
{
	bool _loggedIn = false;
	
	while (!_loggedIn)
	{
		string _name;
		cout << "Name : ";
		getline(cin, _name);

		string _username = _name;
		ranges::transform(_username, _username.begin(),
			[](const unsigned char _c){ return std::tolower(_c); });

		if (AccountExist(_username))
		{
			cout << "Account " << _name << " already exists" << endl;
			continue;
		}

		string _password;
		cout << "Password : ";
		getline(cin, _password);

		CreateAccount(_name, _username, _password);
		_loggedIn = true;
	}
}

void VM::ShowLoadAccountScreen()
{
	bool _loggedIn = false;
	
	Log("Available accounts :");
	for (const Account* _account : accounts)
		Log(" - {}", _account->GetUsername());

	while (!_loggedIn)
	{
		string _username;
		cout << "Username : ";
		getline(cin, _username);

		string _password;
		cout << "Password : ";
		getline(cin, _password);

		_loggedIn = LoadAccount(_username, _password);
	}
}
