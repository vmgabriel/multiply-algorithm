/*
 * Multi.cxx
 * 
 * Copyright 2016 Gabriel Vargas <gabreta@VmGabriel96>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
 //Tiempo para el tamaño M N Tiempo(graf 1) T(N)(graf 2) T(M,N)(graf 2)

#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
    return
	(double)(a->tv_sec + (double)a->tv_usec/1000000) -
	(double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int aleatorio ()
{
    int a = rand() % 5000 + 5000;
    return a;
}

//Funcion destructiva de memoria en uso (DESTRUCT)
void destruct (int *** mdes)
{
    int x=(sizeof mdes/sizeof *mdes);
    int y=0;
    for (int i=0;i<x;i++)
    {
	y=(sizeof mdes[i]/sizeof *mdes[i]);
	for (int j=0;j<y;j++)
	{
	    delete mdes[i][j];
	}
	y=0;
	delete []mdes[i];
    }
    delete []mdes;
}

void llenar (int ** mat, int x, int y)
{
    for (int i=0 ;i<x ;i++)
    {
	mat[i] = new int [y];
	for (int j=0 ;j<y; j++)
	{
	    mat[i][j]=aleatorio();
	}
    }
}

void proc (int ** a, int ** b, int ** c,int n, int m, int d)
{
    /*
      a = Apuntador de apuntadores de matriz 1
      b = Apuntador de apuntadores de matriz 2
      c = Apuntador de apuntadores de matriz Final
      
      Mat 1
      |1 2|
      |1 2|      2 = x = tamaño final de la matriz
      |1 2|[x,y][2,3]   3 = y = tamaño igual

      Mat 2
      |1 2 3|
      |1 2 3|          3 = y = tamaño igual
      |1 2 3|[y,z][3,3]   3 = z = tamaño final de la matriz

      [2,3]*[3,3] =[2,3] = [x,y]*[y,z]=[x,z]

      n = x
      m = z
      d = y
     */
    for (int i=0; i<n ;i++)
    {
	c[i] = new int [m];
	for (int j=0; j<m ;j++)
	{
	    c[i][j]=0;
	    for (int k=0; k<d ;k++)
	    {
		c[i][j] = c[i][j]+(a[i][k]*b[k][j]);
	    }
	}
    }
}

void imprimir (int ** m, int x, int y)
{
    for (int i=0;i<x;i++)
    {
	cout<<"|";
	for (int j=0;j<y;j++)
	{
	    cout<<" "<<m[i][j];
	}
	cout<<" |"<<endl;
    }
}

int main(int argc, char **argv)
{
    int n=10,m=20;
    for (n=10;n<=200;n+=10)
    {
	struct timeval t_ini, t_fin;
	double secs;

	int d=10;

	int ** m1 = new int *[n];
	int ** m2 = new int *[n];

	llenar(m1,n,n);
	llenar(m2,n,n);
    
	int ** mr = new int *[n];

	//usado para eliminar lo que hay en cada caso
	int *** temp = new int **[3];
	temp[0]=m1;
	temp[1]=m2;
	temp[2]=mr;

	gettimeofday(&t_ini, NULL);
	proc (m1,m2,mr,n,m,d);
	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);

	cout<<"time with "<<m<<","<<n<<" is "<<secs<<endl;

	destruct(temp);
	m+=20;
    }
    return 0;
}
