#include <stdio.h>
#include <stdlib.h>					// malloc(), free()
#include "Painter.h"

void DrawArrow(GLfloat angle)
{
	glPushMatrix(); // Save world coordinate system.

        glColor3f(0.0f, 0.0f, 0.0f); // sets color to black.

		glRotatef(angle, 0.0, 0.0, 1.0);

		glTranslatef(0.0, 1.0, 0.0);

		glDisable(GL_LIGHTING);	// Just use colours.

		glBegin(GL_TRIANGLES);
			glVertex2f(0.0f, 0.75f); // point
			glVertex2f(-0.5f, 0.25f); // left
			glVertex2f(0.5f, 0.25f); // right
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(-0.25f, 0.25f); // upper left
			glVertex2f(-0.25f, -0.5f); // lower left
			glVertex2f(0.25f, -0.5f); // lower right
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(0.25f, -0.5f); // lower right
			glVertex2f(0.25f, 0.25f); // upper right
			glVertex2f(-0.25f, 0.25f); // upper left
		glEnd();

	glPopMatrix();	// Restore world coordinate system.
}