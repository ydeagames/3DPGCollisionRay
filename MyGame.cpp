#include "pch.h"
#include "MyGame.h"
#include "GameCamera.h"
#include "GameContext.h"
#include "Input.h"
#include "DebugCamera.h"
#include "GridFloor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::Initialize(GameContext& context)
{
	// デバッグカメラ作成
	m_pDebugCamera = std::make_unique<DebugCamera>();
	// グリッド床作成
	m_pGridFloor = std::make_unique<GridFloor>(context.GetDR().GetD3DDevice(), context.GetDR().GetD3DDeviceContext(), &context.GetStates(), 10.0f, 10);

	// フォント
	m_font = std::make_unique<SpriteFont>(context.GetDR().GetD3DDevice(), L"logofont.spritefont");
	m_batch = std::make_unique<SpriteBatch>(context.GetDR().GetD3DDeviceContext());

	// オブジェクトの処理
	{
		auto object = std::make_unique<LineShape>();
		object->posA = Vector3(0, 1, 5);
		object->material.color = Colors::Black;
		m_ray = std::move(object);
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

void MyGame::Update(GameContext& context)
{
	Input::Update();
	m_pDebugCamera->update();
	context.GetCamera().view = m_pDebugCamera->getViewMatrix();

	if (Input::GetMouseButtonDown(Input::Buttons::MouseRight))
		backMode = !backMode;
	if (!backMode)
	{
		auto ray = context.GetCamera().ScreenPointToRay(Input::GetMousePosition());
		auto plane = Plane(Vector3::Forward * BackscreenDistance, Vector3::Forward);
		float dist;
		if (ray.Intersects(plane, dist))
		{
			auto raypos = ray.position + ray.direction * dist;
			raypos.Clamp(Vector3(-5, -5, -BackscreenDistance), Vector3(5, 5, -BackscreenDistance));
			m_ray->posB = Vector3::Lerp(m_ray->posB, raypos, .1f);
		}
	}
	else
	{
		auto ray = context.GetCamera().ScreenPointToRay(Input::GetMousePosition());
		auto plane = BoundingSphere(Vector3::Zero, BacksphereRange);
		float dist;
		if (ray.Intersects(plane, dist))
		{
			auto raypos = ray.position + ray.direction * dist;
			m_ray->posB = Vector3::Lerp(m_ray->posB, raypos, .1f);
		}
	}

	// オブジェクトの更新
	for (auto& obj : m_objects)
	{
		obj->material.wireframe = m_ray->IsHit(*obj);
	}
}

void MyGame::Render(GameContext& context)
{
	m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection);
	if (!backMode)
	{
		m_pGridFloor->draw(context.GetDR().GetD3DDeviceContext(), context.GetCamera().view, context.GetCamera().projection, Colors::Turquoise, Matrix::CreateRotationX(XMConvertToRadians(90)) * Matrix::CreateTranslation(Vector3::Forward * BackscreenDistance));
	}
	else
	{
		static auto geo = GeometricPrimitive::CreateSphere(context.GetDR().GetD3DDeviceContext());
		geo->Draw(Matrix::CreateScale(Vector3(BacksphereRange) * 2.f), context.GetCamera().view, context.GetCamera().projection, Colors::Turquoise, nullptr, true);
	}
	std::wostringstream sb;
	sb << L"[操作方法]" << std::endl;
	sb << L"  2つの操作モードがあり、右クリックで切り替えます。" << std::endl;
	sb << (!backMode ? L"->" : L"  ") << L"平面モード: Rayの先端はカーソル上の平面を移動します" << std::endl;
	sb << (backMode ? L"->" : L"  ") << L"球体モード: Rayの先端はカーソル上の球体を移動します (カメラを引くとRayはカメラに近いところに移動します)" << std::endl;
	m_batch->Begin();
	m_font->DrawString(m_batch.get(), sb.str().c_str(), Vector3::Zero, Colors::White, 0, Vector3::Zero, Vector3(.5f));
	m_batch->End();

	// オブジェクトの描画
	for (auto& obj : m_objects)
		obj->Draw(context);
	m_ray->Draw(context);
}

void MyGame::Finalize(GameContext & context)
{
}
