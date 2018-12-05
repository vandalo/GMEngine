#pragma once

template<typename T>
class CHash
{
public:
	static std::size_t Hash()
	{
		static int dummy =  0;
		return reinterpret_cast<std::size_t>(&dummy);
	}
};