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

	static std::shared_ptr<Application> getInstance()
	{
		static std::shared_ptr<Application> instance(new Application());
		return instance;
	}

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
	T* GetModule()
	{
		std::size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it == m_modules.end())
		{
			SDL_assert(it != m_modules.end());
			return nullptr;
		}
		return static_cast<T*>(m_modules[hash].get());
	}

private:
	std::unordered_map<std::size_t, std::unique_ptr<IModule>> m_modules;
};