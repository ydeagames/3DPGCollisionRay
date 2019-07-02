#pragma once
#include "CollisionObject.h"
#include "CapsulePrimitive.h"

class GameContext;

class MyGame
{
private:
	// オブジェクト関連
	std::unique_ptr<RayShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// オブジェクト

	// オブジェクト関連
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pObject1;			// オブジェクト１
	std::unique_ptr<CapsulePrimitive>				m_pObject2;			// オブジェクト２
	std::unique_ptr<DirectX::GeometricPrimitive>	m_pObject3;			// オブジェクト３

	DirectX::SimpleMath::Matrix						m_object1Matrix;	// オブジェクト１のワールド行列
	DirectX::SimpleMath::Matrix						m_object2Matrix;	// オブジェクト２のワールド行列
	DirectX::SimpleMath::Matrix						m_object3Matrix;	// オブジェクト３のワールド行列

	DirectX::SimpleMath::Vector3					m_object1Pos;		// オブジェクト１の座標
	DirectX::SimpleMath::Vector3					m_object2Pos;		// オブジェクト２の座標
	DirectX::SimpleMath::Vector3					m_object3Pos;		// オブジェクト３の座標


public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
	// 破棄
	void Finalize(GameContext& context);
};

