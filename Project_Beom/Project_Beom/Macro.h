#pragma once

template<typename T>
inline void SAFE_DELETE(T& value)
{
	if (nullptr != value)
	{
		delete value;
		value = nullptr;
	}
}

template<typename T>
inline void SAFE_DELETE_ARRAY(T& value)
{
	if (nullptr != value)
	{
		delete[] value;
		value = nullptr;
	}
}

template<typename T>
inline void SAFE_RELEASE(T& value)
{
	if (nullptr != value)
	{
		value->Release();
		delete value;
		value = nullptr;
	}
}

template<class T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}

protected:
	virtual bool Initialize() = 0;
	virtual void Release() = 0;

public:
	static T* GetInstance()
	{
		if (nullptr == m_Instance)
		{
			m_Instance = new T;
			m_Instance->Initialize();
		}
		return m_Instance;
	}
	static void DestroyInstance() 
	{ 
		if (nullptr != m_Instance)
		{
			SAFE_RELEASE(m_Instance);
		}
	}

private:
	static T* m_Instance;
};

template<class T>
T* Singleton<T>::m_Instance = nullptr;

#define GETMGR(Class) Class::GetInstance()
#define DESTROYMGR(Class) Class::DestroyInstance()