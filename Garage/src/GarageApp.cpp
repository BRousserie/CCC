#include <CCC.h>

class Garage : public CCC::Application
{
public:
	Garage()
	{
		PushOverlay(new CCC::ImGuiLayer());
	}

	~Garage()
	{
		
	}

};

CCC::Application* CCC::CreateApplication()
{
	return new Garage();
}