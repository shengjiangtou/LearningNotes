﻿/**
*@brief Description: Algorithm module of robotics, according to the 
book [modern robotics : mechanics,planning,and control].
*@File:RobotAlgorithmModule.c
*@Author:LiBing
*@Date:2019/03/01
*@note:     
*@warning: 
*/
#include "RobotAlgorithmModule.h"
#include <math.h>
#include <string.h>
/**
*@brief Description:use GrublersFormula calculate The number of degrees of 
freedom of a mechanism with links and joints.
*@param[in]		N		the number of links( including the ground ).
*@param[in]		m		the number of degrees of freedom of a rigid body
*						(m = 3 for planar mechanisms and m = 6 for spatial mechanisms).
*@param[in]		J		the number of joints.
*@param[in]		f		the number of freedoms provided by each joint..
*@return				The number of degrees of freedom of a mechanism
*@note:					This formula holds only if all joint constraints are independent.
*						If they are not independent then the formula provides a lower 
*						bound on the number of degrees of freedom.
*@waring:
*/
int GrublersFormula(int m, int N, int J, int *f)
{
	int i;
	int dof;
	int c = 0;
	for (i=1;i<=J;i++)
	{
		c = c + f[i-1];
	}
	dof = m*(N - 1 - J) + c;
	return dof;
}

/**
*@brief Description: Make  matrix b equal to  matrix a.
*@param[in]			a		a 3 x 3  matrix.
*@param[out]		b		result,b=a.
*@note:
*@waring:
*/
void Matrix3Equal(double a[][3], double b[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	return;
}

/**
*@brief Description: Make  matrix b equal to  matrix a.
*@param[in]			a		a 4 x 4  matrix.
*@param[out]		b		result,b=a.
*@note:
*@waring:
*/
void Matrix4Equal(double a[][4], double b[][4])
{
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	return;
}


/**
*@brief Description:Calculate a 3 x 3  matrix add a 3 x 3  matrix.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		b		a 3 x 3  matrix.
*@param[out]	c		result of a+b.
*@note:
*@waring:
*/
void Matrix3Add(double a[][3], double b[][3], double c[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return;
}

/**
*@brief Description:Calculate a 3 x 3  matrix Subtract a 3 x 3  matrix.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		b		a 3 x 3  matrix.
*@param[out]	c		result of a-b.
*@note:
*@waring:
*/
void Matrix3Sub(double a[][3], double b[][3], double c[][3])
{
	int i;
	int j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
	return;
}

/**
*@brief Description: Calculate two 3 x 3  matrix multiplication. 
*@param[in]		a		a 3 x 3  matrix.		
*@param[in]		b		a 3 x 3  matrix.	
*@param[out]	c		result of a*b.
*@note:
*@waring:
*/
void Matrix3Mult(double a[][3],double b[][3],double c[][3])
{
	int i;
	int j;
	int k;
	for (i=0;i<3;i++)
	{		
		for (j=0;j<3;j++)
		{
			c[i][j] = 0.0;
			for (k=0;k<3;k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}

		}
	}
	return;
}

/**
*@brief Description: Calculate two 4 x 4  matrix multiplication.
*@param[in]		a		a 4 x 4  matrix.
*@param[in]		b		a 4 x 4  matrix.
*@param[out]	c		result of a*b.
*@note:
*@waring:
*/
void Matrix4Mult(double a[][4], double b[][4], double c[][4])
{
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			c[i][j] = 0.0;
			for (k = 0; k < 4; k++)
			{
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}

		}
	}
	return;
}


/**
*@brief Description: Calculate  3 x 3  matrix multiply a value.
*@param[in]		a		a 3 x 3  matrix.
*@param[in]		Value	a scalar value.
*@param[out]	c		result of a*Value.
*@note:
*@waring:
*/
void Matrix3MultValue(double a[][3], double Value, double c[][3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			c[i][j] = a[i][j] * Value;
		}
	}
	return;
}

