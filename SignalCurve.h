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

	enum CurveType{
		Curve_Linear,
		Curve_Exp,
		Curve_Log,
		Curve_SLine,
		Curve_Max
	};

	SignalCurve();
	SignalCurve(unsigned int curveType);
	virtual ~SignalCurve();

	void setValueAt(unsigned int x, unsigned int value);
	unsigned int getValueForX(unsigned int x);
	std::vector<CurvePoint*> *getAllCurvePoints();
	unsigned int getCurveType() const;
	void setCurveType(unsigned int curveType);

private:
	std::vector<CurvePoint*> *m_curvePoints;
	unsigned int m_curveType;
};

#endif /* SIGNALCURVE_H_ */
