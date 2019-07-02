#include "pch.h"
#include "ObjectShapes.h"
#include "GameContext.h"
#include "GameCamera.h"
#include "CapsulePrimitive.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void RayShape::Draw(GameContext & context) const
{
	static auto batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context.GetDR().GetD3DDeviceContext());
	batch->Begin();
	batch->DrawLine(VertexPositionColor(pos, material.m_objectColor), VertexPositionColor(pos + dir, material.m_objectColor));
	batch->End();
}

bool BoxShape::IsHit(const RayShape & other) const
{
	return false;
}

void BoxShape::Draw(GameContext & context) const
{
	static auto geo = GeometricPrimitive::CreateCube(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(ext * 2) * Matrix::CreateTranslation(pos), context.GetCamera().view, context.GetCamera().projection, material.m_objectColor, nullptr, material.m_objectWireframe);
}

bool SphereShape::IsHit(const RayShape & other) const
{
	return false;
}

void SphereShape::Draw(GameContext & context) const
{
	static auto geo = GeometricPrimitive::CreateSphere(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(radius * 2) * Matrix::CreateTranslation(pos), context.GetCamera().view, context.GetCamera().projection, material.m_objectColor, nullptr, material.m_objectWireframe);
}

bool CapsuleShape::IsHit(const RayShape & other) const
{
	return false;
}

void CapsuleShape::Draw(GameContext & context) const
{
	static auto geo = CapsulePrimitive::Create(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(radius * 2) * Matrix::CreateTranslation((posA + posB) * .5f), context.GetCamera().view, context.GetCamera().projection, material.m_objectColor, nullptr, material.m_objectWireframe);
}
