#pragma once

#include <SFML/System/Vector3.hpp>
#include <cstdint>

namespace sg {

/** 4x4 matrix.
 */
template <class T>
struct Matrix {
	/** Ctor.
	 * Initializes matrix with identity matrix.
	 */
	Matrix();

	/** Ctor.
	 * @param a0 Row 0, column 0.
	 * @param a1 Row 1, column 0.
	 * @param a2 Row 2, column 0.
	 * @param a3 Row 3, column 0.
	 * @param a4 Row 0, column 1.
	 * @param a5 Row 1, column 1.
	 * @param a6 Row 2, column 1.
	 * @param a7 Row 3, column 1.
	 * @param a8 Row 0, column 2.
	 * @param a9 Row 1, column 2.
	 * @param a10 Row 2, column 2.
	 * @param a11 Row 3, column 2.
	 * @param a12 Row 0, column 3.
	 * @param a13 Row 1, column 3.
	 * @param a14 Row 2, column 3.
	 * @param a15 Row 3, column 3.
	 */
	Matrix(
		T a0, T a4, T a8, T a12,
		T a1, T a5, T a9, T a13,
		T a2, T a6, T a10, T a14,
		T a3, T a7, T a11, T a15
	);

	/** Index access operator.
	 * @param index Index (0-15).
	 * @return Value.
	 */
	const T& operator[]( std::size_t index ) const;

	/** Index access operator.
	 * @param index Index (0-15).
	 * @return Value.
	 */
	T& operator[]( std::size_t index );

	/** Equality.
	 * @param other Other matrix.
	 * @return true if equal.
	 */
	bool operator==( const Matrix<T>& other ) const;

	/** Unequality.
	 * @param other Other matrix.
	 * @return true if not equal.
	 */
	bool operator!=( const Matrix<T>& other ) const;

	/** Reset to identity matrix.
	 */
	void reset();

	/** Multiply with another matrix.
	 * @param other Other matrix.
	 */
	void multiply( const Matrix<T>& other );

	/** Translate matrix.
	 * @param translation Translation vector.
	 */
	void translate( const sf::Vector3<T>& translation );

	/** Rotate matrix.
	 * @param rotation Degrees (x = pitch, y = yaw, z = roll).
	 */
	void rotate( const sf::Vector3<T>& rotation );

	/** Scale matrix.
	 * @param factor Scale factor.
	 */
	void scale( const sf::Vector3<T>& factor );

	T values[16];
};

typedef Matrix<float> FloatMatrix; ///< Float matrix.

}

#include "Matrix.inl"
