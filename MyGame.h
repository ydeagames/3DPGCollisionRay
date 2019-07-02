#pragma once
#include "ObjectShapes.h"

class GameContext;

class MyGame
{
private:
	// �I�u�W�F�N�g�֘A
	std::unique_ptr<RayShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// �I�u�W�F�N�g

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

