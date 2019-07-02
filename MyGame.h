#pragma once
#include "CollisionObject.h"
#include "CapsulePrimitive.h"

class GameContext;

class MyGame
{
private:
	// �I�u�W�F�N�g�֘A
	std::unique_ptr<RayShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// �I�u�W�F�N�g

	// �I�u�W�F�N�g�֘A
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pObject1;			// �I�u�W�F�N�g�P
	std::unique_ptr<CapsulePrimitive>				m_pObject2;			// �I�u�W�F�N�g�Q
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pObject3;			// �I�u�W�F�N�g�R

	DirectX::SimpleMath::Matrix						m_object1Matrix;	// �I�u�W�F�N�g�P�̃��[���h�s��
	DirectX::SimpleMath::Matrix						m_object2Matrix;	// �I�u�W�F�N�g�Q�̃��[���h�s��
	DirectX::SimpleMath::Matrix						m_object3Matrix;	// �I�u�W�F�N�g�R�̃��[���h�s��

	DirectX::SimpleMath::Vector3					m_object1Pos;		// �I�u�W�F�N�g�P�̍��W
	DirectX::SimpleMath::Vector3					m_object2Pos;		// �I�u�W�F�N�g�Q�̍��W
	DirectX::SimpleMath::Vector3					m_object3Pos;		// �I�u�W�F�N�g�R�̍��W


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

