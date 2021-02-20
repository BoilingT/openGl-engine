#include "vectorMath.h"
#define MATH_PI 3.1415926535897932384626433832795 /* PI */

vec3::vec3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
	values = new float[3]{x, y, z};
}

std::string vec3::toString() {
	std::string str = "{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "}";
	return str;
}

float* vec3::getValues() {
	return values;
}

float vec3::magnitude() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float vec3::dotProduct(vec3 vec) {
	//vec1 * vec2 = ||vec1||*||vec2||*cos(x)
	//a*b = |a|*|b|*cos(x)
	//x = (vec1*vec2)
	
	float x;
	
	x = acosf((*this * vec) / (magnitude() * vec.magnitude()));

		
	return x;
}

float vec3::dotProduct(vec3 vec, std::string str) {
	//vec1 * vec2 = ||vec1||*||vec2||*cos(x)
	//a*b = |a|*|b|*cos(x)
	//x = (vec1*vec2)
	float x;

	x = acosf((*this * vec) / (magnitude() * vec.magnitude()));

	return (str == "degree" || str == "d") ? x * (180 / MATH_PI) : x;
}


vec4::vec4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
	values = new float[4]{ x, y, z, w };

}

std::string vec4::toString() {
	std::string str = "{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + +", " + std::to_string(w) + "}";
	return str;
}
float* vec4::getValues() {
	return values;
}
