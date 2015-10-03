// A C+GLUT implementation of the Creating a Window task at Rosetta Code// http://rosettacode.org/wiki/Creating_a_Window
#include &lt;stdlib.h&gt;
#include &lt;GL/glut.h&gt;

// This function is not strictly necessary to meet the requirements of the task.
void onKeyPress(unsigned char key, int x, int y)
{
	// If you have any cleanup or such, you need to use C's
	// onexit routine for registering cleanup callbacks.
	exit(0);

}

int main(int argc, char **argv)
{
	// Pulls out any command-line arguments that are specific to GLUT,
	// And leaves a command-line argument set without any of those arguments
	// when it returns.
	// (If you want a copy, take a copy first.)
	glutInit(&amp;argc, argv);

	// Tell GLUT we want to create a window.
	// It won't *actually* be created until we call glutMainLoop below.
	glutCreateWindow(&quot;Goodbye, World!&quot;);

	// Register a callback to handle key press events (so we can quit on
	// when someone hits a key)  This part is not necessary to meet the
	// requirements of the task.
	glutKeyboardFunc(&amp;onKeyPress);

	// Put the execution of the app in glut's hands. Most GUI environments
	// involve a message loop that communicate window events. GLUT handles
	// most of these with defaults, except for any we register callbacks
	// for. (Like the onKeyPress above.)
	glutMainLoop();

	return 0;

}


