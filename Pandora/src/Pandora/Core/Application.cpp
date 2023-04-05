#include "Application.hpp"

#include <GL/glew.h>

namespace Pandora {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
		: m_Running(true)
	{
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
	}

	void Application::Run()
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}