/**
*@brief Description: Calculate  4 x 4  matrix multiply a value.
*@param[in]		a		a 4 x 4  matrix.
*@param[in]		Value	a scalar value.
*@param[out]	c		result of a*Value.
*@note:
*@waring:
*/
void Matrix4MultValue(double a[][4], double Value, double c[][4])
{
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			c[i][j] = a[i][j] * Value;
		}
	}
	return;
}


/**
*@brief Description:Computes the result of a 3 x 3 Matrix multiply a 3-vector.
*@param[in]		R			a 3 x 3 Matrix.
*@param[in]		vec1		an input of 3-vector.
*@param[out]	vec2		the output result of 3-vector.
*@note:
*@waring:
*/
void Matrix3MultVec(double R[3][3], double vec1[3], double vec2[3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		vec2[i] = 0;
		for (j=0;j<3;j++)
		{
			vec2[i] = vec2[i] + R[i][j] * vec1[j];
		}
	}
	return;
}

/**
*@brief Description:Computes a 3-vector add a 3-vector.
*@param[in]		vec1		a 3-vector.
*@param[in]		vec2		a 3-vector.
*@param[out]	vec3		result of vec1 + vec2;
*@note:
*@waring:
*/
void Vec3Add(double vec1[3], double vec2[3], double vec3[3])
{
	vec3[0] = vec1[0] + vec2[0];
	vec3[1] = vec1[1] + vec2[1];
	vec3[2] = vec1[2] + vec2[2];
	return;
}


/**
*@brief Description:Computes result of two 3-vector cross product.
*@param[in]		vec1		a first 3-vector.
*@param[in]		vec2		a first 3-vector.
*@param[out]	vec3		result of vec1 cross product vec2.
*@note:
*@waring:
*/
void Vec3Cross(double vec1[3],double vec2[3],double vec3[3])
{
	vec3[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	vec3[1] = -(vec1[0] * vec2[2] - vec2[0] * vec1[2]);
	vec3[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];
	return;
}

/**
*@brief Description:Computes a 3-vector multiply a scalar value.
*@param[in]		vec1			a 3-vector.
*@param[in]		value			a scalar value.
*@param[out]	vec2			result of vec1 * value. 
*@note:
*@waring:
*/
void Vec3MultValue(double vec1[3], double value, double vec2[3])
{
	vec2[0] = vec1[0] * value;
	vec2[1] = vec1[1] * value;
	vec2[2] = vec1[2] * value;
	return;
}

/**
*@brief Description: Computes the norm of a 3-vector.
*@param[in]		vec			an input 3-vector.
*@retval		the norm of a an input 3-vector.
*@note:
*@waring:
*/
double Vec3Norm(double vec[3])
{
	return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}


/**
*@brief Computes the inverse of the rotation matrix R.
*@param[in]		R		rotation matrix .
*@param[out]	InvR	inverse matrix of R.
*@note					Input R must be a 3 x 3 rotation matrix.
*/
void RotInv(double R[3][3], double InvR[3][3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			InvR[i][j] = R[j][i];
		}
	}
	return;
}

/**
*@brief Description:Returns the 3 x 3 skew-symmetric matrix corresponding to omg.
*@param[in]		omg		a 3-vector.
*@param[out]	so3Mat	the 3 x 3 skew-symmetric matrix corresponding to omg.
*@note:
*@waring:
*/
void VecToso3(double omg[3],double so3Mat[3][3])
{
	so3Mat[0][0] = 0.0;		so3Mat[0][1] = -omg[2]; so3Mat[0][2] = omg[1];
	so3Mat[1][0] = omg[2];	so3Mat[1][1] = 0;		so3Mat[1][2] = -omg[0];
	so3Mat[2][0] = -omg[1];	so3Mat[2][1] = omg[0];	so3Mat[2][2] = 0.0;
	return;
}


/**
*@brief Description:Returns the 3-vector corresponding to the 3 x 3 skew-symmetric matrix so3mat.
*@param[in]		so3Mat		a 3 x 3 skew-symmetric matrix so3mat
*@param[out]	omg			the 3-vector
*@note:
*@waring:
*/
void so3ToVec(double so3Mat[3][3], double omg[3])
{
	omg[0] = so3Mat[2][1]; omg[1] = so3Mat[0][2]; omg[2] = so3Mat[1][0];
	return;
}


