#pragma once

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/KeyCodes.hpp"
#include "Pandora/Core/MouseCodes.hpp"

namespace Pandora {

	enum class InputMode
	{
		Normal, Capture, Hidden
	};

    class Input
    {
    public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static void SetInputMode(InputMode inputMode) { s_Instance->SetInputModeImpl(inputMode); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual void SetInputModeImpl(InputMode inputMode) = 0;
	private:
		static Scope<Input> s_Instance;
    };
}