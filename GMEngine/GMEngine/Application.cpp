#include "GMEngine.h"
#include "Application.h"
#include "IModule.h"
#include "CModuleWindow.h"
#include "CModuleAudio.h"

Application::Application()
{
	Add<CModuleWindow>();
	Add<CModuleAudio>();
}

Application::~Application()
{}

bool Application::Init()
{
	bool ret = true;

	for (auto& module : m_modules)
	{
		ret = module.second->Init();
	}

	for (auto& module : m_modules)
	{
		ret = module.second->Start();
	}

	return ret;
}

bool Application::Update()
{
	return true;
}

bool Application::CleanUp()
{
	bool ret = true;
	
	/*for (auto& module : m_modules)
	{
		delete module.second;
	}*/

	return ret;
}