/**
*@brief Description:Extracts  the unit rotation axis omghat and the corresponding
rotation angle theta from exponential coordinates omghat*theta for rotation, expc3.
*@param[in]		expc3			
*@param[out]	omghat		the unit vector of rotation axis .
*@param[out]	theta		rotation angle.
*@retval        0			success.
*@note:
*@waring:
*/
void AxisAng3(double expc3[3],double omghat[3],double *theta)
{
	int i;
	int ret = 0;
	*theta = sqrt(expc3[0] * expc3[0] + expc3[1] * expc3[1] + expc3[2] * expc3[2]);
	if (*theta<ZERO_VALUE)
	{
		omghat[0] = 0.0;
		omghat[1] = 0.0;
		omghat[2] = 0.0;
		*theta = 0.0;
		return;
	}
	for (i=0;i<3;i++)
	{
		omghat[i]=expc3[i]/(*theta);
	}
	return ;
}

/**
*@brief Description:Computes the rotation matrix R in SO(3) corresponding to
the matrix exponential of so3mat in so(3).
*@param[in]		so3Mat		[omghat]*theta,matrix exponential of so3mat in so(3).			
*@param[out]	R			rotation matrix R in SO(3).
*@note:
*@waring:
*/
void MatrixExp3(double so3Mat[3][3],double R[3][3])
{
	double omgtheta[3];
	double omghat[3] = { 0 };
	double theta = 0;
	int ret = 0;
	int i;
	int j;
	double MatI3[3][3] =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};
	so3ToVec(so3Mat, omgtheta);
	AxisAng3(omgtheta, omghat, &theta);
	if (theta<ZERO_VALUE)
	{
		Matrix3Equal(MatI3, R);
		return ;
	}
	else
	{

		//calculate formula(3.51) in book [modern robotics : mechanics,planning,and control]
		double omgmat[3][3];
		double temp[3][3];
		Matrix3MultValue(so3Mat, 1.0 / theta, omgmat);
		Matrix3Mult(omgmat, omgmat, temp);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				R[i][j] = MatI3[i][j] + sin(theta)*so3Mat[i][j] / theta + (1 - cos(theta))*temp[i][j];
			}
		}
	}
	return;
}

/**
*@brief Description:Computes the matrix logarithm so3mat in so(3) of the rotation matrix R in SO(3).
*@param[in]		R		the rotation matrix.
*@param[out]	so3Mat	matrix logarithm.
*@note:
*@waring:
*/
void MatrixLog3(double R[3][3],double so3Mat[3][3])
{
	double omg[3] = { 0 };
	double acosinput = (R[0][0] + R[1][1] + R[2][2] - 1.0) / 2;
	if (acosinput > 1.0)
	{
		memset(so3Mat, 0, 9 * sizeof(double));
	}
	else if (acosinput<=-1.0)
	{
		if ((1.0+R[2][2])>= ZERO_VALUE)
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*R[0][2];
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*R[1][2];
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[2][2]))*(1.0 + R[2][2]);
		}
		else if ((1.0+R[1][1]>=ZERO_VALUE))
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*R[0][1];
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*(1.0 + R[1][1]);
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[1][1]))*R[2][1];
		}
		else 
		{
			omg[0] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*(1.0 + R[0][0]);
			omg[1] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*R[1][0];
			omg[2] = 1.0 / sqrt(2 * (1.0 + R[0][0]))*R[2][0];
		}
		omg[0] = PI*omg[0];
		omg[1] = PI*omg[1];
		omg[2] = PI*omg[2];
		VecToso3(omg, so3Mat);
	}
	else
	{
		int i;
		int j;
		double theta = acos(acosinput);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				so3Mat[i][j] = 1.0 / (2.0*sin(theta))*(R[i][j] - R[j][i])*theta;
			}
		}
	}

	return;
}

