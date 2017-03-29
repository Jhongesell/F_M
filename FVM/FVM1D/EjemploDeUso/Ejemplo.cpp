
#include "FVM1D.hpp"
#include "CtrlParametros.hpp"
#include "Problema_1DEjemp01.hpp"
#include "Geometria_1DHomogenea.hpp"
#include "ResuelveTridiagonal.hpp"


// Ejemplo para resolver un problema en una dimensión mediante el método de volumen finito
int main(int argc, const char *args[])
{
   // Control de parametros pasados de la linea de comandos
   CtrlParametros parm(argc, args);
	int nx = parm.intVal("nx",10); // Partición en X

   // Definicion de la geometria
   Geometria_1DHomogenea *ge1 = new Geometria_1DHomogenea();

   // Definicion del problema
   Problema_1DEjemp01 *pr = new Problema_1DEjemp01();
   pr->inicializa(ge1, nx);
   
   // Visualiza problema y geomentria
   pr->visualizaProblema();   
   ge1->visualiza();

   // Declara el metodo numerico para resolver el sistema lineal asociado
   ResuelveTridiagonal *rsl = new ResuelveTridiagonal();
   
   // FVM
   FVM1D fvm(pr, ge1, rsl);
   fvm.resuelve();
   fvm.visualizaSolucion();
   fvm.grabaSolucion("Solucion.txt");
   printf("\nError %lf\n\n",fvm.error());
   
   
   // Libera la memoiria dinamica
   delete pr;
   delete ge1;
   delete rsl;
   
   return 0;
}
