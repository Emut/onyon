#ifndef CBUFFER_H
#define CBUFFER_H


template<class T>
class CBuffer{

public:
	CBuffer(int width, int heigth): m_width(width), m_heigth(heigth){
		m_itsBuffer = new T[width * heigth];
	}
	~CBuffer(){
		delete[] m_itsBuffer;
	}

	T* getBufferPointer(){
		return m_itsBuffer;
	}

	void Fill(const T fillThis){
		int totalSize = m_width * m_heigth;
		T* it = m_itsBuffer;
		for(int i = 0; i < totalSize; ++i){
			*it = fillThis;
			++it;
		}
	}

	void Print(){
		int totalSize = m_width * m_heigth;
		T* it = m_itsBuffer;
		for(int i = 0; i < totalSize; ++i){
			std::cout<<*it<<' ';
			++it;
			if(i%m_width == m_width-1)
				std::cout<<std::endl;
		}		
	}

	T& getElmRef(int x, int y){
		T& retVal = m_itsBuffer[y * m_width + x];
		return retVal;
	}

	int getWidth(){
		return m_width;
	}

	int getHeigth(){
		return m_heigth;
	}

private:
	CBuffer();	//disallow defc
	CBuffer(const CBuffer&);	//disallow cc
	T* m_itsBuffer;
	int m_width;
	int m_heigth;

};

#endif