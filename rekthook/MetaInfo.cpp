

#include "MetaInfo.h"
#include "Utilities.h"

void PrintMetaHeader()
{
	printf("                                  LO");
	Utilities::SetConsoleColor(FOREGROUND_INTENSE_GREEN);
	printf("GIC\n");
	Utilities::SetConsoleColor(FOREGROUND_WHITE);
	Utilities::Log("Build %s", __DATE__);
	Utilities::Log("Setting Up Rekthook for %s", Rekthook_META_GAME);
}