#include "Camera.h"

Camera::Camera()
{

	m_viewDimensions = { 0, 0, 0, 0 }; // Initialize the view dimensions to zero

	//functional (Taken from Game.cpp)
	m_movespeed = 30.0f;
	m_camRotRate = 1.5f;

	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

}

// Destructor
Camera::~Camera()
{

}

void Camera::Initialise(HWND window)
{

	m_window = window; // Store the window handle

}

void Camera::InputHandling(InputCommands m_input, float deltaTime)
{
	//camera motion is on a plane, so kill the 7 component of the look direction
	DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	m_deltaX = m_input.mouseX - middleScreenX;
	m_deltaY = m_input.mouseY - middleScreenY;

		//process input and update rotation
		if (m_input.rotRight)
		{
			m_camOrientation.y += m_camRotRate;
		}
		if (m_input.rotLeft)
		{
			m_camOrientation.y -= m_camRotRate;
		}
		if (m_input.rotUp)
		{
			m_camOrientation.x += m_camRotRate;
		}
		if (m_input.rotDown)
		{
			m_camOrientation.x -= m_camRotRate;
		}
	

	// Calculating the camera look direction
	m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.y = sin((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180) * cos((m_camOrientation.x) * 3.1415 / 180);
	
	m_camLookDirection.Normalize();

	// Calculating the camera right direction
	m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);

	//process input and update movement
	if (m_input.forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed * deltaTime;
	}
	if (m_input.back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed * deltaTime;
	}
	if (m_input.right)
	{
		m_camPosition += m_camRight * m_movespeed * deltaTime;
	}
	if (m_input.left)
	{
		m_camPosition -= m_camRight * m_movespeed * deltaTime;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection * deltaTime;
}

// Update for Camera Class
void Camera::Update(float deltaTime)
{
	// Clamp the camera orientation
	m_camOrientation.x = std::min(m_camOrientation.x, 89.f);
	m_camOrientation.x = std::max(m_camOrientation.x, -89.f);

	// update the camera position and lookat point
	Camera::InputHandling(m_input, deltaTime);

	// Check if mouse is focused for first person movement
	if (m_input.mouseFocus)
	{
		middleScreenX = m_viewDimensions.right / 2; // Calculate the middle of the screen (Width)
		middleScreenY = m_viewDimensions.bottom / 2; // Calculate the middle of the screen (Height)

		screenCenter = { middleScreenX, middleScreenY }; // Set the screen center to the middle of the screen

		
		SetCursorPos(middleScreenX, middleScreenY); // Set the cursor position to the middle of the screen
		ClientToScreen(m_window, &screenCenter); // Convert the window coordinations to screen coordinates
		ShowCursor(false); // Hide the cursor
	}
	else
	{
		ShowCursor(true); // Show the cursor
	}

}

void Camera::Tick(InputCommands* input)
{
	m_input = *input;
}

// Get the camera position
DirectX::SimpleMath::Vector3 Camera::GetCameraPos()
{
	return m_camPosition;
}

// Get the camera lookat point
DirectX::SimpleMath::Matrix Camera::GetLookAt()
{
	return DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
}

void Camera::UpdateViewRect(RECT viewRectIn)
{
	m_viewDimensions = viewRectIn; // Update the view dimensions
}

// Camera Focuses in on object after being clicked
void Camera::LookAtObject(DirectX::SimpleMath::Vector3 objectPos)
{
	float distance = 5;
	
	m_camLookAt = objectPos; // Set the camera lookat point to the object's position

	m_camPosition = m_camLookAt - (m_camLookDirection * distance);
}
