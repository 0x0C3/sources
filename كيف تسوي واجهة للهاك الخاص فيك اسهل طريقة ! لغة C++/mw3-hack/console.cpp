#include "includes.h"
#include "console.h"
#include "addresses.h"

namespace console
{
	void commands()
	{
		std::string input;

	cmd:
		printf("MW3 HACK > ");
		std::getline(std::cin, input);
		printf("\n");

		if (input == "quit")
		{
			ExitProcess(0);
		}
		else if (input == "clear" || input == "cls")
		{
			system("cls");
			goto cmd;
		}
		else
		{
			addresses::Cbuf_AddText(0, input.data());
			goto cmd;
		}
	}

	DWORD WINAPI console(LPVOID lp)
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());

		SetConsoleTitleA("MW3 HACK"); // console title

		FILE* file;
		freopen_s(&file, "CONIN$", "r", stdin);
		freopen_s(&file, "CONOUT$", "w", stdout);
		freopen_s(&file, "CONOUT$", "w", stderr);

		commands();

		FreeLibraryAndExitThread((HMODULE)lp, 0);
	}
}