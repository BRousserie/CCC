#pragma once

#include "CCC/Layer.h"

#include "CCC/Events/MouseEvent.h"
#include "CCC/Events/KeyEvent.h"
#include "CCC/Events/ApplicationEvent.h"

namespace CCC
{
	class CCC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
						
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
		float m_Time = 0.0f;
	};
}
