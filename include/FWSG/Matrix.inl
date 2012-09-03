#include <cassert>
#include <cmath>

const float PI = 3.14159265f;

namespace sg {

template <class T>
Matrix<T>::Matrix() :
	Matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	)
{
}

template <class T>
Matrix<T>::Matrix(
	T a0, T a4, T a8, T a12,
	T a1, T a5, T a9, T a13,
	T a2, T a6, T a10, T a14,
	T a3, T a7, T a11, T a15
) {
	values[ 0] = a0;
	values[ 1] = a1;
	values[ 2] = a2;
	values[ 3] = a3;

	values[ 4] = a4;
	values[ 5] = a5;
	values[ 6] = a6;
	values[ 7] = a7;

	values[ 8] = a8;
	values[ 9] = a9;
	values[10] = a10;
	values[11] = a11;

	values[12] = a12;
	values[13] = a13;
	values[14] = a14;
	values[15] = a15;
}

template <class T>
const T& Matrix<T>::operator[]( std::size_t index ) const {
	assert( index < 16 );
	return values[index];
}

template <class T>
T& Matrix<T>::operator[]( std::size_t index ) {
	assert( index < 16 );
	return values[index];
}

template <class T>
void Matrix<T>::reset() {
	values[ 0] = 1; values[ 4] = 0; values[ 8] = 0; values[12] = 0;
	values[ 1] = 0; values[ 5] = 1; values[ 9] = 0; values[13] = 0;
	values[ 2] = 0; values[ 6] = 0; values[10] = 1; values[14] = 0;
	values[ 3] = 0; values[ 7] = 0; values[11] = 0; values[15] = 1;
}

template <class T>
void Matrix<T>::multiply( const Matrix<T>& other ) {
	*this = Matrix<T>(
		values[ 0] * other.values[ 0] + values[ 4] * other.values[ 1] + values[ 8] * other.values[ 2] + values[12] * other.values[ 3],
		values[ 0] * other.values[ 4] + values[ 4] * other.values[ 5] + values[ 8] * other.values[ 6] + values[12] * other.values[ 7],
		values[ 0] * other.values[ 8] + values[ 4] * other.values[ 9] + values[ 8] * other.values[10] + values[12] * other.values[11],
		values[ 0] * other.values[12] + values[ 4] * other.values[13] + values[ 8] * other.values[14] + values[12] * other.values[15],

		values[ 1] * other.values[ 0] + values[ 5] * other.values[ 1] + values[ 9] * other.values[ 2] + values[13] * other.values[ 3],
		values[ 1] * other.values[ 4] + values[ 5] * other.values[ 5] + values[ 9] * other.values[ 6] + values[13] * other.values[ 7],
		values[ 1] * other.values[ 8] + values[ 5] * other.values[ 9] + values[ 9] * other.values[10] + values[13] * other.values[11],
		values[ 1] * other.values[12] + values[ 5] * other.values[13] + values[ 9] * other.values[14] + values[13] * other.values[15],

		values[ 2] * other.values[ 0] + values[ 6] * other.values[ 1] + values[10] * other.values[ 2] + values[14] * other.values[ 3],
		values[ 2] * other.values[ 4] + values[ 6] * other.values[ 5] + values[10] * other.values[ 6] + values[14] * other.values[ 7],
		values[ 2] * other.values[ 8] + values[ 6] * other.values[ 9] + values[10] * other.values[10] + values[14] * other.values[11],
		values[ 2] * other.values[12] + values[ 6] * other.values[13] + values[10] * other.values[14] + values[14] * other.values[15],

		values[ 3] * other.values[ 0] + values[ 7] * other.values[ 1] + values[11] * other.values[ 2] + values[15] * other.values[ 3],
		values[ 3] * other.values[ 4] + values[ 7] * other.values[ 5] + values[11] * other.values[ 6] + values[15] * other.values[ 7],
		values[ 3] * other.values[ 8] + values[ 7] * other.values[ 9] + values[11] * other.values[10] + values[15] * other.values[11],
		values[ 3] * other.values[12] + values[ 7] * other.values[13] + values[11] * other.values[14] + values[15] * other.values[15]
	);
}

template <class T>
void Matrix<T>::translate( const sf::Vector3<T>& translation ) {
	multiply(
		Matrix<T>(
			1, 0, 0, translation.x,
			0, 1, 0, translation.y,
			0, 0, 1, translation.z,
			0, 0, 0, 1
		)
	);
}

template <class T>
void Matrix<T>::rotate( const sf::Vector3<T>& rotation ) {
	float cos_a = std::cos( rotation.x * PI / 180.0f );
	float sin_a = std::sin( rotation.x * PI / 180.0f );
	float cos_b = std::cos( rotation.y * PI / 180.0f );
	float sin_b = std::sin( rotation.y * PI / 180.0f );
	float cos_g = std::cos( rotation.z * PI / 180.0f );
	float sin_g = std::sin( rotation.z * PI / 180.0f );

	multiply(
		Matrix<T>(
			cos_b * cos_g, cos_b * sin_g, -sin_b, 0,
			sin_a * sin_b * cos_g - cos_a * sin_g, sin_a * sin_b * sin_g + cos_a * cos_g, sin_a * cos_b, 0,
			cos_a * sin_b * cos_g + sin_a * sin_g, cos_a * sin_b * sin_g - sin_a * cos_g, cos_a * cos_b, 0,
			0, 0, 0, 1
		)
	);
}

template <class T>
void Matrix<T>::scale( const sf::Vector3<T>& factor ) {
	multiply(
		Matrix<T>(
			factor.x, 0, 0, 0,
			0, factor.y, 0, 0,
			0, 0, factor.z, 0,
			0, 0, 0, 1
		)
	);
}

template <class T>
bool Matrix<T>::operator==( const Matrix<T>& other ) const {
	return
		(values[ 0] == other.values[ 0]) &&
		(values[ 1] == other.values[ 1]) &&
		(values[ 2] == other.values[ 2]) &&
		(values[ 3] == other.values[ 3]) &&
		(values[ 4] == other.values[ 4]) &&
		(values[ 5] == other.values[ 5]) &&
		(values[ 6] == other.values[ 6]) &&
		(values[ 7] == other.values[ 7]) &&
		(values[ 8] == other.values[ 8]) &&
		(values[ 9] == other.values[ 9]) &&
		(values[10] == other.values[10]) &&
		(values[11] == other.values[11]) &&
		(values[12] == other.values[12]) &&
		(values[13] == other.values[13]) &&
		(values[14] == other.values[14]) &&
		(values[15] == other.values[15])
	;
}

template <class T>
bool Matrix<T>::operator!=( const Matrix<T>& other ) const {
	return
		(values[ 0] != other.values[ 0]) ||
		(values[ 1] != other.values[ 1]) ||
		(values[ 2] != other.values[ 2]) ||
		(values[ 3] != other.values[ 3]) ||
		(values[ 4] != other.values[ 4]) ||
		(values[ 5] != other.values[ 5]) ||
		(values[ 6] != other.values[ 6]) ||
		(values[ 7] != other.values[ 7]) ||
		(values[ 8] != other.values[ 8]) ||
		(values[ 9] != other.values[ 9]) ||
		(values[10] != other.values[10]) ||
		(values[11] != other.values[11]) ||
		(values[12] != other.values[12]) ||
		(values[13] != other.values[13]) ||
		(values[14] != other.values[14]) ||
		(values[15] != other.values[15])
	;
}

}
