#pragma once
#include "ObjectShapes.h"

class GameContext;

class CollisionObject
{
public:
	std::unique_ptr<ObjectShape>					m_objectCollider;	// オブジェクトの当たり判定

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

