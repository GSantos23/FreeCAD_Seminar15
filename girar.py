# Archivo de animacion modificado ---- 8/Jun/2015

# execfile("/home/gerson/Simpo_FreeCAD/girar.py")

import os
os.chdir("/home/gerson/Simpo_FreeCAD") #**************************


import Part
from PyQt4 import QtCore, QtGui 
from FreeCAD import Base
from math import cos, sin, degrees, radians
import sys

sys.path.append('/home/gerson/Simpo_FreeCAD')  #*********************************
import engrane


animation=reload(engrane)
a=animation.engrane()
a.inicializar()



def circulo( ):
	global a
	a.calcular()
	
	pi =  3.141592653589793


	phi0=degrees(a.phi0)
	phi1=degrees(a.phi1)


	#print "phi4 = ", phi4 

	# Movimiento de engranes en FreeCAD
	# Engrane Motor
	App.getDocument("gear").Part__Feature003.Placement=App.Placement(App.Vector(0,0,0), App.Rotation(phi0,0,0), App.Vector(0,0,0)) 
	# Engrane Conducido
	App.getDocument("gear").Part__Feature001.Placement=App.Placement(App.Vector(-45,0,0), App.Rotation(-phi0*(12.0/24.0)-7.5,0,0), App.Vector(0,0,0)) 




#Timer utilizado para evitar que el programa se congele
timer=QtCore.QTimer()
timer.timeout.connect(circulo) 
timer.start(10)
