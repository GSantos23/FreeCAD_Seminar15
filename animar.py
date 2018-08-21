# Animacion de eslabones utilizando FreeCAD
# 1 Julio 2015

# execfile("/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones/animar.py")

import os
os.chdir("/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones")


import Part
from PyQt4 import QtCore, QtGui
from FreeCAD import Base
from math import cos, sin, degrees, radians
import sys

sys.path.append('/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones')
import acoplar

# Contador que delimita el numero de punto graficados por la trayectoria
counter = 0

# Carga modulo Python - C++
animation=reload(acoplar)
a=animation.acoplar()
a.inicializar()

# Crear Archivo donde se guarda la trayectoria
puntos = open("/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones/trayecto.asc","w")
puntos.close()
trayectoria = App.ActiveDocument.addObject("Points::ImportAscii","trayecto")
trayectoria.FileName = "/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones/trayecto.asc"


def circulo( ):
	global a, counter
	a.calcular()
	
	z = 0
	pi =  3.141592653589793

	# Angulos Principlaes
	phi0=degrees(a.phi0)
	phi1=degrees(a.phi1)
	phi2=degrees(a.phi2)

	# Posicion de nodos
	ax=a.ax   
	ay=a.ay 
	cx=a.cx
	cy=a.cy
	fx=a.fx
	fy=a.fy
	fx2=a.fx2
	fy2=a.fy2
	ex=a.ex
	ey=a.ey
	gx=a.gx
	gy=a.gy
	# Posiciones Fijas
	bx=a.bx
	by=a.by
	dx=a.dx
	dy=a.dy
	# Variables Virtuales
	r1=a.r1
	r2=a.r2
	r3=a.r3
	# Angulos Trgonometricos
	alfa=a.alfa
	beta=a.beta
	gamma=a.gamma
	delta=a.delta
	epsilon=a.epsilon
	kappa=a.kappa


	#print "epsilon = ", th0
	
	# Movimiento de eslabones en FreeCAD
	# Eslabon L1
	App.getDocument("pata").Part__Feature.Placement=App.Placement(App.Vector(0,0,0), App.Rotation(phi0,0,0), App.Vector(0,0,0))
	# Eslabon L2
	App.getDocument("pata").Part__Feature001.Placement=App.Placement(App.Vector(bx,by,0), App.Rotation(phi1,0,0), App.Vector(0,0,0)) 
	# Eslabon L3
	App.getDocument("pata").Part__Feature002.Placement=App.Placement(App.Vector(ax,ay,10), App.Rotation(phi2,0,0), App.Vector(0,0,0)) 
	# Eslabon L4
	App.getDocument("pata").Part__Feature003.Placement=App.Placement(App.Vector(fx,fy,10), App.Rotation(phi2,0,0), App.Vector(0,0,0)) 
		
	########################################################################################################################################
	# Trayectoria de eslabones utilizando nube de puntos
	
	if(counter%1 == 0 and counter <=3600):
		puntos = open("/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones/trayecto.asc","a")
		print >> puntos, fx2, fy2, z
		puntos.close() 
		if( counter%36 == 0 ):
			App.getDocument("pata").removeObject("trayecto")
			trayectoria = App.ActiveDocument.addObject("Points::ImportAscii","trayecto")
			trayectoria.FileName = "/home/gerson/Thesis/Klann_FreeCAD/New_Klann/Klann_iostream/extremidad/Eslabones/trayecto.asc"
			FreeCADGui.getDocument("pata").getObject("trayecto").PointSize = 3.00
			FreeCADGui.getDocument("pata").getObject("trayecto").ShapeColor = (1.00,0.00,0.00) 
			App.ActiveDocument.recompute()
	counter=counter+1
	
# Timer utilizado para evitar que el programa se congele
timer=QtCore.QTimer()
timer.timeout.connect(circulo) 
timer.start()
