#pragma once

#include "Pandora/Core/Input.hpp"

namespace Pandora {

    class LinuxInput : public Input
    {
    protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
    };
}