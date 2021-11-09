#pragma once

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Move();
	void Rotation();
	void PlayAnimation();
	void ManageState();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& position)
	{
		playerPosition = position;
	}
	const Vector3& GetPosition() const
	{
		return playerPosition;
	}

private:
	ModelRender playerRender;
	Quaternion playerRotation;
	Vector3 playerMoveSpeed ;
	Vector3 stickL;
	float playerHeight = 50.0f;
	float playerRad =  25.0f;
	CharacterController playerController;
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Walk,
		enAnimationClip_Num
	};
	AnimationClip animationClips[enAnimationClip_Num];
	int playerMoveState = 0;
	Vector3 playerRight;
	Vector3 playerForward;
	float playerAngle;
	int playerJumpCount = 0;
	Vector3 playerPosition ;
};

