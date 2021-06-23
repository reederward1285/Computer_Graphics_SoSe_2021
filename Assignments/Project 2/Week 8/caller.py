from triangle import Triangle
from vertex import Vertex
from mesh import Mesh

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib import style

class Caller:

    def __init__(self):
        self.tris = []
        self.points = []

        self.point0 = Vertex(0.0, 0.0, 0.0)
        self.points.append(self.point0)
        self.point1 = Vertex(8.0, 0.0, 0.0)
        self.points.append(self.point1)
        self.point2 = Vertex(0.0, 8.0, 0.0)
        self.points.append(self.point2)
        self.point3 = Vertex(0.0, 0.0, 8.0)
        self.points.append(self.point3)
        for point in self.points:
            point.printXYZ()

        self.tri0 = Triangle(0, 1, 3)
        self.tris.append(self.tri0)
        self.tri1 = Triangle(1, 2, 3)
        self.tris.append(self.tri1)
        self.tri2 = Triangle(2, 0, 3)
        self.tris.append(self.tri2)
        self.tri3 = Triangle(2, 1, 0)
        self.tris.append(self.tri3)    
        for tri in self.tris:
            tri.printIV()

        self.mesh = Mesh(self.points, self.tris)

    def scaleMesh(self, factor, axyz):
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

    def showObject(self):
        fig = plt.figure(figsize=(6,6))
        ax = fig.add_subplot(111, projection='3d')
        for i in range(0, len(self.mesh.tris)):
            x1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[0]])
            y1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[1]])
            z1=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[2]])  
            ax.scatter(x1,y1,z1)#
            ax.text(self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0],self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1],self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2],  '%s' % (str(self.mesh.tris[i].iv[0])), size=10, zorder=1,  color='k')
            x2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[0], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[0]])
            y2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[1], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[1]])
            z2=np.array([self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[1]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[2]].xyz[2], self.mesh.pts[self.mesh.tris[i].iv[0]].xyz[2]]) 
            ax.plot(x2, y2, z2, color = 'g')
            # create vertices from points
            verts = [list(zip(x1, y1, z1))]
            # create 3d polygons and specify parameters
            srf = Poly3DCollection(verts, alpha=.75, facecolor='#800000')
            # add polygon to the figure
            plt.gca().add_collection3d(srf)
        plt.show()

    #def updateObject(self):
        #plt.draw()