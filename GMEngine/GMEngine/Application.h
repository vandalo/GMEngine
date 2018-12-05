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
			m_modules[hash] = new T();
		}
	}

	template<typename T>
	T* GetModule()
	{
		std::size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it != m_modules.end())
		{
			LOG("Try to get non-existing module");
			SDL_assert(true);
			return nullptr;
		}
		return static_cast<T*>(m_modules[hash]);
	}

private:
	std::unordered_map<std::size_t, IModule*> m_modules;
};
