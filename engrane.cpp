/*	Transmicion de engranes
	Utilizando C++ desde python
*/

#include <boost/python.hpp>
#include <iostream>
#include<armadillo>
#include<fstream>
#include <cmath>


#define pi 3.141592653589793
using namespace arma;
using namespace std;

class animation
{
	private:
		// Radio de los engranes
		double r1,r2; 
	public:
		// Angulos de eslabones
 		double phi0,phi1;
 		// Relacion de engranejes
 		double z1;

		void inicializar( )		
		{
			phi0 = 0; 			
			
	    }
		void calcular()
		{

			phi0 +=.9* pi/180; 
						
		}
};

BOOST_PYTHON_MODULE(engrane)
{
	using namespace boost::python;
	class_<animation>("engrane")
		.def("inicializar", &animation::inicializar)		
		.def("calcular", &animation::calcular)
		.def_readwrite("phi0", &animation::phi0)
		.def_readwrite("phi1", &animation::phi1)
		.def_readwrite("z1", &animation::z1);
}



/*
 
g++ -g -shared -fPIC engrane.cpp -o engrane.so -I/usr/include/python2.7 -lpython2.7 -lboost_python-2.7 -larmadillo -llapack -lboost_iostreams -lboost_system -lboost_filesystem


*/
