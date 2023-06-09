#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrt(SquareMagnitude(vec));

}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
	float mag = Magnitude(vec);

	vec.x = vec.x / mag;
	vec.y = vec.y / mag;

	return vec;
}

float VectorHelper::Dot(sf::Vector3f a, sf::Vector3f b)
{
	//Dot
	/*
	* ab{3D} = a[x]*b[x] + a[y]*b[y] + a[z]*b[z]
	*/

	float ab;
	ab = a.x * b.x + a.y * b.y + a.z * b.z;

	return ab;
}

float VectorHelper::Dot(sf::Vector2f a, sf::Vector2f b)
{
	//Dot
	/*
	* ab{2D} = a[x]*b[x] + a[y]*b[y]
	*/

	float ab;
	ab = a.x * b.x + a.y * b.y;
	return ab;
}

sf::Vector3f VectorHelper::Cross(sf::Vector3f a, sf::Vector3f b)
{
	//Cross
	/*
	* c[x] = a[y]b[z] - a[z]b[y]
	* c[y] = a[z]b[x] - a[x]b[z]
	* c[z] = a[x]b[y] - a[y]b[x]
	*/

	sf::Vector3f c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return c;
}

//sf::Vector2f VectorHelper::Cross(sf::Vector2f a, sf::Vector2f b)
//{
	//sf::Vector2f c;
	


	//return c;
//}

//Practical Task - Reflection
sf::Vector3f VectorHelper::GetReflection(sf::Vector3f incident, sf::Vector3f normal)
{
	//Reflection
	/*
	* R[r] = R[i] -2N(R[i].N)
	*/

	sf::Vector3f R;

	R = incident - 2.0f * normal*Dot(incident, normal);
	return R;
}

sf::Vector2f VectorHelper::GetReflection(sf::Vector2f incident, sf::Vector2f normal)
{
	//Reflection
	/*
	* R[r] = R[i] -2N(R[i].N)
	*/

	 sf::Vector2f R;

	 R = incident - 2.0f * normal * Dot(incident, normal);

	return R;
}

sf::Vector3f VectorHelper::GetNormal(sf::Vector3f line1, sf::Vector3f line2)
{
	sf::Vector3f result;
	result = Cross(line1, line2);

	return result;
}

sf::Vector2f VectorHelper::GetNormal(sf::Vector2f line)
{
	sf::Vector2f result;
	result = sf::Vector2f(line.y, -line.x);

	return result;
}
