#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void update(unsigned char note, unsigned char velocity) = 0;
};

#endif //_OBSERVER_H_
