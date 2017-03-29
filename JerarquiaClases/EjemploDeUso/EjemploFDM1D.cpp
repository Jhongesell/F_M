
#include "CtrlParametros.hpp"
#include "FDM1D.hpp"
#include "Problema_1DEjemp01.hpp"
#include "Geometria_1DHomogenea.hpp"
#include "ResuelveTridiagonal.hpp"


// Ejemplo para resolver un problema en una dimensi�n mediante el m�todo de diferencias
int main(int argc, const char *args[])
{
   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);
	int nx = parm.intVal("nx",10); // Partici�n en X

   // Geometria
   Geometria_1DHomogenea *ge1 = new Geometria_1DHomogenea();

   // Problema
   Problema_1DEjemp01 *pr = new Problema_1DEjemp01();
   pr->inicializa(ge1, nx);
   pr->visualizaProblema();   
   ge1->visualiza();

   // Metodo de resoluci�n del sistema lineal asociado al m�todo
   ResuelveTridiagonal *rsl = new ResuelveTridiagonal();
   
   
   // M�todo de diferencias finitas
   FDM1D fdm(pr, ge1, rsl);
   fdm.activaVisualiza(false);
   fdm.resuelve();
   fdm.visualizaSolucion();
   fdm.grabaSolucion("Solucion.txt");
   printf("\nError %lf\n\n",fdm.error());
   
   // Libera la memoria solicitada
   delete pr;
   delete ge1;
   delete rsl;
   
   return 0;
}
