//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría en dos dimensiones usando triángulos                   //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// Página:   http://www.mmc.igeofcu.unam.mx/acl                                             //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#include "Geometria_2DTriangulos.hpp"

// Genera la geometria
void Geometria_2DTriangulos::generaGeometria(void)
{
   int i, j, t, n;


   // Solicita la memoria necesaria
   EL = new MatrizInt(N_E,NNE,"Nodos que conforman a los elementos",-1);
   if (!EL) errorSolicitudMemoria("Geometria Triangulos");
   int col[]= {Particion.retorna(0)+1,Particion.retorna(1)+1};
   ND = new MatrizTamanoVariable(DIM,col,"Coordenadas de Nodos");
   if (!ND) errorSolicitudMemoria("Coordenadas Geometria Triangulos");
   NN = new VectorInt(N_N,"Coordenadas de Nodos");
   if (!NN) errorSolicitudMemoria("Geometria Triangulos");


   // Calcula los tamaños de las particiones horizontales como verticales
   ldouble Ic_H = (Dominio.retorna(1,0) - Dominio.retorna(0,0)) / Particion.retorna(0);
   ldouble Ic_V = (Dominio.retorna(1,1) - Dominio.retorna(0,1)) / Particion.retorna(1);


   for (i = 0; i < Particion.retorna(1); i++)
   {
      ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
      for (j = 0; j < Particion.retorna(0); j++)
      {
         ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
         t = (i * Particion.retorna(0) * 2) + (j * 2);

         // Triangulo inferior
         n = (i * Particion.retorna(0)) + j + i;
         EL->asigna(t,0,n);

         n = (i * Particion.retorna(0)) + j + 1 + i;
         EL->asigna(t,1,n);

         n = ((i + 1) * Particion.retorna(0)) + j + 1 + i;
         EL->asigna(t,2,n);

         t ++;
         // Tringulo superior
         n = (i * Particion.retorna(0)) + j + 1 + i;
         EL->asigna(t,0,n);

         n = ((i + 1) * Particion.retorna(0)) + j + i + 2;
         EL->asigna(t,1,n);

         n = ((i + 1) * Particion.retorna(0)) + j + 1 + i;
         EL->asigna(t,2,n);
      }
      ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
   }
   ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
}



// Regresa el valor del área del elemento
// @return Area del elemento
ldouble Geometria_2DTriangulos::areaElemento(int el)
{
   ldouble x[3];
   ldouble y[3];
   coordenadasElemento(el, x, y);
   return ((x[1]*y[2]-x[2]*y[1]) - (x[0]*(y[2]-y[1])) + (y[0]*(x[2]-x[1]))) / 2.0;
}





