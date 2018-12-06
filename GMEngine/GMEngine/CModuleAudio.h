#pragma once

#include <vector>

#include "IModule.h"

struct _Mix_Music;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class CModuleAudio : public IModule
{
public:
	CModuleAudio();
	~CModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time);
	bool PauseMusic(float fade_time);

	unsigned int LoadFx(const char* path);

	bool PlayFx(unsigned int fx, int repeat);
	bool PauseFx(unsigned int fx);
	void MusicFadeOut(float fade_time);

private:

	Mix_Music*	m_music = nullptr;
	std::vector<Mix_Chunk*>	m_fx;
};

