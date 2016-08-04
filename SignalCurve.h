/*
 * SignalCurve.h
 *
 *  Created on: 20 juil. 2016
 *      Author: ludovic
 */

#ifndef SIGNALCURVE_H_
#define SIGNALCURVE_H_

#include <vector>

typedef struct {
	unsigned int xValue;
	unsigned int yValue;
} CurvePoint;

class SignalCurve {
public:
	SignalCurve();
	SignalCurve(unsigned int curveType);
	virtual ~SignalCurve();

	void setValueAt(unsigned int x, unsigned int value);
	unsigned int getValueForX(unsigned int x);
	std::vector<CurvePoint*> *getAllCurvePoints();

private:
	std::vector<CurvePoint*> *m_curvePoints;
};

#endif /* SIGNALCURVE_H_ */
