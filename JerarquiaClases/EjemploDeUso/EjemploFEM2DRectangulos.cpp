
#include "CtrlParametros.hpp"
#include "FEM2DRectangulos.hpp"
#include "Problema_2DEjemp01.hpp"
#include "Geometria_2DRectangulos.hpp"
#include "ResuelveCGMBandDisp.hpp"
#include "ResuelveJacobiBandDisp.hpp"
#include "ResuelveGaussSeidelBandDisp.hpp"
#include "ResuelveFactorizacionLUBandDisp.hpp"
#include "ResuelveInversa.hpp"
#include <time.h>



// Ejemplo para resolver un problema en dos dimensiones mediante el método de elemento finito
int main(int argc, const char *args[])
{
   /// Tiempo inicial
   time_t t1;
   /// Tiempo final
   time_t t2;
   
   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);
	int nx = parm.intVal("nx",5); // Partición en X
   int ny = parm.intVal("ny",nx); // Partición en Y
   
   // Definicion de la geometria	
   Geometria_2DRectangulos *ge = new Geometria_2DRectangulos();

   // Definicion del problema
   Problema_2DEjemp01 *pr = new Problema_2DEjemp01();
   pr->inicializa(ge,nx,ny);
   
   // Visualiza problema y geomentria
   pr->visualizaProblema();   
   ge->visualiza();

   // Declara los distintos metodos numericos para resolver el sistema lineal asociado
   ResuelveCGMBandDisp *rsl1 = new ResuelveCGMBandDisp();
   ResuelveJacobiBandDisp *rsl2 = new ResuelveJacobiBandDisp();
   ResuelveGaussSeidelBandDisp *rsl3 = new ResuelveGaussSeidelBandDisp();
   ResuelveFactorizacionLUBandDisp *rsl4 = new ResuelveFactorizacionLUBandDisp();
   ResuelveInversa *rsl5 = new ResuelveInversa();
   // Uso de punteros para cambiar el metodo numerico
   ResuelveSistemaLineal *rsl[5];
   rsl[0] = rsl1;   
   rsl[1] = rsl2;   
   rsl[2] = rsl3;
   rsl[3] = rsl4;
   rsl[4] = rsl5;

   // FEM
   for (int i = 0; i < 5; i++)
   {
      time(&t1);
      FEM2DRectangulos fem(pr, ge, rsl[i]);
      fem.activaVisualiza(false);
      fem.resuelve();
      fem.visualizaSolucion();
      fem.grabaSolucion("Solucion.txt");
      fem.error();
      printf("\n\n");
      time(&t2);
      printf("\nTiempo Cálculo: %f\n",difftime(t2,t1));
   }   
   
   // Libera la memoiria dinamica
   delete pr;
   delete ge;
   delete rsl1;
   delete rsl2;
   delete rsl3;
   delete rsl4;
   delete rsl5;
   
   
   return 0;
}
