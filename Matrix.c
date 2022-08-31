#include "Matrix.h"

#if (CALC_MATRIX == 1)
void MatrixCopy(float *m, char rows, char columns, float *new_m)
{
  char i,j;

    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
          *(new_m+columns*i+j) = *(m+columns*i+j);
}

//Забить в ячейку значение val
void MatrixSetCell(float *m, char rows, char columns, char row, char column, float val)
{
  *(m+columns*(row-1)+column-1) = val;
}


//Забить все ячейки значением val
void MatrixFill(float *m, char rows, char columns, float val)
{
char i,j;

for(i = 0; i < rows; i++)
   for(j = 0; j < columns; j++)
      *(m+columns*i+j) = val;
}


//Получить значение ячейки
float MatrixGetCell(float *m, char rows, char columns, char row, char column)
{
  return *(m+columns*(row-1)+column-1);
}

//Операция перемножения матриц
void MatrixMultiplyM2M(float *m1, char rows1, char columns1, float *m2, char rows2, char columns2, float *new_m)
{
float Sum;
char i,j,k;

  if (columns1 != rows2)
      *new_m = 0;
  else
    {
      for(i = 0; i < rows1; i++)
        for (j = 0; j < columns2; j++)
        {
            Sum = 0;
            for(k = 0; k < columns1; k++)
                Sum+= (*(m1+columns1*i+k)) * (*(m2+columns2*k+j));
            *(new_m+columns2*i+j) = Sum;
        }
    }
}


//Умножение числа(скаляра S) на матрицу
void MatrixMultiplyS2M(float *m, char rows, char columns, float s, float *new_m)
{
char i,j;

for(i = 0; i < rows; i++)
  for (j = 0; j < columns; j++)
    *(new_m+i*columns+j) = (*(m+i*columns+j))*s;
}


//Сложение/вычитание матриц
void MatrixPlusMinus(float *m1, float *m2, char rows, char columns, signed char sign,float *new_m)
{
char i,j;

if (sign >= 0)
  {
    for(i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
        *(new_m+i*columns+j) = (*(m1+i*columns+j)) + (*(m2+i*columns+j));
  }
else
  {
    for(i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
        *(new_m+i*columns+j) = (*(m1+i*columns+j)) - (*(m2+i*columns+j));
  }
}


void MatrixTranspose(float *m, char rows, char columns, float *new_m)
{
char i,j;
for(i = 0; i < rows; i++)
  for (j = 0; j < columns; j++)
    *(new_m+j*rows+i) = *(m+i*columns+j);
}

//Вычисление матрицы алгебраических дополнений
void MatrixCofactor(float *m, char size, float *new_m)
{
//float *buf1 = malloc(sizeof(float) * (size-1) * (size-1));
  float bufxx[10][10];
  float *buf1=(float*)bufxx;
char i=0,j=0,k=0,l=0, c=0, d=0;
signed char sign;

while (i<size)
  {
    j = 0;
    while (j<size)
      {
        k = 0;
        c = 0;
        if (((i+j)%2) == 0)
          sign = 1;
        else
          sign = -1;


        while (k<(size-1))
          {
            if (c == i)
              c++;
            l = 0;
            d = 0;
            while(l<(size-1))
              {
                if (d == j)
                  d++;
                *(buf1+(size-1)*k+l) = *(m+size*c+d);
                l++;
                d++;
              }
            k++;
            c++;
          }
          matrixDet_LU_Transform(buf1, size - 1,(new_m+size*i+j));
        *(new_m+size*i+j)*=sign;
        j++;
      }
    i++;
  }
}


//Нахождение определителя квадратной матрицы по методу LU-разложения
void MatrixDet_LU_Transform(float *A, char n,float *out) //необходимо задать исходную матрицу и переменную для LU-матрицы
{
float temp = 0;//, *LU = malloc(sizeof(float) * n * n);
float LU_ [3][3];
float * LU = (float*)LU_;
char i,j,k;
for (j = 0; j < n; j++)
  {
    *(LU+j) = *(A+j);
    if (j >= 1)
      *(LU+j*n) = *(A+j*n)/(*LU);
  }
for (i = 1; i < n; i++)
  {
    for (j = i; j < n; j++)
      {
        for (k = 0; k <= (i-1); k++)
          temp += (*(LU+n*i+k))*(*(LU+k*n+j));
        *(LU+i*n+j) = *(A+i*n+j) - temp;
        temp = 0;
      }
    for (j = i+1; j < n; j++)
      {
        for (k = 0; k <= (i-1); k++)
          temp += (*(LU+j*n+k))*(*(LU+k*n+i));
        *(LU+j*n+i) = ((*(A+j*n+i)) - temp)/(*(LU+i*n+i));
        temp = 0;
      }
  }
temp = 1;
for (i = 0; i < n; i++)
  temp *= *(LU+i*n+i);
*out=temp;
}

void MatrixInverse(float *m, char size, float *new_m)
{
float buf1[4][4];// = malloc(sizeof(float) * size * size);
float buf2 [4][4];//= malloc(sizeof(float) * size * size);
float buf;
float buf3[3][3];
 float det ;
  MatrixDet_LU_Transform(m, size,&det);
char i,j;

MatrixCofactor(m, size, &buf1[0][0]);
MatrixTranspose(&buf1[0][0], size, size, &buf2[0][0]);

for (i = 1; i <= size; i++)
  for (j = 1; j <= size; j++)
    {
      buf = MatrixGetCell(&buf1[0][0], size, size, i, j)/det;
      MatrixSetCell((float*)buf3, size, size, i, j, buf);
    }
MatrixTranspose(&buf3[0][0], size, size, new_m);
}

TVector Subtraction( TVector a,  TVector b)
{
     TVector result   ;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
    return result;
}

TVector Addition( TVector a,  TVector b)
{
     TVector result   ;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
    return result;
}

TVector Normalization( TVector a, float len)
{
     TVector result   ;
  float mod = pow(a.x * a.x + a.y * a.y, 0.5) ;
  if (mod > 0) {
	float k = len/mod;

	 result.x = a.x * k;
	 result.y = a.y * k;
  }
    return result;
}

TVector Scale( TVector a, float k)
{
  TVector result   ;
  result.x = a.x * k;
  result.y = a.y * k;
  return result;
}

float Mod( TVector a)
{
  return pow(a.x * a.x + a.y * a.y, 0.5);
}
#endif /*CALC_MATRIX*/

