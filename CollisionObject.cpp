#include "pch.h"
#include "CollisionObject.h"
#include "GameCamera.h"
#include "GameContext.h"
#include "ObjectShapes.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CollisionObject::Initialize(GameContext & context)
{
}

void CollisionObject::Update(GameContext & context)
{
}

void CollisionObject::Render(GameContext & context)
{
	// �I�u�W�F�N�g�̕`��
	m_objectCollider->Draw(context);
}

void CollisionObject::Finalize(GameContext & context)
{
}
