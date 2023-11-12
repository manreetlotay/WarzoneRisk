#pragma once
#include <list>
#include <string>

using namespace std;


class ILoggable {
	public:
		ILoggable();
		~ILoggable();

		virtual string stringToLog();

};

// Note the Observer and Subject class were copied from the lecture slides
class Observer {
	public:
		virtual void Update(ILoggable*);
		~Observer();
	protected:
		Observer();
};

class Subject {
	public:
		Subject();
		~Subject();

		virtual void Attach(Observer* o);
		virtual void Detach(Observer* o);
		virtual void Notify(ILoggable*);
	private:
		list<Observer*>* _observers;
};

class LogObserver:public Observer 
{
	public:
		LogObserver();
		~LogObserver();
		void Update(ILoggable*);

};