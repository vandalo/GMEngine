#pragma once

#include "IModule.h"
#include "CModuleWindow.h"

struct SDL_Window;
struct SDL_Surface;

class CModuleWindow : public IModule
{
public:

	CModuleWindow();
	virtual ~CModuleWindow();

	bool Init();
	bool CleanUp();

public:
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_screenSurface = nullptr;
};
