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

	// �t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_batch;

	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_pDebugCamera;
	// �O���b�h��
	std::unique_ptr<GridFloor> m_pGridFloor;

private:
	// �I�u�W�F�N�g�֘A
	std::unique_ptr<LineShape> m_ray;
	std::vector<std::unique_ptr<ObjectShape>> m_objects;	// �I�u�W�F�N�g

public:
	MyGame();
	~MyGame();

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

