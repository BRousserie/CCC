#include "CCCpch.h"
#include "WindowsInput.h"
#include "CCC/Application.h"

#include <GLFW/glfw3.h>

namespace CCC
{

	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		std::pair<double, double> pos;
		glfwGetCursorPos(window, &pos.first, &pos.second);

		return pos;
	}

	float WindowsInput::GetMouseXImpl()
	{
		return GetMousePosImpl().first;
	}
	
	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePosImpl().second;
	}
	
}

