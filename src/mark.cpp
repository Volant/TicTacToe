#include "util.h"
#include "mark.hpp"

#include <cmath>

void Mark::Draw (float xs, float ys, float xe, float ye) {
    glBegin (GL_LINES);
        glColor3f (1, 1, 1);
        glVertex2f (xs, ys);

        glColor3f(1, 1, 1);
        glVertex2f (xe, ye);
    glEnd();
}

void Mark::Draw (float x, float y, float r) {
	float N = 100;

	glBegin (GL_LINE_LOOP);
	for (int i = 0; i < N; i++) {
		float angle = 2.0 * 3.1415926 * float (i) / float (N);
		float dx = r * cosf (angle);
		float dy = r * sinf (angle);
		glVertex2f (x + dx, y + dy);
	}
	glEnd();
}
