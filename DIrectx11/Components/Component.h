#pragma once
class Component
{
public:
	Component();
	virtual ~Component();


	void EnableUpdate();
	void EnableRender();

	void SetActive(bool b) { bActive = b; }

	void ShowInspactor()
	{
		ImGui::BeginChild("Insfactor");
		SetInspactor();
		ImGui::EndChild();
	}
protected:
	virtual void Update() =0;
	virtual void Render() =0;

	bool bActive;

	virtual void SetInspactor() = 0;
};


