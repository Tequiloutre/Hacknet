#pragma once
#include <string>

enum PortType
{
	None,
	SSH,
	FTP
};

class Port
{
	PortType type = None;
	int number = 0;
	bool isOpened = false;

public:

	std::string GetType() const;
	int GetNumber() const { return number; }
	bool IsOpened() const { return isOpened; }
	
	Port(const PortType _type, const int _number)
	{
		type = _type;
		number = _number;
	}

	void Open() { isOpened = true; }
};
