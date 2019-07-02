#pragma once
#include "ObjectShapes.h"

class GameContext;

class CollisionObject
{
public:
	std::unique_ptr<ObjectShape>					m_objectCollider;	// �I�u�W�F�N�g�̓����蔻��

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
	// �j��
	void Finalize(GameContext& context);
};

