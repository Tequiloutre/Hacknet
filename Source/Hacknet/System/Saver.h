#pragma once
#include <string>

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

	static void SaveGame();
	static void LoadAccount(const std::string& _accountName);
	static void LoadGame();
};
