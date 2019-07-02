#include "pch.h"
#include "MyGame.h"
#include "GameCamera.h"
#include "GameContext.h"
#include "Input.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void MyGame::Initialize(GameContext & context)
{
	// オブジェクトの処理
	{
		m_ray = std::make_unique<RayShape>();
		m_ray->pos = Vector3(0, 1, -5);
	}
	{
		auto object = std::make_unique<SphereShape>();
		object->pos = Vector3(2.0f, 0.0f, 0.0f);
		object->radius = .5f;
		object->material.color = Colors::Red;
		m_objects.emplace_back(std::move(object));
	}
	{
		auto object = std::make_unique<CapsuleShape>();
		auto pos = Vector3(-2.0f, 0.0f, 0.0f);
		object->posA = pos + Vector3::Up * .5f;
		object->posB = pos + Vector3::Down * .5f;
		object->radius = .5f;
		object->material.color = Colors::Blue;
		m_objects.emplace_back(std::move(object));
	}
	{
		auto object = std::make_unique<BoxShape>();
		object->pos = Vector3(0.0f, 0.0f, 0.0f);
		object->ext = Vector3::One * .5f;
		object->material.color = Colors::Green;
		m_objects.emplace_back(std::move(object));
	}
}

void MyGame::Update(GameContext & context)
{
	Input::Update();

	auto key = Keyboard::Get().GetState();
	{
		auto input = Vector3::Zero;
		if (key.A || key.Left)
			input.x -= 1;
		if (key.D || key.Right)
			input.x += 1;
		if (key.W || key.Up)
			input.z -= 1;
		if (key.S || key.Down)
			input.z += 1;
		if (key.Q || key.LeftShift)
			input.y -= 1;
		if (key.E || key.Space)
			input.y += 1;
		m_ray->dir = input * .01f - m_ray->pos;
	}

	// オブジェクトの更新
	for (auto& obj : m_objects)
	{
		if (m_ray->IsHit(*obj))
		{
		}
	}
}

void MyGame::Render(GameContext & context)
{
	// オブジェクトの描画
	for (auto& obj : m_objects)
		obj->Draw(context);
	m_ray->Draw(context);
}

void MyGame::Finalize(GameContext & context)
{
}
