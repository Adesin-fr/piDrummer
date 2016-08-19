/*
 * SignalCurve.cpp
 *
 *  Created on: 20 juil. 2016
 *      Author: ludovic
 */

#include "SignalCurve.h"


using namespace std;



void FillList(unsigned int curveType, std::vector<CurvePoint*> *m_curvePoints);

SignalCurve::SignalCurve() {
	// Init the vector list :
	m_curvePoints = 0;
	m_stdCurvePoints=new vector<CurvePoint*>;
	m_customCurvePoints=new vector<CurvePoint*>;
	m_curveType=SignalCurve::Curve_Linear;

	// Create a linear curve:
	this->setCurveType(SignalCurve::Curve_Linear);
}

SignalCurve::SignalCurve(unsigned int curveType) {
	// Init the vector list :
	m_curvePoints = 0;
	m_stdCurvePoints=new vector<CurvePoint*>;
	m_customCurvePoints=new vector<CurvePoint*>;
	m_curveType=curveType;

	// Create a linear curve:
	this->setCurveType(SignalCurve::Curve_Linear);

}


SignalCurve::~SignalCurve() {
	m_curvePoints->clear();
}

void SignalCurve::setValueAt(unsigned int x, unsigned int value){

	(*m_curvePoints)[x]->yValue=value;
}


unsigned int SignalCurve::getValueForX(unsigned int x){
	// Calculate the interpolated value for x from current curve :
	CurvePoint *upPt, *lowPt;
	unsigned int i=0;

	// Search for the segment that contains our value :

	upPt=(*m_curvePoints)[i];
	do{
		if (upPt->xValue==x){
				return upPt->yValue;
		}
		i++;
		upPt=(*m_curvePoints)[i];
	}while (x > (upPt->xValue));

	// Now we got our "upper" segment point, calculate the slope and get our output point :
	lowPt=(*m_curvePoints)[i-1];

	return (x-lowPt->xValue) * ( (upPt->yValue - lowPt->yValue) / (upPt->xValue - lowPt->xValue) ) + lowPt->yValue;

}

std::vector<CurvePoint*> *SignalCurve::getAllCurvePoints(){
	return m_curvePoints;
}

unsigned int SignalCurve::getCurveType() const {
	return m_curveType;
}

void SignalCurve::setCurveType(unsigned int curveType) {
	if (curveType == SignalCurve::Curve_Custom){
		if (m_customCurvePoints->size()==0){
			// If the customCurvePoints list is empty, then fill it first with a linear curve type :
			FillList(SignalCurve::Curve_Linear, m_customCurvePoints);
		}
		m_curvePoints=m_customCurvePoints;
	}else{
		FillList(curveType, m_stdCurvePoints);
		m_curvePoints=m_stdCurvePoints;
	}

	m_curveType = curveType;

}

void FillList(unsigned int curveType, std::vector<CurvePoint*> *m_curvePoints){

	const unsigned int NBPOINTS=17;
	CurvePoint *tmpPoint;

	unsigned int xValues[NBPOINTS]={0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80 ,88, 96, 104, 112, 120, 127};
	unsigned int exp[NBPOINTS]={0, 15, 29, 43, 55, 66, 77, 86, 95, 102, 109, 114, 119, 122, 125, 126,127};
	unsigned int log[NBPOINTS]={0, 1, 2, 5, 8, 13, 18, 25, 32, 41, 50, 61, 72, 84, 98, 112,	127};
	unsigned int sCurve[NBPOINTS]={0, 2, 3, 5, 10, 20, 40, 75, 95, 107, 113, 118, 121, 123, 125, 126, 127};
	unsigned int maxedOut[NBPOINTS]={127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,127, 127, 127, 127, 127,	127};

	m_curvePoints->clear();

	// Create a list of points with a specified count :
	for (unsigned int i=0; i<NBPOINTS; i++){
		tmpPoint=new CurvePoint();
		tmpPoint->xValue=xValues[i];
		tmpPoint->yValue=xValues[i];
		m_curvePoints->push_back(tmpPoint);
	}

	if (curveType==SignalCurve::Curve_Exp){
		// Exponential curve :
		for (unsigned int i=0; i<NBPOINTS; i++){
			tmpPoint=(*m_curvePoints)[i];
			tmpPoint->yValue=exp[i];
		}

	}else if (curveType==SignalCurve::Curve_Log){
		// Log curve :
		for (unsigned int i=0; i<NBPOINTS; i++){
			tmpPoint=(*m_curvePoints)[i];
			tmpPoint->yValue=log[i];
		}

	}else if (curveType==SignalCurve::Curve_SLine){
		// S curve :
		for (unsigned int i=0; i<NBPOINTS; i++){
			tmpPoint=(*m_curvePoints)[i];
			tmpPoint->yValue=sCurve[i];
		}

	}else if (curveType==SignalCurve::Curve_Max){
		// maxed out :
		for (unsigned int i=0; i<NBPOINTS; i++){
			tmpPoint=(*m_curvePoints)[i];
			tmpPoint->yValue=maxedOut[i];
		}

	}
}