/**
*@brief Description:Builds the homogeneous transformation matrix T corresponding to a rotation 
matrix R in SO(3) and a position vector p in R3.
*@param[in]		R		a rotation matrix R in SO(3).
*@param[in]		p		a position vector p in R3.
*@param[out]	T		the homogeneous transformation matrix T.
*@note:
*@waring:
*/
void RpToTrans(double R[3][3], double p[3], double T[4][4])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			T[i][j] = R[i][j];
		}
	}
	T[0][3] = p[0];
	T[1][3] = p[1];
	T[2][3] = p[2];
	T[3][0] = 0.0; 
	T[3][1] = 0.0; 
	T[3][2] = 0.0;
	T[3][3] = 1.0;
	return;
}

/**
*@brief Description: Extracts the rotation matrix R and position vector p 
from a homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	R		the rotation matrix.
*@param[out]	p		position vector.
*@note:
*@waring:
*/
void TransToRp(double T[4][4], double R[3][3], double p[3])
{
	int i;
	int j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			R[i][j] = T[i][j];
		}
	}
	p[0] = T[0][3];
	p[1] = T[1][3];
	p[2] = T[2][3];
	return;
}

/**
*@brief Description:Computes the inverse of a homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	InvT	the inverse of T.
*@note:
*@waring:
*/
void TransInv(double T[4][4],double InvT[4][4])
{
	double R[3][3];
	double InvR[3][3];
	double p[3];
	double p2[3];
	TransToRp(T, R, p);
	RotInv(R, InvR);
	Matrix3MultValue(InvR, -1.0, R);
	Matrix3MultVec(R, p, p2);
	RpToTrans(InvR, p2, InvT);
	return;
}

/**
*@brief Description:Computes the se(3) matrix corresponding to a 6-vector twist V.
*@param[in]		V		a 6-vector twist V.
*@param[out]	se3Mat	the se(3) matrix.
*@note:
*@waring:
*/
void VecTose3(double V[6], double se3Mat[4][4])
{
	double so3Mat[3][3];
	double omg[3];
	int i;
	int j;
	omg[0] = V[0];
	omg[1] = V[1];
	omg[2] = V[2];
	VecToso3(omg, so3Mat);
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			se3Mat[i][j] = so3Mat[i][j];
		}

	}
	se3Mat[0][3] = V[3];
	se3Mat[1][3] = V[4];
	se3Mat[2][3] = V[5];
	se3Mat[3][0] = 0.0;
	se3Mat[3][1] = 0.0;
	se3Mat[3][2] = 0.0;
	se3Mat[3][3] = 0.0;
	return;
}

/**
*@brief Description:Computes the 6-vector twist corresponding to an se(3) matrix se3mat.
*@param[in]		se3Mat			an se(3) matrix.
*@param[out]	V				he 6-vector twist.
*@note:
*@waring:
*/
void se3ToVec(double se3Mat[4][4],double V[6])
{
	V[0] = se3Mat[2][1];
	V[1] = se3Mat[0][2];
	V[2] = se3Mat[1][0];
	V[3] = se3Mat[0][3];
	V[4] = se3Mat[1][3];
	V[5] = se3Mat[2][3];
	return;
}

/**
*@brief Description:Computes the 6 x 6 adjoint representation [AdT ] 
of the homogeneous transformation matrix T.
*@param[in]		T		a homogeneous transformation matrix.
*@param[out]	AdT		the 6 x 6 adjoint representation [AdT ].
*@note:
*@waring:
*/
void Adjoint(double T[4][4], double AdT[6][6])
{
	double R[3][3];
	double p[3];
	double so3Mat[3][3];
	int i;
	int j;
	TransToRp(T, R, p);
	VecToso3(p, so3Mat);
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			AdT[i][j] = R[i][j];
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 3; j < 6; j++)
		{
			AdT[i][j] = 0.0;
		}
	}
	for (i=3;i<6;i++)
	{
		for (j = 3; j < 6; j++)
		{
			AdT[i][j] = R[i-3][j-3];
		}
	}
	double mat[3][3];
	Matrix3Mult(so3Mat, R, mat);
	for (i = 3; i < 6; i++)
	{
		for (j = 0; j < 3; j++)
		{
			AdT[i][j] = mat[i-3][j];
		}
	}

	return;
}

