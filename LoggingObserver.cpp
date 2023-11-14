#include "LoggingObserver.h"
#include <fstream>


ILoggable::ILoggable() {}
ILoggable::~ILoggable() {}

string ILoggable::stringToLog()
{
	return string();
}



Observer::Observer() {}
void Observer::Update(ILoggable*)
{
}
Observer::~Observer() {}

Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {}

void Subject::Attach(Observer* o) {
	_observers->push_back(o);
}
void Subject::Detach(Observer* o) {
	_observers->remove(o);
}
void Subject::Notify(ILoggable* l) {
	for (Observer* ob : *_observers){
		ob->Update(l);
	}
}

LogObserver::LogObserver() {
}
LogObserver::~LogObserver() {}
void LogObserver::Update(ILoggable* l) {
	ofstream file;
	file.open("gamelog.txt",ios::app);
	if (file.is_open()) {
		file<<l->stringToLog()<<endl;
	}
	file.close();
}