#pragma once

#include "pch.h"
#include "InputCommands.h"
#include <cstdint>

class Camera
{
private:
	RECT m_viewDimensions; // window dimensions

	//camera (taken from the game.h file)
	DirectX::SimpleMath::Vector3 m_camPosition; // camera position
	DirectX::SimpleMath::Vector3 m_camOrientation; // camera orientation
	DirectX::SimpleMath::Vector3 m_camLookAt; // camera look at
	DirectX::SimpleMath::Vector3 m_camLookDirection; // camera look direction
	DirectX::SimpleMath::Vector3 m_camRight; // camera right vector
	float m_camRotRate; // camera rotation rate
	float m_movespeed; // camera movement speed
	float m_mouseSens; // mouse sensitivity
	float m_deltaX; 
	float m_deltaY; 
	long middleScreenX;
	long middleScreenY;

	
public:
	Camera(); // Constructor
	~Camera(); // Destructor

	void Initialise(HWND hwnd);
	void InputHandling(InputCommands m_input, float deltaTime);
	void Tick(InputCommands* input);
	void Update(float deltaTime);
	void UpdateViewRect(RECT viewRectIn);
	void LookAtObject(DirectX::SimpleMath::Vector3 objectPos);

	DirectX::SimpleMath::Vector3 GetCameraPos();
	DirectX::SimpleMath::Matrix GetLookAt();

	HWND m_window;
	POINT screenCenter;

	InputCommands m_input;

};

