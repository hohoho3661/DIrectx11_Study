#include "stdafx.h"
#include "Component.h"


Component::Component()
	:bActive(true)
{
}


Component::~Component()
{
}

void Component::EnableUpdate()
{
	if (bActive)
		Update();
}

void Component::EnableRender()
{
	if (bActive)
		Render();
}
