#pragma once
class Vector2
{
public:
	float x, y, z;

	Vector2();
	Vector2(float x, float y, float z);
	~Vector2();

	void set(float x, float y, float z);
	void zero();
};

