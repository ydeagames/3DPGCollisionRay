#pragma once
#include "ObjectShapes.h"

class DebugCamera;
class GridFloor;

class GameContext;

class MyGame
{
private:
	static constexpr float BackscreenDistance = 5.f;
	static constexpr float BacksphereRange = 7.5f;

	bool backMode = false;

	// フォント
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_batch;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_pDebugCamera;
	// グリッド床
	std::unique_ptr<GridFloor> m_pGridFloor;

private:
	// オブジェクト関連
	std::unique_ptr<LineShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// オブジェクト

public:
	MyGame();
	~MyGame();

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

