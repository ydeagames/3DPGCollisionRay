#include "pch.h"
#include "ObjectShapes.h"
#include "GameContext.h"
#include "GameCamera.h"
#include "CapsulePrimitive.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace
{
	// 直線とAABBの衝突判定関数
	bool HitCheck_Line2AABB(const LineShape& line, const BoxShape& box, float* t = nullptr, DirectX::SimpleMath::Vector3* colPos = nullptr)
	{
		DirectX::SimpleMath::Vector3 p_l = line.posA;
		DirectX::SimpleMath::Vector3 dir_l = line.posB - line.posA;

		// 方向ベクトル正規化
		LineShape nLine = line;
		dir_l.Normalize();

		// 交差判定
		union
		{
			float f[3];
			XMFLOAT3 v;
		} p, d, min, max;
		p.v = p_l;
		d.v = dir_l;
		min.v = box.pos - box.ext;
		max.v = box.pos + box.ext;

		float tmp_t = -FLT_MAX;
		float t_max = FLT_MAX;
		for (int i = 0; i < 3; ++i)
			if (abs(d.f[i]) < FLT_EPSILON)
			{
				if (p.f[i] < min.f[i] || p.f[i] > max.f[i])
					return false; // 交差していない
			}
			else
			{
				// スラブとの距離を算出
				// t1が近スラブ、t2が遠スラブとの距離
				float odd = 1.0f / d.f[i];
				float t1 = (min.f[i] - p.f[i]) * odd;
				float t2 = (max.f[i] - p.f[i]) * odd;
				if (t1 > t2)
					std::swap(t1, t2);
				if (t1 > tmp_t) tmp_t = t1;
				if (t2 < t_max) t_max = t2;
				// スラブ交差チェック
				if (tmp_t >= t_max)
					return false;
			}
		if (t)
			*t = tmp_t;
		// 交差している
		if (colPos)
			*colPos = p_l + tmp_t * dir_l;
		return true;
	}

	float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c)
	{
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 bc = c - b;
		float e = ac.Dot(ab);
		if (e <= 0.0f)
			return ac.LengthSquared();
		float f = ab.LengthSquared();
		if (e >= f)
			return bc.LengthSquared();
		return ac.LengthSquared() - e * e / f;
	}

	bool HitCheck_Capsule2Sphere(const CapsuleShape& capsule, const SphereShape& sphere)
	{
		float dist2 = SqDistPointSegment(capsule.posA, capsule.posB, sphere.pos);
		float radius = capsule.radius + sphere.radius;
		return dist2 <= radius * radius;
	}

	bool HitCheck_Line2Sphere(const LineShape& line, const SphereShape& sphere)
	{
		CapsuleShape capsule1;
		capsule1.posA = line.posA;
		capsule1.posB = line.posB;
		capsule1.radius = 0.f;
		return HitCheck_Capsule2Sphere(capsule1, sphere);
	}

	float Clamp(float n, float min, float max)
	{
		if (n < min) return min;
		if (n > max) return max;
		return n;
	}

	Vector3 ClosestPtSegmentSegmentNorm(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2, float& s, float& t, Vector3 & c1, Vector3 & c2)
	{
		Vector3 d1 = q1 - p1; Vector3 d2 = q2 - p2; Vector3 r = p1 - p2;
		float a = d1.LengthSquared(); float e = d2.LengthSquared(); float f = d2.Dot(r);
		if (a <= FLT_EPSILON && e <= FLT_EPSILON)
		{
			s = t = 0.0f;
			c1 = p1;
			c2 = p2;
			return (c1 - c2);
		}
		if (a <= FLT_EPSILON)
		{
			s = 0.0f;
			t = f / e;
			t = Clamp(t, 0.0f, 1.0f);
		}
		else
		{
			float c = d1.Dot(r);
			if (e <= FLT_EPSILON)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else
			{
				float b = d1.Dot(d2);
				float denom = a * e - b * b;
				if (denom != 0.0f)
				{
					s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
				}
				else
				{
					s = 0.0f;
				}
				float tnom = (b * s + f);
				if (tnom < 0.0f)
				{
					t = 0.0f;
					s = Clamp(-c / a, 0.0f, 1.0f);
				}
				else if (tnom > e)
				{
					t = 1.0f;
					s = Clamp((b - c) / a, 0.0f, 1.0f);
				}
				else
				{
					t = tnom / e;
				}
			}
		}
		c1 = p1 + d1 * s;
		c2 = p2 + d2 * t;
		return (c1 - c2);
	}

	float ClosestPtSegmentSegment(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2, float& s, float& t, Vector3 & c1, Vector3 & c2)
	{
		return ClosestPtSegmentSegmentNorm(p1, q1, p2, q2, s, t, c1, c2).LengthSquared();
	}

	bool HitCheck_Capsule2Capsule(const CapsuleShape& capsule1, const CapsuleShape& capsule2, float* s = nullptr, float* t = nullptr, Vector3* c1 = nullptr, Vector3* c2 = nullptr)
	{
		float s_, t_;
		DirectX::SimpleMath::Vector3 c1_, c2_;
		float dist2 = ClosestPtSegmentSegment(capsule1.posA, capsule1.posB, capsule2.posA, capsule2.posB, s ? *s : s_, t ? *t : t_, c1 ? *c1 : c1_, c2 ? *c2 : c2_);
		float radius = capsule1.radius + capsule2.radius;
		return dist2 <= radius * radius;
	}

	bool HitCheck_Line2Capsule(const LineShape& line, const CapsuleShape& capsule, float* s = nullptr, float* t = nullptr, Vector3* c1 = nullptr, Vector3* c2 = nullptr)
	{
		CapsuleShape capsule1;
		capsule1.posA = line.posA;
		capsule1.posB = line.posB;
		capsule1.radius = 0.f;
		return HitCheck_Capsule2Capsule(capsule1, capsule, s, t, c1, c2);
	}
}

