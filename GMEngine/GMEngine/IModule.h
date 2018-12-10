#pragma once

class IModule
{
public:

	IModule() : active(true)
	{}

	virtual ~IModule()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		if (active == false)
			return active = Start();

		return true;
	}

	bool Disable()
	{
		if (active == true)
			return active = !CleanUp();

		return true;
	}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate(float deltaTime)
	{
		return true;
	}

	virtual bool Update(float deltaTime)
	{
		return true;
	}

	virtual bool PostUpdate(float deltaTime)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

private:
	bool active;
};