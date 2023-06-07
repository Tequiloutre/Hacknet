#pragma once

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "Processes/Process.h"
#include "Network/Node.h"

class Account;

class VM
{
	inline static std::string name = "Hacknet";
	inline static std::string version = "0.1";
	inline static std::vector<Account*> accounts;
	inline static Account* activeAccount = nullptr;
	inline static bool isOn = false;
	inline static bool isBusy = false;

	inline static Node* activeNode = nullptr;
	inline static Folder* activeFolder = nullptr;

	inline static std::vector<Process*> commands;

public:

	~VM();

	static std::string GetName() { return name; }
	static std::string GetVersion() { return version; }
	static Account* GetActiveAccount() { return activeAccount; }
	static Node* GetActiveNode() { return activeNode; }
	static Folder* GetActiveFolder() { return activeFolder; }
	static bool IsOn() { return isOn; }
	static bool Execute(const std::string& _commandName, const std::vector<std::string>& _args);

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

	static void StartUp();
	static void Update();
	static void Shutdown();

	static void Connect(Node* _node);
	static void Disconnect();

	static void SetActiveFolder(Folder* _folder);

private:
	
	static void InitCommands();
	static void LoadAccounts();

	static bool AccountExist(const std::string& _username);
	static void CreateAccount(const std::string& _name, const std::string& _username, const std::string& _password);
	static bool LoadAccount(const std::string& _username, const std::string& _password);

	static void ShowMainScreen();
	static void ShowCreateAccountScreen();
	static void ShowLoadAccountScreen();
};