/**
*@brief Description: Computes a normalized screw axis representation S of a screw described by 
a unit vector s in the direction of the screw axis, located at the point q, with pitch h.
*@param[in]		q		a point lying on the screw axis.
*@param[in]		s		a unit vector in the direction of the screw axis.
*@param[in]		h		the pitch of the screw axis.
*@param[in]		S		a normalized screw axis representation.
*@note:
*@waring:
*/
void ScrewToAxis(double q[3], double s[3], double h,double S[6])
{
	double v[3];
	double temp[3];
	Vec3Cross(s, q, temp);
	Vec3MultValue(temp, -1.0, temp);
	Vec3MultValue(s, h, v);
	Vec3Add(v, temp, v);
	S[0] = s[0];
	S[1] = s[1];
	S[2] = s[2];
	S[3] = v[0];
	S[4] = v[1];
	S[5] = v[2];
	return;
}

/**
*@brief Description: Extracts the normalized screw axis S and the distance traveled along the screw
theta from the 6-vector of exponential coordinates S*theta.
*@param[in]		expc6		the 6-vector of exponential coordinates.
*@param[out]	S			the normalized screw axis.
*@param[out]	theta		the distance traveled along the screw.
*@retval		0			success; 
*@retval		1			failure,because the input expc6 is a zero vector
*@note:
*@waring:
*/
void AxisAng6(double expc6[6],double S[6],double *theta)
{
	*theta = Vec3Norm(expc6);
	if (*theta<ZERO_VALUE)
	{
		*theta = Vec3Norm(&expc6[3]);
		if (*theta<ZERO_VALUE)
		{
			*theta=0.0;
			//S is undefine,no motion at all.
			S[0] = 0.0; S[1] = 0.0; S[2] = 0.0; S[3] = 0.0; S[4] = 0.0; S[5] = 0.0;
			return;
		}
	}
	Vec3MultValue(expc6, 1.0 / (*theta), S);
	Vec3MultValue(&expc6[3], 1.0 / (*theta), &S[3]);
	return ;
}

/**
*@brief Description: Computes the homogeneous transformation matrix T in SE(3) corresponding to
the matrix exponential of se3mat in se(3).
*@param[in]		se3mat			the matrix exponential of se3mat in se(3).
*@param[out]	T				the homogeneous transformation matrix T in SE(3).
*@note:
*@waring:
*/
void MatrixExp6(double se3Mat[4][4], double T[4][4])
{
	int i;
	int j;
	double so3mat[3][3];
	double omgmat[3][3];
	double temp[3][3];
	double Gtheta[3][3];
	double p[3];
	double v[3];
	double omgtheta[3];
	double omghat[3];
	double theta;
	double MatI3[3][3] =
	{
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	};
	TransToRp(se3Mat, so3mat, p);//extracts so3mat from se3mat
	so3ToVec(so3mat, omgtheta);
	if (Vec3Norm(omgtheta)<ZERO_VALUE)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				T[i][j] = MatI3[i][j];
			}
		}
		T[0][3] = se3Mat[0][3];
		T[1][3] = se3Mat[1][3];
		T[2][3] = se3Mat[2][3];
		T[3][0] = 0.0;
		T[3][1] = 0.0;
		T[3][2] = 0.0;
		T[3][3] = 1.0;
	}
	else
	{
		AxisAng3(omgtheta, omghat, &theta);
		MatrixExp3(so3mat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				T[i][j] = temp[i][j];
			}
		}
		Matrix3MultValue(so3mat, 1.0/theta,omgmat);
		Matrix3Mult(omgmat, omgmat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Gtheta[i][j] = MatI3[i][j] * theta + (1.0 - cos(theta))*omgmat[i][j] + (theta - sin(theta))*temp[i][j];
			}
		}	
		v[0] = p[0] / theta; 
		v[1] = p[1] / theta;
		v[2] = p[2] / theta;
		Matrix3MultVec(Gtheta, v, p);
		T[0][3] = p[0]; T[1][3] = p[1]; T[2][3] = p[2];
		T[3][0] = 0.0;
		T[3][1] = 0.0;
		T[3][2] = 0.0;
		T[3][3] = 1.0;
	}
	return;
}


