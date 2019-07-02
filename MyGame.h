#pragma once
#include "ObjectShapes.h"

class GameContext;

class MyGame
{
private:
	// オブジェクト関連
	std::unique_ptr<RayShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// オブジェクト

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

