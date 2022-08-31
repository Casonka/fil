#pragma once
    /*!
    *   --------------------------------------------------------------------------
    *                       ///Matrix\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 01/08/2022 - last update version Regulators
    *
    *       @note [RCR:Matrix] Header file Matrix
    */
#if (CALC_MATRIX == 1)

void MatrixCopy(float *m, char rows, char columns, float *new_m);
float MatrixGetCell(float *m, char rows, char columns, char row, char column);
void MatrixMultiplyM2M(float *m1, char rows1, char columns1, float *m2, char rows2, char columns2, float *new_m);
void MatrixMultiplyS2M(float *m, char rows, char columns, float s, float *new_m);
void MatrixPlusMinus(float *m1, float *m2, char rows, char columns, signed char sign,float *new_m);
void MatrixTranspose(float *m, char rows, char columns, float *new_m);
void MatrixDet_LU_Transform(float *A, char n,float *out);
void MatrixCofactor(float *m, char size, float *new_m);
void MatrixInverse(float *m, char size, float *new_m);
void MatrixFill(float *m, char rows, char columns, float val);

 typedef struct  {
	float x;
	float y;
} TVector;
//vector function
TVector Normalization( TVector a, float len);
TVector Subtraction( TVector a,  TVector b);
TVector Addition( TVector a,  TVector b);
float Mod( TVector a);
TVector Scale( TVector a, float k);

#endif /*CALC_MATRIX*/
