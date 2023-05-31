#include "Port.h"

std::string Port::GetType() const
{
	switch (type)
	{
		case None: return "None";
		case SSH: return "SSH";
		case FTP: return "FTP";
	}
	return "None";
}
