#pragma once
#include <iosfwd>
#include <string>
#include <Eigen/Dense>
#include "Tester.h"
using namespace Eigen;

class Test: public Tester
{
public:
	Test(std::stringstream ss);
	~Test();
	void node();
	void cluster();
	void eig();
	void concat();
	void solveClusters();
	void testCalAlpha();
};
