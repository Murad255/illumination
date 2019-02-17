/*
 * Smother.h
 *
 * Created: 10.02.2019 18:14:57
 *  Author: murad
 */ 


#ifndef SMOOTHER_H_
#define SMOOTHER_H_
#include <math.h>
#define value 100
#define PI 3.14
class Smoother 
	{
protected:
	float coint,pastCoint,nextCoint;
	float a;							//коэффициент для преобразования {0,2}в {pastCoint,nextCoint}
	int numCycle;
	virtual void Change()=0;
public:
	Smoother(float pastCoint,float nextCoint,int numCycle);
	Smoother(){};
	bool CointNum();
	void CointTime();
	void begin(float pastCoint,float nextCoint);
			
	};

/////////////////////////////////////////////
Smoother::Smoother(float pastCoint,float nextCoint,int numCycle=100){
	this->pastCoint=pastCoint;
	this->nextCoint=nextCoint;
	this->numCycle=numCycle;
	a=(nextCoint-pastCoint)/2;
	}
void Smoother::begin(float pastCoint,float nextCoint){
		this->pastCoint=pastCoint;
		this->nextCoint=nextCoint;
		//this->numCycle=numCycle;
		a=(nextCoint-pastCoint)/2;
	}
bool Smoother::CointNum(){
	//for (int i = 0;
	if(numCycle <= value) {
		coint = a * (-cos((float)(PI/100*numCycle))+(float)(1))+pastCoint;
		Change();
		++numCycle;
		return 0;
	}
	else return 1;
}



#endif /* SMOOTHER_H_ */