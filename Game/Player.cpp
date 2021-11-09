#include "stdafx.h"
#include "Player.h"

Vector3 gPlayerPosition;

Player::Player()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);

	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);

	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);

	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	playerRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
	
	playerRender.SetPosition(playerPosition);

	playerController.Init(playerRad, playerHeight, playerPosition);
}

Player::~Player()
{

}

void Player::Move()
{
	playerMoveSpeed.x = 0.0f;
	playerMoveSpeed.z = 0.0f;

	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	playerForward = g_camera3D->GetForward();
	playerRight = g_camera3D->GetRight();

	playerForward.y = 0.0f;
	playerRight.y = 0.0f;

	playerForward.Normalize();
	playerRight.Normalize();

	playerRight *= stickL.x * 2000.0f;
	playerForward *= stickL.y * 2000.0f;

	if (g_pad[0]->IsTrigger(enButtonA) && playerJumpCount == 0)
	{
		playerJumpCount=1;
		playerMoveSpeed.y += 700.0f;
	}

	if (playerJumpCount == 1 && playerPosition.y<=25.0f)
		playerJumpCount = 0;

	playerMoveSpeed += playerRight + playerForward;
	playerMoveSpeed.y -= 30.0f;

	if (playerPosition.y < 0.0f)
		playerMoveSpeed.y = 0.0f;
	playerPosition = playerController.Execute(playerMoveSpeed, 1.0f / 60.0f);
	playerRender.SetPosition(playerPosition);
}

void Player::Rotation()
{
	if (fabsf(playerMoveSpeed.x) < 0.1f && fabsf(playerMoveSpeed.z) < 0.1f)
		return;

	playerAngle = atan2(-playerMoveSpeed.x, playerMoveSpeed.z);

	playerRotation.SetRotationY(-playerAngle);

	playerRender.SetRotation(playerRotation);
}

void Player::ManageState()
{

}

void Player::PlayAnimation()
{

}

void Player::Update()
{
	Move();
	Rotation();

	gPlayerPosition = playerPosition;

	playerRender.Update();
}

void Player::Render(RenderContext& rc)
{
	playerRender.Draw(rc);
}