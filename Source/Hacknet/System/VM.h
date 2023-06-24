#pragma once

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "Singleton.h"

class Account;
class Node;
class Process;
class Folder;

class VM : public Singleton<VM>
{
	std::string name = "Hacknet";
	std::string version = "0.1";
	std::vector<Account*> accounts;
	Account* activeAccount = nullptr;
	bool isOn = false;
	bool isBusy = false;

	Node* activeNode = nullptr;
	Folder* activeFolder = nullptr;

	std::vector<Process*> commands;

	std::string input = "";
	std::vector<std::string> inputHistory;
	int historyIndex = 0;

public:

	~VM();

	static int GetChNoBlock();
	
	std::string GetName() const { return name; }
	std::string GetVersion() const { return version; }
	Account* GetActiveAccount() const { return activeAccount; }
	Node* GetActiveNode() const { return activeNode; }
	Folder* GetActiveFolder() const { return activeFolder; }
	bool IsOn() const { return isOn; }
	std::string GetCommandStartingWith(const std::string& _input) const;
	
	template<typename... T>
	static std::string ToString(const std::string& _format, const T&... _args)
	{
		return std::vformat(_format, std::make_format_args(_args...));
	}
	template<typename T>
	static void Log(const T& _args)
	{
		std::cout << _args << std::endl;
	}
	template<typename... T>
	static void Log(const std::string& _format, const T&... _args)
	{
		std::cout << ToString(_format, _args...) << std::endl;
	}

	void StartUp();
	void Update();
	void Shutdown();

	bool Execute(const std::string& _commandName, const std::vector<std::string>& _args);
	void Connect(Node* _node);
	void Disconnect();
	void SetActiveFolder(Folder* _folder);

private:
	
	void InitCommands();

	void LoadAccounts();
	bool AccountExist(const std::string& _username);
	void CreateAccount(const std::string& _name, const std::string& _username, const std::string& _password);
	bool LoadAccount(const std::string& _username, const std::string& _password);

	void ShowMainScreen();
	void ShowCreateAccountScreen();
	void ShowLoadAccountScreen();
};
