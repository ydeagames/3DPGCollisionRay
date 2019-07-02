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
	m_ray = std::make_unique<RayShape>();
	m_ray->pos = Vector3(0, 1, -5);

	// オブジェクトの処理
	auto object = std::make_unique<SphereShape>();
	object->pos = Vector3::Zero;
	object->radius = .5f;
	m_objects.emplace_back(std::move(object));

	// オブジェクト作成
	m_pObject1 = GeometricPrimitive::CreateSphere(context.GetDR().GetD3DDeviceContext());
	m_pObject2 = CapsulePrimitive::Create(context.GetDR().GetD3DDeviceContext());
	m_pObject3 = GeometricPrimitive::CreateBox(context.GetDR().GetD3DDeviceContext(), SimpleMath::Vector3::One);

	// オブジェクトの初期座標設定
	m_object1Pos = SimpleMath::Vector3(2.0f, 0.0f, 0.0f);
	m_object2Pos = SimpleMath::Vector3(-2.0f, 0.0f, 0.0f);
	m_object3Pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
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

	// オブジェクトの更新
	m_object1Matrix = SimpleMath::Matrix::CreateTranslation(m_object1Pos);
	m_object2Matrix = SimpleMath::Matrix::CreateTranslation(m_object2Pos);
	m_object3Matrix = SimpleMath::Matrix::CreateTranslation(m_object3Pos);

}

void MyGame::Render(GameContext & context)
{
	// オブジェクトの描画
	for (auto& obj : m_objects)
		obj->Draw(context);

	// オブジェクトの描画
	m_pObject1->Draw(m_object1Matrix, context.GetCamera().view, context.GetCamera().projection, Colors::Red);
	m_pObject2->Draw(m_object2Matrix, context.GetCamera().view, context.GetCamera().projection, Colors::Blue);
	m_pObject3->Draw(m_object3Matrix, context.GetCamera().view, context.GetCamera().projection, Colors::Green);

}

void MyGame::Finalize(GameContext & context)
{
	m_pObject1.reset();
	m_pObject2.reset();

}
