from triangle import Triangle
from vertex import vertex
from mesh import Mesh
import re
import numpy as np

import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib import style
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

from PyQt5 import QtCore, QtWidgets
from  PyQt5.QtWidgets import QSizePolicy
import sys


class ModellingCaller(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = plt.figure(figsize=(6,6))
        self.axes = fig.add_subplot(111, projection='3d')
        
        self.axes.set_xlabel('X axis')
        self.axes.set_ylabel('Y axis')
        self.axes.set_zlabel('Z axis')

        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        # internal modellingCaller values
        self.tris = []
        self.points = []

    def ReadBlend(self, fname):
        """imports an OBJ file, and populates tris and points
        """
        print("filename",fname)
        file = open(fname, "r")

        currentLine = file.readline()

        while (currentLine):


            # parse out numbers from the string
            numbers = re.findall(r'-?\d+(?:\.\d+)?', currentLine)

            # find 'v' character and populate vertex information
            #currentLine = char(currentLine)
            if (currentLine[0] == "v" and  currentLine[1] == " "):


                #print(currentLine[0])
                # make a new vertex object out of it
                self.newVertex = vertex(float(numbers[0]), float(numbers[1]), float(numbers[2]))
                self.points.append(self.newVertex)
                                
            # find 'f' character and populate face information
            elif (currentLine[0] == "f"):
                #print(numbers)
                self.newTriangle = Triangle(int(numbers[0])-1, int(numbers[3])-1, int(numbers[6])-1)
                self.tris.append(self.newTriangle)

            currentLine = file.readline()

        for point in self.points:
            point.printXYZ()

        for tri in self.tris:
            tri.printIV()

    def createMesh(self):
        """...import...
        """
        #! must be replaced by importcode

        # create points and safe in list
        # point0 = vertex(0.0, 0.0, 0.0)
        # self.points.append(self.point0)
        # point1 = vertex(8.0, 0.0, 0.0)
        # self.points.append(self.point1)
        # point2 = vertex(0.0, 8.0, 0.0)
        # self.points.append(self.point2)
        # point3 = vertex(0.0, 0.0, 8.0)
        # self.points.append(self.point3)
        # for point in self.points:
        #     point.printXYZ()

        # create triangles and safe in list
        # tri0 = Triangle(0, 1, 3)
        # self.tris.append(self.tri0)
        # tri1 = Triangle(1, 2, 3)
        # self.tris.append(self.tri1)
        # tri2 = Triangle(2, 0, 3)
        # self.tris.append(self.tri2)
        # tri3 = Triangle(2, 1, 0)
        # self.tris.append(self.tri3)    
        # for tri in self.tris:
        #     tri.printIV()

        self.mesh = Mesh(self.points, self.tris)

    def scaleMesh(self, factor, axyz):
        """scale Object (all; x, y or z coordinates)
        Args: 
            factor(float): calculate scalefactor
            axyz(int): all; x, y or z coordinates
        """
        self.factor = factor
        self.axyz = axyz
        print(self.factor, self.axyz)
        if(self.axyz == 0):
            self.mesh.scaleAlg(float(self.factor))
        elif(self.axyz == 1):
            self.mesh.xscaleAlg(float(self.factor))
        elif(self.axyz == 2):
            self.mesh.yscaleAlg(float(self.factor))
        elif(self.axyz == 3):
            self.mesh.zscaleAlg(float(self.factor))
        else:
            print("INCORRECT INPUT")

    def subMesh(self, insertAlg, insertQuantity):
        """subdivide object (linear or loop)
        Args:
            insertAlg(int): linear or loop
            insertQuantity(int): number, how often the subdivision algorithm should be performed
        """
        self.insertAlg = insertAlg
        self.insertQuantity = insertQuantity
        iQ = int(insertQuantity)
        if(iQ > 0):
            if(self.insertAlg == 1):
                for i in range(0, iQ):
                    print(" ")
                    print("Loop: ", i+1)
                    self.mesh.connectAlg()
                    self.mesh.loopSubdivisionAlg()
                self.mesh.normalVector()
                #print("loop")
            elif(self.insertAlg == 0):
                for i in range(0, iQ):
                    print(" ")
                    print("Loop: ", i+1)
                    self.mesh.connectAlg()
                    self.mesh.linearSubdivisionAlg()
                self.mesh.normalVector()
                #print("linear")
            else:
                print("INCORRECT INPUT")

    def maniMesh(self, axyz, factor, point):
        """manipulate one point (in all, x, y or z direction)
        Args: 
            factor(float): calculate scalefactor
            axyz(int): all; x, y or z coordinates
            point(int): point to be manipulated
        """
        self.axyz = axyz
        self.factor = factor
        self.point = point
        print(self.factor, self.axyz, self.point)
        if(self.axyz == 0):
            self.mesh.maniAlg(float(self.factor), int(self.point))
        elif(self.axyz == 1):
            self.mesh.xmaniAlg(float(self.factor), int(self.point))
        elif(self.axyz == 2):
            self.mesh.ymaniAlg(float(self.factor), int(self.point))
        elif(self.axyz == 3):
            self.mesh.zmaniAlg(float(self.factor), int(self.point))
        else:
            print("INCORRECT INPUT")

    def showObject(self):
        """show an object in a coordinate system
        """

        plt.clf()

        #calculate axis length
        h = self.highestPoint()
        l = self.lowestPoint() 
        d = (h - l) / 10
        h = h + d
        l = l - d

        #self.fig = plt.figure(figsize=(6,6))
        ax = self.figure.add_subplot(111, projection='3d')

        for i in range(0, len(self.mesh.tris)):

            # draw points
            x1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[0]])
            y1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[1]])
            z1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[2]])  
            ax.scatter(x1,y1,z1)

            # draw lines
            ax.text(self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0],self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1],self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2],  '%s' % (str(self.mesh.tris[i].iv[0])), size=10, zorder=1,  color='k')
            x2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0]])
            y2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1]])
            z2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2]]) 
            ax.plot(x2, y2, z2, color = 'g')

            # draw surfaces
            # create vertices from points
            verts = [list(zip(x1, y1, z1))]
            # create 3d polygons and specify parameters
            srf = Poly3DCollection(verts, alpha=.75, facecolor='#800000')
            # add polygon to the figure
            plt.gca().add_collection3d(srf)

            # labeling
            ax.set_xlim(l, h)
            ax.set_ylim(l, h)
            ax.set_zlim(l, h)
            ax.set_xlabel('X axis')
            ax.set_ylabel('Y axis')
            ax.set_zlabel('Z axis')
            
        plt.draw()

    def highestPoint(self):
        """find highest point
        """
        h = -100000
        for p in self.mesh.pts:
            if(p.xyz[0]>h):
                h = p.xyz[0]
            if(p.xyz[1]>h):
                h = p.xyz[1]
            if(p.xyz[2]>h):
                h = p.xyz[2]
        return h

    def lowestPoint(self):
        """find lowest point
        """
        l = 100000
        for p in self.mesh.pts:
            if(p.xyz[0]<l):
                l = p.xyz[0]
            if(p.xyz[1]<l):
                l = p.xyz[1]
            if(p.xyz[2]<l):
                l = p.xyz[2]
        return l


    #def updateObject(self):
        #plt.draw()