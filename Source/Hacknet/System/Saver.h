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

	static void Init();
	static void SaveNode(Node* _node);
	static Node* LoadNode(const std::string& _name);

private:

	static void InitGameDir();
	
};
