#include "stdafx.h"
#include <Application.h>

int main()
{
	Application* app = new Application();
	if (app != nullptr)
	{
		printf("app memory reference: %x\n", (unsigned int)app);
	}

	while(1){}

	return 0;
}

