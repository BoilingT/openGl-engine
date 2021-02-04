#pragma once

#include <iostream>;
#include <string>;
#include <math.h>;

using namespace std;

/// <summary>
/// Vector containing x, y, z, w values,
/// When using operators the w value will not change
/// </summary>
class Vec4 {
public:
	float x = 0, y = 0, z = 0, w = 0;
	Vec4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vec4() {
		x, y, z, w = 0;
	}

#pragma region operators

	auto operator / (float other) {
		Vec4 vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		vec.w = w / other;
		return vec;
	}

	auto operator * (float other) {
		Vec4 vec;
		vec.x = x * other;
		vec.y = y * other;
		vec.z = z * other;
		vec.w = w * other;

		return vec;
	}

	auto operator + (float other) {
		Vec4 vec;
		vec.x = x + other;
		vec.y = y + other;
		vec.z = z + other;
		vec.w = w + other;

		return vec;
	}

	/////////////////////////////////////////////////

	auto operator / (Vec4 other) {
		Vec4 vec;
		vec.x = x / other.x;
		vec.y = y / other.y;
		vec.z = z / other.z;
		vec.w = w / other.w;

		return vec;
	}

	auto operator * (Vec4 other) {
		Vec4 vectorProducts = { x * other.x, y * other.y, z * other.z, w * other.w };

		float result = vectorProducts.x + vectorProducts.y + vectorProducts.z + vectorProducts.w;

		return result;
	}

	auto operator + (Vec4 other) {
		Vec4 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		vec.z = z + other.z;
		vec.w = w + other.w;
		return vec;
	}

#pragma endregion

	string toString() {

		string result = "{" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ", " + to_string(w) + "}";

		return result;
	}
};


/// <summary>
/// Vector containing x, y, z values
/// </summary>
class Vec3 {
public:
	float x = 0, y = 0, z = 0;
	Vec3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vec3() {
		x, y, z = 0;
	}

	/// <summary>
	/// Returns the magnitude/size of the vector
	/// </summary>
	/// <returns>float</returns>
	float abs() {
		float result = sqrt(
			(powf(x, 2) + powf(y, 2) + powf(z, 2))
		);
		return result;
	}

	/// <summary>
	/// Returns the vector values
	/// </summary>
	/// <returns>string</returns>
	string toString() {

		string result = "{" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "}";

		return result;
	}

	//Operators
#pragma region operators



	auto operator / (float other) {
		Vec3 vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		return vec;
	}

	auto operator * (float other) {
		Vec3 vec;
		vec.x = x * other;
		vec.y = y * other;
		vec.z = z * other;
		return vec;
	}

	auto operator + (float other) {
		Vec3 vec;
		vec.x = x + other;
		vec.y = y + other;
		vec.z = z + other;
		return vec;
	}

	//

	auto operator / (Vec3 other) {
		Vec3 vec;
		vec.x = x / other.x;
		vec.y = y / other.y;
		vec.z = z / other.z;
		return vec;
	}

	auto operator * (Vec3 other) {
		Vec3 vectorProducts = { x * other.x, y * other.y, z * other.z };

		float result = vectorProducts.x + vectorProducts.y + vectorProducts.z;

		return result;
	}

	auto operator + (Vec3 other) {
		Vec3 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		vec.z = z + other.z;
		return vec;
	}

#pragma endregion

	
};

//Find the angle between two vectors
float dotProduct(Vec3 u, Vec3 v) {
	/*
		u * v = ||u|| * ||v|| * cos(x)

		find cos(x):

		a = b * cos(x)

		cos(x) = a/b
		x = acos(a/b)
		
	*/
	float uMag = u.abs(), vMag = v.abs();
	float quota = (u * v) / (uMag * vMag);
	float x = acosf(quota);

	return x;
}
