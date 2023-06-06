#pragma once
#include <string>
#include <vector>

#include "Network/Account.h"

class Node;

class Saver
{
	inline static std::string gameName = "ReHacknet";
	inline static std::string gameDir = "";
	
public:

	static std::string GetGameDir() { return gameDir; }
	static std::string GetSaveDir() { return gameDir + "Saves/"; }

private:

	static void InitGameDir();

public:

	static void Init();
	static void SaveNode(Node* _node);
	static Node* LoadNode(const std::string& _name);

	static std::vector<std::string> GetAccountList();
	static void SaveGame();
	static Account* LoadAccount(const std::string& _accountName);
	static void LoadGame(const std::string& _account);
};
