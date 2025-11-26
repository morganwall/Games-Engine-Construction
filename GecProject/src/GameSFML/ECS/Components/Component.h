#pragma once

class Component // Base component class.
{
public:
	// ImGui elements for the component.
	virtual void OnGui() {}

	virtual ~Component() {}
};