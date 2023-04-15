#pragma once

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/Layer.hpp"

namespace Pandora {

    class ImGuiLayer : public Layer
    {
    public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
    };
}