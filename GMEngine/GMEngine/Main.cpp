#include "GMEngine.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "Application.h"
#include "CModuleAudio.h"

std::unique_ptr<Application> app;

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
			app = std::make_unique<Application>();
			state = MAIN_START;
			break;
		case MAIN_START:
			if (app->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				//app.get().GetModule<CModuleAudio>()->PlayMusic("4WinningRun.ogg", 0);
				CModuleAudio* ma = app.get()->GetModule<CModuleAudio>();
				ma->PlayMusic("music/4WinningRun.ogg", 0.f);
				state = MAIN_UPDATE;
			}
			break;
		case MAIN_UPDATE:
			if (app->Update() == false)
			{
				state = MAIN_FINISH;
			}
			break;
		case MAIN_FINISH:
			state = MAIN_EXIT;
			break;
		case MAIN_EXIT:
			break;
		default:
			LOG("Main state not controled");
			SDL_assert(true);
		}
	}
	LOG("Program closed");
	return 0;
}
