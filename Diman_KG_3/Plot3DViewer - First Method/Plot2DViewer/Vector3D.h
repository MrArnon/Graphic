#pragma once 

class Vector3D 
{ 
	public: 
	double X; 
	double Y; 
	double Z; 

	Vector3D() 
	{ 
		X = Y = Z = 0; 
	} 

	Vector3D( double x, double y, double z ) 
	{ 
		X = x; 
		Y = y; 
		Z = z; 
	} 

	Vector3D( double number ) 
	{ 
		X = Y = Z = number; 
	} 

	/* CrossProduct */ 
	Vector3D operator ^ ( const Vector3D &other ) const 
	{ 
		return Vector3D( 
		Y * other.Z - Z * other.Y, 
		Z * other.X - X * other.Z, 
		X * other.Y - Y * other.X 
	) ;
	} 

	/* Dot product */ 
	float operator | ( const Vector3D & other ) const 
	{ 
	return X * other.X + Y * other.Y + Z * other.Z; 
	} 

	Vector3D & operator = ( const Vector3D & other ) 
	{ 
	this->X = other.X; 
	this->Y = other.Y; 
	this->Z = other.Z; 

	return *this; 
	} 

	Vector3D operator + ( const Vector3D & other ) 
	{ 
	return Vector3D( X + other.X, Y + other.Y, Z + other.Z ); 
	} 

	Vector3D operator - ( const Vector3D & other ) 
	{ 
	return Vector3D( X - other.X, Y - other.Y, Z - other.Z ); 
	} 

	Vector3D operator + ( float Delta ) 
	{ 
	return Vector3D( X + Delta, Y + Delta, Z + Delta ); 
	} 

	Vector3D operator - ( float Delta ) 
	{ 
	return Vector3D( X - Delta, Y - Delta, Z - Delta ); 
	} 

	Vector3D operator * ( float Scale ) 
	{ 
	return Vector3D( X * Scale, Y * Scale, Z * Scale ); 
	} 

	Vector3D operator / ( float Scale ) 
	{ 
	if ( Scale == 0 ) 
	return *this; 

	Scale = 1.f / Scale; 
	return Vector3D( X * Scale, Y * Scale, Z * Scale ); 
	} 

	bool operator == ( const Vector3D & other ) const 
	{ 
	return X == other.X && Y == other.Y && Z == other.Z; 
	} 

	bool operator != ( const Vector3D & other ) const 
	{ 
	return X != other.X && Y != other.Y && Z != other.Z; 
	} 

	double Length() 
	{ 
	return sqrt( X * X + Y * Y + Z * Z ); 
	} 

	void Normalize() 
	{ 
	const double fLength = Length(); 

	X /= fLength; 
	Y /= fLength; 
	Z /= fLength; 
	} 
};