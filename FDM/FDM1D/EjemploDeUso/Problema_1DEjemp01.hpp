

#ifndef __Problema_1DEjemp01__
#define __Problema_1DEjemp01__

#include "Problema_1D.hpp"


class Problema_1DEjemp01 : public Problema_1D
{

public:

   /// Constructor de la clase
   Problema_1DEjemp01(void) : Problema_1D()
   {
      // Dominio
      Dominio.asigna(0,0,0.0);
      Dominio.asigna(1,0,1.0);

      // Tipo de frontera
      TipoFrontera.asigna(0,DIRICHLET);
      TipoFrontera.asigna(1,DIRICHLET);

      Coeficientes_constantes = true;
      Solucion_analitica = SOLUCION_ANALITICA_NO_DISPONIBLE;
   }


   /// Lado derecho de la ecuacion
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @param di Banda solicitada
       @return Valor de la función */
   ldouble f(ldouble *x, int di)
   {
      if (di == -1) return (-1.0/(h*h)-1.0/(2.0*h));
      if (di ==  0) return (2.0/(h*h));
      if (di ==  1) return (-1.0/(h*h)+1.0/(2.0*h));
      printf("\nError al solicitar valores de funcion");
      return 0.0;
   }


   /// Retorna la solucion exacta
   /** @param x Puntero al arreglo de coordenadas del punto solicitado
       @return Valor de la solución */
   ldouble solucionExacta(ldouble *x)
   {
      return 0.0;
   }

   // Lado derecho de la ecuacion
   ldouble ladoDerecho(ldouble *x)
   {
      return 0.0;
   }

   /// Valor en la frontera X = X0
   /** @param x Puntero al arreglo de coordenadas
       @param fr Número de frontera
       @return Valor en la frontera */
   ldouble condicionesFrontera(ldouble *x, int fr)
   {
      if (fr == 0) return 0.0;
      if (fr == 1) return 1.0;
      printf("\nError al solicitar valores de la frontera");
      return 0.0;
   }


   /// Visualiza la definicion del problema
   void visualizaProblema(void)
   {
      printf ("\n\n -Uxx+Ux=0");
      printf ("\n   0<x<1");
      printf ("\n   U(0)=0 y U(1)=1\n");
   }


};

/**
Esta clase implementa los comportamientos para definir un problema en una dimensión
@example Ejemplo.cpp */

#endif
