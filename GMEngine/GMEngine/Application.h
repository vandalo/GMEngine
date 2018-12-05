#pragma once

#include <unordered_map>
#include <memory>

#include "IModule.h"

class Application
{
public:
	Application();
	~Application();
	bool Init();
	bool Update();
	bool CleanUp();

	template<typename T>
	void Add()
	{
		std::size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it == m_modules.end())
		{
			m_modules[hash] = std::make_unique<T>();
		}
	}

	template<typename T>
	IModule& GetModule()
	{
		std:size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it == m_modules.end())
		{
			return m_modules[hash];
		}
		LOG("Try to get non-existing module");
		SDL_assert(true);
	}

private:
	std::unordered_map<std::size_t, std::unique_ptr<IModule>> m_modules;
};
