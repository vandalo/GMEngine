#include "GMEngine.h"
#include "Application.h"
#include "CModuleWindow.h"
#include "SDL/include/SDL.h"

CModuleWindow::CModuleWindow()
{
}

CModuleWindow::~CModuleWindow()
{
}

bool CModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (m_window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			m_screenSurface = SDL_GetWindowSurface(m_window);
		}
	}

	return ret;
}

bool CModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
	}

	SDL_Quit();
	return true;
}

