#include <CCC.h>

class Garage : public CCC::Application
{
public:
	Garage()
	{
		
	}

	~Garage()
	{
		
	}

};

CCC::Application* CCC::CreateApplication()
{
	return new Garage();
}