#pragma once

class GameContext;

struct Material
{
	DirectX::SimpleMath::Vector4	color = DirectX::Colors::White;		// オブジェクトの色
	bool							wireframe = false;						// オブジェクトがワイヤーフレームか
	//bool							m_objectAlpha		= false;						// オブジェクトが半透明か
};

struct ObjectShape;
struct RayShape;
struct BoxShape;
struct SphereShape;

struct ObjectShape
{
	Material						material;

	virtual bool IsHit(const ObjectShape& other) const = 0;
	virtual bool IsHit(const RayShape& other) const { return false; }
	virtual bool IsHit(const BoxShape& other) const { return false; }
	virtual bool IsHit(const SphereShape& other) const { return false; }

	virtual void Draw(GameContext& context) const = 0;
};

struct RayShape : public ObjectShape
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 dir;

	virtual bool IsHit(const ObjectShape& other) const { return other.IsHit(*this); }
	virtual void Draw(GameContext& context) const override;
};

struct BoxShape : public ObjectShape
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 ext;

	virtual bool IsHit(const ObjectShape& other) const { return other.IsHit(*this); }
	virtual bool IsHit(const RayShape& other) const override;
	virtual void Draw(GameContext& context) const override;
};

struct SphereShape : public ObjectShape
{
	DirectX::SimpleMath::Vector3 pos;
	float						 radius;

	virtual bool IsHit(const ObjectShape& other) const { return other.IsHit(*this); }
	virtual bool IsHit(const RayShape& other) const override;
	virtual void Draw(GameContext& context) const override;
};

struct CapsuleShape : public ObjectShape
{
	DirectX::SimpleMath::Vector3 posA;
	DirectX::SimpleMath::Vector3 posB;
	float						 radius;

	virtual bool IsHit(const ObjectShape& other) const { return other.IsHit(*this); }
	virtual bool IsHit(const RayShape& other) const override;
	virtual void Draw(GameContext& context) const override;
};
