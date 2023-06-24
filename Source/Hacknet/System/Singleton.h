#pragma once

template<class T>
class Singleton
{
	inline static T* instance = nullptr;
	
public:

	Singleton();

	static T* GetInstance() { return instance; }
};

template <class T>
Singleton<T>::Singleton()
{
	if (instance)
	{
		delete this;
		return;
	}

	instance = static_cast<T*>(this);
}
