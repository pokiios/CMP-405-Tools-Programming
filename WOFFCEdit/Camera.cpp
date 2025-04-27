#include "Camera.h"

Camera::Camera()
{
	m_viewDimensions = { 0, 0, 0, 0 }; // Initialize the view dimensions

	//functional (Taken from Game.cpp)
	m_movespeed = 50.0f;
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

void Camera::InputHandling(InputCommands m_input, float deltaTime)
{
	//camera motion is on a plane, so kill the 7 component of the look direction
	DirectX::SimpleMath::Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	// https://asliceofrendering.com/camera/2019/11/30/ArcballCamera/
	//Arcball Camera
	// Rotate camera around pivot is mouse down
	if (m_input.mouseRBDown)
	{
		// Calculate Rotation Angles
		float deltaAngleX = (2 * 3.14159 / m_viewDimensions.right);
		float deltaAngleY = (3.14159 / m_viewDimensions.bottom);

		// Calculate the change in mouse position
		float deltaX = (m_input.mouseX - m_mouseLastXPos);
		float deltaY = (m_input.mouseY - m_mouseLastYPos);

		// Update camera orientation based on mouse movement
		m_camOrientation.y += deltaX * m_mouseSens;
		m_camOrientation.x -= deltaY * m_mouseSens;
	}


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

	// Quick fix Clamp the camera orientation
	if (m_camOrientation.x > 89.0f)
	{
		m_camOrientation.x = 89.0f;
	}
	if (m_camOrientation.x < -89.0f)
	{
		m_camOrientation.x = -89.0f;
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
	////https://asliceofrendering.com/camera/2019/11/30/ArcballCamera/
	m_mouseLastXPos = m_input.mouseX;
	m_mouseLastYPos = m_input.mouseY;

	// update the camera position and lookat point
	Camera::InputHandling(m_input, deltaTime);

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
