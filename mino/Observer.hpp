#pragma once

#include<vector>
using namespace std;

template<typename T> class Observer
{
public:
	Observer() {}
	virtual ~Observer<T>() {}
	virtual void target_called(T& source,array<int,4> &bingoLine )=0;
};

template<typename T> class Observable 
{
protected:
	vector< Observer<T>*> observers;
public:
	Observable<T>() {}
	virtual ~Observable<T>() {}
	void notify(T& source, array<int,4> &bingoLine)
	{
		vector<Observer<T>*>::iterator it;
		for(it=observers.begin(); it!=observers.end(); ++it)
			(*it)->target_called(source, bingoLine);
	}
	void subscribe(Observer<T>* f) {	observers.push_back(f);	}
	void unsubscribe(Observer<T>* f)
	{
		observers.erase(
			remove( observers.begin(), observers.end(), f), observers.end() );
	}
};

//#include"Observer.tpp"