#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;

	int mouseX;
	int mouseY;
	bool mouseLBDown;
	bool mouseRBDown;

	bool copy;
	bool paste;
	bool del;

	bool scaleUp;
	bool scaleDown;

	bool rotateObjLeft;
	bool rotateObjRight;

	bool newObject;

	bool moveObjLeft;
	bool moveObjRight;
	bool moveObjUp;
	bool moveObjDown;
};
