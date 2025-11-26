#pragma once
#include "Component.h"

class InputComponent : public Component
{
	bool m_HasInput{ true }; // Has input.

public:
	// Get Has Input.
	bool HasInput() const { return m_HasInput; }
	// Set Has Input.
	void SetHasInput(bool hasInput) { m_HasInput = hasInput; }

	InputComponent() {}
};