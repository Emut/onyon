#ifndef CLINEARITER_H
#define CLINEARITER_H
//An iterator starting at a given value and increases one by one
template <class T>
class CLinearIter
{
	T m_i;

public:
	CLinearIter(T i) : m_i(i) {}
	void operator++()
	{
		++m_i;
	}
	CLinearIter<T> &operator++(int)
	{
		++m_i;
		return *this;
	}
	bool operator!=(const CLinearIter<T> &comp)
	{
		return m_i != comp.m_i;
	}
	T &operator*()
	{
		return m_i;
	}
	CLinearIter<T> &operator=(const CLinearIter<T> &copyFrom)
	{
		m_i = copyFrom.m_i;
		return *this;
	}
	CLinearIter(const CLinearIter<T> &copyFrom)
	{
		m_i = copyFrom.m_i;
	}
};
#endif