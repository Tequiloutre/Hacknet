#include "System/VM.h"
#include "Network/WAN.h"
#include "System/Saver.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(205);
	
	srand(static_cast<unsigned int>(time(nullptr)));  // NOLINT(cert-msc51-cpp)

	static VM vm;
	static WAN wan;
	static Saver saver;

	Saver::Init();
	VM::GetInstance()->StartUp();


	while (VM::GetInstance()->IsOn())
	{
		VM::GetInstance()->Update();
	}

    return 0;
}