/**
*@brief Description: Computes the matrix logarithm se3mat in se(3) of 
the homogeneous transformation matrix T in SE(3)
*@param[in]		T			the homogeneous transformation matrix.			
*@param[out]	se3Mat		the matrix logarithm of T.
*@note:
*@waring:
*/
void MatrixLog6(double T[4][4], double se3Mat[4][4])
{
	int i;
	int j;
	double R[3][3];
	double so3mat[3][3];
	double p[3];
	TransToRp(T, R, p);
	MatrixLog3(R, so3mat);
	int flag = 0;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (fabs(so3mat[i][j])<ZERO_VALUE)
			{
				continue;
			}
			else
			{
				flag = 1;
				break;
			}
		}
	}
	if (!flag)
	{
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				se3Mat[i][j] = 0.0;
			}

		}
		se3Mat[0][3] = T[0][3];
		se3Mat[1][3] = T[1][3];
		se3Mat[2][3] = T[2][3];
		se3Mat[3][0] = 0.0;
		se3Mat[3][1] = 0.0;
		se3Mat[3][2] = 0.0;
		se3Mat[3][3] = 0.0;
	}
	else
	{
		double MatI3[3][3] =
		{
			1.0,0.0,0.0,
			0.0,1.0,0.0,
			0.0,0.0,1.0
		};
		double v[3];
		double temp[3][3];
		double InvGtheta[3][3];
		double theta = acos((R[0][0] + R[1][1] + R[2][2] - 1.0) / 2.0);
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				se3Mat[i][j] = so3mat[i][j];
			}
		}

		Matrix3Mult(so3mat, so3mat, temp);
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				InvGtheta[i][j] = MatI3[i][j] - 0.5*so3mat[i][j] + (1.0 / theta - 0.5*1.0 / tan(0.5*theta))*temp[i][j] / theta;
			}
		}
		Matrix3MultVec(InvGtheta, p, v);
		se3Mat[0][3] = v[0];
		se3Mat[1][3] = v[1];
		se3Mat[2][3] = v[2];
		se3Mat[3][0] = 0.0;
		se3Mat[3][1] = 0.0;
		se3Mat[3][2] = 0.0;
		se3Mat[3][3] = 0.0;
	}
	return ;
}

/**
*@brief Description: Computes the end-effector frame given the zero position of the end-effector M,
the list of joint screws Slist expressed in the fixed-space frame, and the list of joint values thetalist.
*@param[in]		M			the zero position of the end-effector expressed in the fixed-space frame.
*@param[in]		JointNum	the number of joints.
*@param[in]		Slist		the list of joint screws Slist expressed in the fixed-space frame.
*@param[in]		thetalist   the list of joint values.
*@param[out]	T			the end-effector frame expressed in the fixed-space frame.
*@note:
*@waring:
*/
void FKinSpace(double M[4][4],int  JointNum,double Slist[][6], double thetalist[],double T[4][4])
{
	int i;
	int j;
	int k;
	double se3mat[4][4];
	double T2[4][4];
	double exp6[4][4];
	Matrix4Equal(M, T);
	for (i= JointNum-1;i>=0;i--)
	{
		VecTose3(&Slist[i][0], se3mat);
		for (j=0;j<4;j++)
		{
			for (k=0;k<4;k++)
			{
				se3mat[j][k] = se3mat[j][k] * thetalist[i];
			}
		}
		MatrixExp6(se3mat, exp6);
		Matrix4Mult(exp6, T, T2);
		Matrix4Equal(T2, T);
	}
	return ;
}