void LineShape::Draw(GameContext & context) const
{
	static auto batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context.GetDR().GetD3DDeviceContext());
	static auto geo = GeometricPrimitive::CreateCube(context.GetDR().GetD3DDeviceContext());
	batch->Begin();
	batch->DrawLine(VertexPositionColor(posA, material.color), VertexPositionColor(posB, material.color));
	batch->End();
	geo->Draw(Matrix::CreateScale(Vector3(.05f)) * Matrix::CreateTranslation(posA), context.GetCamera().view, context.GetCamera().projection, material.color, nullptr, material.wireframe);
	geo->Draw(Matrix::CreateScale(Vector3(.05f)) * Matrix::CreateTranslation(posB), context.GetCamera().view, context.GetCamera().projection, material.color, nullptr, material.wireframe);
}

bool BoxShape::IsHit(const LineShape & other) const
{
	return HitCheck_Line2AABB(other, *this);
}

void BoxShape::Draw(GameContext & context) const
{
	static auto geo = GeometricPrimitive::CreateCube(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(ext * 2) * Matrix::CreateTranslation(pos), context.GetCamera().view, context.GetCamera().projection, material.color, nullptr, material.wireframe);
}

bool SphereShape::IsHit(const LineShape & other) const
{
	return HitCheck_Line2Sphere(other, *this);
}

void SphereShape::Draw(GameContext & context) const
{
	static auto geo = GeometricPrimitive::CreateSphere(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(radius * 2) * Matrix::CreateTranslation(pos), context.GetCamera().view, context.GetCamera().projection, material.color, nullptr, material.wireframe);
}

bool CapsuleShape::IsHit(const LineShape & other) const
{
	return HitCheck_Line2Capsule(other, *this);
}

void CapsuleShape::Draw(GameContext & context) const
{
	static auto geo = CapsulePrimitive::Create(context.GetDR().GetD3DDeviceContext());
	geo->Draw(Matrix::CreateScale(radius * 2) * Matrix::CreateTranslation((posA + posB) * .5f), context.GetCamera().view, context.GetCamera().projection, material.color, nullptr, material.wireframe);
}
