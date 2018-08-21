/*
 Klann Mechanism animation C++ Class
 
 Author: Gerson Santos
 Date: July 1st 2015
*/

#include <boost/python.hpp>
#include <iostream>
#include <armadillo>
#include <fstream>
#include <cmath>

#define pi 3.141592653589793
using namespace arma; 
using namespace std;

class animation{
	private:
		// Longitudes de los eslabones
		double l1, l2,l3,l4;
	public:
		// Angulos de eslabones
 		double phi0,phi1,phi2;
 		// Angulos por trigonometria
 		double alfa,beta,gamma,delta,epsilon,kappa;
 		// Posicion de eslabones
 		double ax,ay,cx,cy,ex,ey,fx,fy,fx2,fy2,gx,gy;
 		// Posicion fija
 		double bx,by,dx,dy;
 		// Variables Virtuales
 		double r1,r2,r3,r4;

 		void inicializar( )		
		{
			// Angulos 
			phi0 = 0;		
			phi1 = 0;		
			phi2 = 0;       
			
			// Posicion de nodos
			ax = 0;			
			ay = 0;			
			cx = 0;     	
			cy = 0;     	
			ex = 0;     	
			ey = 0;     	
			gx = 0;     	
			gy = 0;     	
			
			// Puntos fijos
			bx = 29.5; 		
			by = -8.8;		
			dx = 11.65;		
			dy = 30.8;		
			
			// Longitud de eslabones
			l1 = 13.40;		
			l2 = 16.03;		
			l3 = 29.50;		
			l4 = 26.10;		
	
		}
		// Funcion principal
		void calcular()
		{
			phi0 +=.1* pi/180 ;
					
			// Eslabon l1
			ax = l1*cos(phi0);
			ay = l1*sin(phi0);
			
			// Variable Virtual R1
			r1 = sqrt(pow(ax-bx,2) + pow(ay-by,2));
			
			// Calculo de angulo alfa
			alfa = atan2((ay - by),(ax - bx));

			// Calculo de angulo beta
			// utilizando ley de cosenos
			beta = acos((r1*r1+l2*l2 - l3*l3)/(2*r1*l2));
			
			// Angulo de restriccion phi1
			phi1 = alfa - beta;
			
			// Nodo C
			cx = bx + l2*cos(phi1);
			cy = by + l2*sin(phi1);
			
			// Calculo de angulo phi2
			phi2 = atan2((cy-ay),(cx-ax));
			
			// Nodo F
			fx =  l3*cos(phi2) + ax;
			fy =  l3*sin(phi2) + ay; 
			
			// Nodo F2
			fx2 =  l4*cos(phi2) + l3*cos(phi2) + l1*cos(phi0);
			fy2 =  l4*sin(phi2) + l3*sin(phi2) + l1*sin(phi0); 
		
						
		}


};


// Modulo Python para usar variables en anima.py
BOOST_PYTHON_MODULE(acoplar)
{
	using namespace boost::python;
	class_<animation>("acoplar")
		.def("inicializar", &animation::inicializar)		
		.def("calcular", &animation::calcular)
		.def_readwrite("ax", &animation::ax)
		.def_readwrite("ay", &animation::ay)
		.def_readwrite("cx", &animation::cx)
		.def_readwrite("cy", &animation::cy)
		.def_readwrite("fx", &animation::fx)
		.def_readwrite("fy", &animation::fy)
		.def_readwrite("fx2", &animation::fx2)
		.def_readwrite("fy2", &animation::fy2)
		.def_readwrite("ex", &animation::ex)
		.def_readwrite("ey", &animation::ey)
		.def_readwrite("gx", &animation::gx)
		.def_readwrite("gy", &animation::gy)
		.def_readwrite("r1", &animation::r1)
		.def_readwrite("r2", &animation::r2)
		.def_readwrite("r3", &animation::r3)
		.def_readwrite("r4", &animation::r4)
		.def_readwrite("bx", &animation::bx)
		.def_readwrite("by", &animation::by)
		.def_readwrite("dx", &animation::dx)
		.def_readwrite("dy", &animation::dy)
		.def_readwrite("alfa", &animation::alfa)
		.def_readwrite("beta", &animation::beta)
		.def_readwrite("gamma", &animation::gamma)
		.def_readwrite("delta", &animation::delta)
		.def_readwrite("epsilon", &animation::epsilon)
		.def_readwrite("kappa", &animation::kappa)
		.def_readwrite("phi0", &animation::phi0)
		.def_readwrite("phi1", &animation::phi1)
		.def_readwrite("phi2", &animation::phi2);
}


// Para compilar
/*
 
g++ -g -shared -fPIC acoplar.cpp -o acoplar.so -I/usr/include/python2.7 -lpython2.7 -lboost_python-2.7 -larmadillo -llapack -lboost_iostreams -lboost_system -lboost_filesystem

*/
