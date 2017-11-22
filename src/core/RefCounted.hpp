#pragma once

#include "debug.hpp"

class RefCounted
{
public:

	void AddRef();
	void Release();

protected:

	RefCounted() = default;
	virtual ~RefCounted() = default;

private:

	unsigned int mRefCount = 0;

};

inline void RefCounted::AddRef()
{
	mRefCount++;
}

inline void RefCounted::Release()
{
	ASSERT(mRefCount > 0);
	
	mRefCount--;
	
	if(mRefCount > 0) {
		return;
	}

	delete this;
}

template< typename T>
class ref
{
	public:
		ref(T* pT = nullptr);
		ref(const ref<T>& rhs);		

		template<typename RhsType>
		ref(ref<RhsType>&& rhs);

		template<typename RhsType>
		ref(const ref<RhsType>& rhs);

		~ref();
		T* operator->() const;
		T* get();


		ref& operator=(const ref& rhs);
		ref& operator=(ref&& rhs);

	private:

		T* mpT;
};

template<typename T, typename ...Params>
ref<T> make_ref(Params&&... params) {
	return ref<T>(
		new T(std::forward<Params>(params)...));
}


template<typename T >
ref<T>::ref(T* pT)
	: mpT(pT)
{
	if(nullptr != mpT) {
		mpT->AddRef();
	}
}

template<typename T >
ref<T>::ref(const ref<T>& rhs)
	: mpT(rhs.mpT)
{
	if(nullptr != mpT) {
		mpT->AddRef();
	}
}

template<typename T >
template<typename RhsType>
ref<T>::ref(ref<RhsType>&& rhs)
	: mpT(rhs.mpT)
{
	rhs.mpT = nullptr;
}

template<typename T >
template<typename RhsType>
ref<T>::ref(const ref<RhsType>& rhs)
	: mpT(rhs.mpT)
{
	if(nullptr != mpT) {
		mpT->AddRef();
	}
}

template<typename T >
ref<T>::~ref()
{
	if(nullptr != mpT)
	{
		mpT->Release();
	}
}

template<typename T>
T* ref<T>::operator->() const
{
	ASSERT(nullptr != mpT);
	return mpT;
}

template<typename T>
T* ref<T>::get()
{
	return mpT;
}

template<typename T>
ref<T>& ref<T>::operator=(const ref& rhs)
{
	if(nullptr != mpT)
	{
		mpT->Release();
	}

	mpT = rhs.mpT;

	if(nullptr != mpT)
	{
		mpT->AddRef();
	}

	return *this;
}

template<typename T>
ref<T>& ref<T>::operator=(ref&& rhs)
{
	if(nullptr != mpT)
	{
		mpT->Release();
	}

	mpT = rhs.mpT;
	rhs.mpT = nullptr;

	return *this;

}