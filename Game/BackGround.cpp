#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	stageRender.Init("Assets/modelData/Stage1/stage1.tkm");
	stagePSO.CreateFromModel(stageRender.GetModel(), stageRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	stageRender.Draw(rc);
}
