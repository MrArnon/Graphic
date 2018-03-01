
#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation( double x, double y )
{
	double T [ 9 ] = {
		1.0, 0, x,
		0, 1.0, y,
		0, 0, 1.0 };
	return Matrix<>( 3, 3, T );
}

Matrix<> Translation( double x, double y, double z )
{
	double T [ 16 ] = {
		1.0, 0, 0, x,
		0, 1.0, 0, y,
		0, 0, 1.0, z,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> Identity()
{
	double T [ 9 ] = {
		1.0, 0, 0,
		0, 1.0, 0,
		0, 0, 1.0
	};

	return Matrix<>( 3, 3, T );
}

Matrix<> Identity3D()
{
	double T [ 16 ] = {
		1.0, 0, 0, 0,
		0, 1.0, 0, 0,
		0, 0, 1.0, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> Rotation( double X )
{
	double T [ 9 ] = {
		cos( X ), -sin( X ), 0,
		sin( X ),  cos( X ), 0,
		0,			0,		 1.0
	};

	return Matrix<>( 3, 3, T );
}

Matrix<> Rotation( double C, double S )
{
	double K = sqrt( pow( C, 2 ) + pow( S, 2 ) );

	double T [ 9 ] = {
		C/K, -S/K, 0,
		S/K,  C/K, 0,
		0,	0, 1.0
	};

	return Matrix<>( 3, 3, T );
}

Matrix<> RotationX( double t )
{
	double T [ 16 ] = {
		1.0, 0, 0, 0,
		0, cos( t ), -sin( t ), 0,
		0, sin( t ), cos( t ), 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> RotationX( double c, double s )
{
	double K = sqrt( pow( c, 2 ) + pow( s, 2 ) );
	double T [ 16 ] = {
		1.0, 0, 0, 0,
		0, c/K, -s/K, 0,
		0, s/K, c/K, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> RotationY( double t )
{
	double T [ 16 ] = {
		cos( t ), 0, sin( t ), 0,
		0, 1.0, 0, 0,
		-sin( t ), 0, cos( t ), 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> RotationY( double c, double s )
{
	double K = sqrt( pow( c, 2 ) + pow( s, 2 ) );
	double T [ 16 ] = {
		c/K, 0, s/K, 0,
		0, 1.0, 0, 0,
		-s/K, 0, c/K, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> RotationZ( double t )
{
	double T [ 16 ] = {
		cos( t ), -sin( t ), 0, 0,
		sin( t ), cos( t ), 0, 0,
		0, 0, 1.0, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> RotationZ( double c, double s )
{
	double K = sqrt( pow( c, 2 ) + pow( s, 2 ) );
	double T [ 16 ] = {
		c/K, -s/K, 0, 0,
		s/K, c/K, 0, 0,
		0, 0, 1.0, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> Scaling( double Kx, double Ky )
{
	double T [ 9 ] = {
		Kx, 0, 0,
		0, Ky, 0,
		0, 0,  1.0
	};

	return Matrix<>( 3, 3, T );
}

Matrix<> Scaling( double Kx, double Ky, double Kz )
{
	double T [ 16 ] = {
		Kx, 0, 0, 0,
		0, Ky, 0, 0,
		0, 0, Kz, 0,
		0, 0, 0, 1.0
	};

	return Matrix<>( 4, 4, T );
}

Matrix<> Mapping( bool isXAxis )
{
	if ( isXAxis ) return Scaling( -1, 1 , 1);
	if ( !isXAxis ) return Scaling( 1, -1 , 1);
}

/*Matrix<> ScaleAroundPoint( float CoordX, float CoordY, float ScaleSpeed, bool bScaleUp )
{
	float ScaleKoeff = bScaleUp ? 1.1 : 0.9;
	return Translation( CoordX, CoordY ) * 
		Scailing( ScaleKoeff * ScaleSpeed, ScaleKoeff * ScaleSpeed )  *
		Translation( -CoordX, -CoordY );
}

Matrix<> MapAroundLine( float FirstX, float FirstY, float SecondX, float SecondY )
{
	return Translation( FirstX, FirstY ) *
		Rotation( SecondX-FirstX, SecondY-FirstY) *
		Mapping( false ) *
		Rotation( SecondX-FirstX, FirstY-SecondY) *
		Translation( -FirstX, -FirstY);
	/*
		Rotation( FirstY - SecondYFirstX - SecondX,  ) *
		Mapping( true ) *
		Rotation( SecondY - FirstY, FirstX - SecondX ) *
		Translation( -FirstX, -FirstY );
		
}*/

#endif AFFINE_TRANSFORM_H