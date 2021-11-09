#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Render(RenderContext& rc);
private:
	ModelRender stageRender;
	PhysicsStaticObject stagePSO;
};

