/*
 * SignalCurve.cpp
 *
 *  Created on: 20 juil. 2016
 *      Author: ludovic
 */

#include "SignalCurve.h"

SignalCurve::SignalCurve() {
	// Create a linear curve:
	SignalCurve(0);
}

SignalCurve::SignalCurve(unsigned int curveType) {
	CurvePoint *tmpPoint;

	unsigned int xValues[16]={ 8, 16, 24, 32, 40, 48, 56, 64, 72, 80 ,88, 96, 104, 112, 120, 127};
	unsigned int exp[16]={ 1, 2, 5, 8, 13, 18, 25, 32, 41, 50, 61, 72, 84, 98, 112,	127};
	unsigned int log[16]={ 1, 2, 5, 8, 13, 18, 25, 32, 41, 50, 61, 72, 84, 98, 112,	127};
	unsigned int sCurve[16]={ 2, 3, 5, 10, 20, 40, 75, 95, 107, 113, 118, 121, 123, 125, 126, 127};

	// Create a list of points with a specified count :
	for (unsigned int i=0; i<16; i++){
		tmpPoint=new CurvePoint;
		tmpPoint->xValue=xValues[i];
		tmpPoint->yValue=xValues[i];
		m_curvePoints.push_back(tmpPoint);
	}

	if (curveType==1){
		// Exponential curve :
		for (unsigned int i=0; i<16; i++){
			tmpPoint=m_curvePoints[i];
			tmpPoint->yValue=exp[i];
		}

	}else if (curveType==2){
		// Log curve :
		for (unsigned int i=0; i<16; i++){
			tmpPoint=m_curvePoints[i];
			tmpPoint->yValue=log[i];
		}

	}else if (curveType==3){
		// S curve :
		for (unsigned int i=0; i<16; i++){
			tmpPoint=m_curvePoints[i];
			tmpPoint->yValue=sCurve[i];
		}

	}

}


SignalCurve::~SignalCurve() {
	m_curvePoints.clear();
}

void SignalCurve::setValueAt(unsigned int x, unsigned int value){

	CurvePoint *tmpPt;

	for (unsigned int i=0; i<m_curvePoints.size(); i++){
		tmpPt=m_curvePoints[i];
		if (tmpPt->xValue==x){
			tmpPt->yValue=value;
			return;
		}
	}
}

unsigned int SignalCurve::getValueForX(unsigned int x){
	// Calculate the interpolated value for x from current curve :
	CurvePoint *upPt, *lowPt;
	unsigned int i=0;
	float coeff;

	// Search for the segment that contains our value :
	upPt=m_curvePoints[i];
	do{
		if (upPt->xValue==x){
				return upPt->yValue;
		}
		i++;
		upPt=m_curvePoints[i];
	}while (x<upPt->xValue);

	// Now we got our "upper" segment point, calculate the slope and get our output point :
	lowPt=m_curvePoints[i-1];

	return (x-lowPt->xValue) * ( (upPt->yValue - lowPt->yValue) / (upPt->xValue - lowPt->xValue) ) + lowPt->yValue;

}

const std::vector<CurvePoint*>& SignalCurve::getAllCurvePoints(){
	return m_curvePoints;
}
