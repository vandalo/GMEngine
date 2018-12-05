#include "GMEngine.h"
#include "Application.h"
#include "IModule.h"
#include "CModuleWindow.h"

Application::Application()
{
	Add<CModuleWindow>();
}

Application::~Application()
{}

bool Application::Init()
{
	bool ret = true;

	for (auto& module : m_modules)
	{
		ret = module.second.get()->Init();
	}

	for (auto& module : m_modules)
	{
		ret = module.second.get()->Start();
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

	for (auto& module : m_modules)
	{
		ret = module.second.get()->CleanUp();
	}

	return ret;
}
