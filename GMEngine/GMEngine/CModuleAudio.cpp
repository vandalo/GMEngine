#include "GMEngine.h"

#include "CModuleAudio.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

CModuleAudio::CModuleAudio()
	: IModule()
	, m_music(nullptr) {}


CModuleAudio::~CModuleAudio() {}

bool CModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool CModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (m_music != nullptr)
	{
		Mix_FreeMusic(m_music);
	}

	for (std::vector<Mix_Chunk*>::iterator it = m_fx.begin(); it != m_fx.end(); ++it)
		Mix_FreeChunk(*it);

	m_fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

bool CModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (m_music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(m_music);
	}

	m_music = Mix_LoadMUS(path);

	if (m_music == nullptr)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(m_music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(m_music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

bool CModuleAudio::PauseMusic(float fade_time)
{
	bool ret = true;

	if (m_music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(m_music);
	}

	return true;
}

unsigned int CModuleAudio::LoadFx(const char* path)
{
	unsigned int ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		m_fx.push_back(chunk);
		ret = m_fx.size() - 1;
	}

	return ret;
}

bool CModuleAudio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (id < m_fx.size())
	{
		Mix_PlayChannel(id, m_fx[id], repeat);
		ret = true;
	}

	return ret;
}

bool CModuleAudio::PauseFx(unsigned int id)
{
	bool ret = false;

	if (id < m_fx.size())
	{
		Mix_Pause(id);
		ret = true;
	}

	return ret;
}

void CModuleAudio::MusicFadeOut(float fade_time) {
	if (m_music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}
	}
}