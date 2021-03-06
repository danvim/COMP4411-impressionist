#include "CircleBrush.h"
//
// CircleBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <ostream>
#include <iostream>

extern float frand();
extern double degToRad(double);

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}
void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	if (source.x > pDoc->m_nPaintWidth || source.y < 0)
	{
		return;
	}

	int size = pDoc->getSize();

	SetColor(source);
	DrawCircle(target, size);
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
}

void CircleBrush::DrawCircle(const Point target, int size)
{
	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++)
	{
		double rad = degToRad(i);
		glVertex2f(
			static_cast<GLfloat>(target.x) + cos(rad)*size / 2.f,
			static_cast<GLfloat>(target.y) + sin(rad)*size / 2.f
		);
	}

	glEnd();
}