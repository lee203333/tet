#pragma once

template<typename T>
void Observable<T>::notify(T& source, int bingoLine ) 
{
	for(auto obj=observers.begin(); obj!=observers.end(); ++obj)
		obj->target_called(source, bingoLine);
}
template<typename T>
void Observable<T>::subscribe(Observer<T>* f) {	observers.push_back(f);	}//���

template<typename T>
void Observable<T>::unsubscribe(Observer<T>* f)  //����
{
	observers.erase(
		remove( observers.begin(), observers.end(), f), observers.end() );
}
