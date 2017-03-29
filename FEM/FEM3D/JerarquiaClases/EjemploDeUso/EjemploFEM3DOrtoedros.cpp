
#include "CtrlParametros.hpp"
#include "FEM3DOrtoedros.hpp"
#include "Problema_3DEjemp01.hpp"
#include "Geometria_3DOrtoedros.hpp"
#include "ResuelveCGMBandDisp.hpp"
#include "ResuelveJacobiBandDisp.hpp"
#include "ResuelveGaussSeidelBandDisp.hpp"
#include "ResuelveFactorizacionLUBandDisp.hpp"
#include "ResuelveInversa.hpp"


// Ejemplo para resolver un problema en dos dimensiones mediante el método de elemento finito
int main(int argc, char *args[])
{
   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);
	 
   // Definicion de la geometria	
   Geometria_3DOrtoedros *ge = new Geometria_3DOrtoedros();

   // Definicion del problema
   Problema_3DEjemp01 *pr = new Problema_3DEjemp01();
   pr->inicializa(ge,parm.intVal("nx",10),parm.intVal("ny",10),parm.intVal("nz",10));
   
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
      FEM3DOrtoedros fem(pr, ge, rsl[i]);
      fem.resuelve();
      fem.visualizaSolucion();
      fem.grabaSolucion("Solucion.txt");
      fem.error();
      printf("\n\n");
   }   
   
   // Borra la memoiria dinamica
   delete pr;
   delete ge;
   delete rsl1;
   delete rsl2;
   delete rsl3;
   delete rsl4;
   delete rsl5;
   
   
   return 0;
}
