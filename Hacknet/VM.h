#pragma once

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "Process.h"

class VM
{
	inline static std::string name = "Hacknet";
	inline static std::string version = "0.1";
	inline static bool isOn = false;
	inline static bool isBusy = false;

	inline static std::vector<Process*> commands;

public:

	static std::string GetName() { return name; }
	static std::string GetVersion() { return version; }
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

	static void Start();
	static void Update();
	static void Exit();

private:
	static void InitCommands();
};