/**
*@brief Description:Computes the end-effector frame given the zero position of the end-effector M,
the list of joint screws Blist expressed in the end-effector frame, and the list of joint values thetalist.
*@param[in]		M			the zero position of the end-effector expressed in the end-effector frame.
*@param[in]		JointNum	the number of joints.
*@param[in]		Blist		the list of joint screws Slist expressed in the end-effector frame.
*@param[in]		thetalist   the list of joint values.
*@param[out]	T			the end-effector frame expressed in the end-effector frame.
*@note:
*@waring:
*/
void FKinBody(double M[4][4], int  JointNum, double Blist[][6], double thetalist[], double T[4][4])
{
	int i;
	int j;
	int k;
	double se3mat[4][4];
	double T2[4][4];
	double exp6[4][4];
	Matrix4Equal(M, T);
	for (i = 0; i < JointNum ; i++)
	{
		VecTose3(&Blist[i][0], se3mat);
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				se3mat[j][k] = se3mat[j][k] * thetalist[i];
			}
		}
		MatrixExp6(se3mat, exp6);
		Matrix4Mult(T, exp6, T2);
		Matrix4Equal(T2, T);
	}
	return ;
}


/**
*@brief Description: Computes the body Jacobian Jb(theta) in 6×n given a list of joint screws Bi 
expressed in the body frame and a list of joint angles.
*@param[in]		Blist		The joint screw axes in the end - effector frame when the manipulator is 
*							at the home position, in the format of a matrix with the screw axes as the column.
*@param[in]		thetalist	A list of joint coordinates.
*@note:
*@waring:
*/
void JacobianBody(int JointNum,double Blist[][MAXJOINTNUM], double thetalist[],double Jb[][MAXJOINTNUM])
{
	int i;
	int j;
	int k;
	double T1[4][4];
	double T2[4][4];
	double se3mat[4][4];
	double V[6];
	double AdT[6][6];
	double T[4][4] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	//Fist column of Jbn.
	for (i=0;i<6;i++)
	{
		Jb[i][JointNum -1] = Blist[i][JointNum - 1];
	}
	//Jbi for i=n-1,n-2,...,1.
	for (i= JointNum -2;i>=0;i--)
	{
		for (j=0;j<6;j++)
		{
			V[j] = -1.0*Blist[j][i+1];
		}
		VecTose3(V, se3mat);
		Matrix4MultValue(se3mat, thetalist[i+1], se3mat);
		MatrixExp6(se3mat, T1);
		Matrix4Mult(T, T1,T2);
		Matrix4Equal(T2, T);
		Adjoint(T, AdT);
		for (j=0;j<6; j++)
		{
			Jb[j][i] = 0;
			for (k=0;k<6;k++)
			{
				Jb[j][i] = Jb[j][i] + AdT[j][k] * Blist[k][i];
			}
		}
	}
	return ;
}

/**
*@brief Description:Computes the space Jacobian Js(theta) in R6 x n given a list of joint screws Si 
expressed in the fixed space frame and a list of joint angles.
*@param[in]		Slist		The joint screw axes expressed in the fixed space frame when the manipulator is
*							at the home position, in the format of a matrix with the screw axes as the column.
*@param[in]		thetalist	A list of joint coordinates.
*@retval		 0			success.
*@retval		 1			failure,the input parameters are error.
*@note:
*@waring:
*/
void JacobianSpace(int JointNum, double Slist[][MAXJOINTNUM], double thetalist[], double Jb[][MAXJOINTNUM])
{
	int i;
	int j;
	int k;
	double T1[4][4];
	double T2[4][4];
	double se3mat[4][4];
	double V[6];
	double AdT[6][6];
	double T[4][4] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	//Fist column of Js.
	for (i = 0; i < 6; i++)
	{
		Jb[i][0] = Slist[i][0];
	}
	//Jsi for i=2,3,...,n.
	for (i = 1; i <JointNum; i++)
	{
		for (j = 0; j < 6; j++)
		{
			V[j] = Slist[j][i - 1];
		}
		VecTose3(V, se3mat);
		Matrix4MultValue(se3mat, thetalist[i - 1], se3mat);
		MatrixExp6(se3mat, T1);
		Matrix4Mult(T, T1, T2);
		Matrix4Equal(T2, T);
		Adjoint(T, AdT);
		for (j = 0; j < 6; j++)
		{
			Jb[j][i] = 0;
			for (k = 0; k < 6; k++)
			{
				Jb[j][i] = Jb[j][i] + AdT[j][k] * Slist[k][i];
			}
		}
	}
	return;
}