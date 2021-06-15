from PySide6.QtGui import QOpenGLExtraFunctions, QOpenGLFunctions
from triangle import Triangle
from vertex import Vertex
from mesh import Mesh

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib import style



if __name__ == "__main__":
    
    tris = []
    points = []

    point0 = Vertex(0.0, 0.0, 0.0)
    points.append(point0)
    point1 = Vertex(8.0, 0.0, 0.0)
    points.append(point1)
    point2 = Vertex(0.0, 8.0, 0.0)
    points.append(point2)
    point3 = Vertex(0.0, 0.0, 8.0)
    points.append(point3)
    for point in points:
        point.printXYZ()

    tri0 = Triangle(0, 1, 3)
    tris.append(tri0)
    tri1 = Triangle(1, 2, 3)
    tris.append(tri1)
    tri2 = Triangle(2, 0, 3)
    tris.append(tri2)
    tri3 = Triangle(2, 1, 0)
    tris.append(tri3)    
    for tri in tris:
        tri.printIV()

    mesh = Mesh(points, tris)
    insertAlg = input("Which algorithm should be used? (o for loop, i for linear) ")
    insertQuantity = input("How often should the subdivision algorithm be performed? ")
    iQ = int(insertQuantity)
    if(insertAlg == "o"):
        for i in range(0, iQ):
            print(" ")
            print("Loop: ", i+1)
            mesh.connectAlg()
            mesh.loopSubdivisionAlg()
        mesh.normalVector()
        #print("loop")
    elif(insertAlg == "i"):
        for i in range(0, iQ):
            print(" ")
            print("Loop: ", i+1)
            mesh.connectAlg()
            mesh.linearSubdivisionAlg()
        mesh.normalVector()
        #print("linear")
    else:
        print("INCORRECT INPUT")

    p1 = Vertex(1.0, 1.0, 1.0)
    p2 = Vertex(1.0, 2.0, 1.0)
    p3 = Vertex(1.0, 1.0, 2.0)
    p4 = Vertex(2.0, 2.0, 2.0)
    ps = []
    ps.append(p1)
    ps.append(p2)
    ps.append(p3)
    ps.append(p4)
    ts = []
    t0 = Triangle(0, 1, 3)
    ts.append(t0)
    t1 = Triangle(1, 2, 3)
    ts.append(t1)
    t2 = Triangle(2, 0, 3)
    ts.append(t2)
    t3 = Triangle(2, 1, 0)
    ts.append(t3)   
    mesh2 = Mesh(ps, ts)

    fig = plt.figure(figsize=(6,6))
    ax = fig.add_subplot(111, projection='3d')
    for tri in mesh.tris:
        x1=np.array([mesh.pts[tri.iv[0]].xyz[0], mesh.pts[tri.iv[1]].xyz[0], mesh.pts[tri.iv[2]].xyz[0]])
        y1=np.array([mesh.pts[tri.iv[0]].xyz[1], mesh.pts[tri.iv[1]].xyz[1], mesh.pts[tri.iv[2]].xyz[1]])
        z1=np.array([mesh.pts[tri.iv[0]].xyz[2], mesh.pts[tri.iv[1]].xyz[2], mesh.pts[tri.iv[2]].xyz[2]])  
        ax.scatter(x1,y1,z1)#
        x2=np.array([mesh.pts[tri.iv[0]].xyz[0], mesh.pts[tri.iv[1]].xyz[0], mesh.pts[tri.iv[2]].xyz[0], mesh.pts[tri.iv[0]].xyz[0]])
        y2=np.array([mesh.pts[tri.iv[0]].xyz[1], mesh.pts[tri.iv[1]].xyz[1], mesh.pts[tri.iv[2]].xyz[1], mesh.pts[tri.iv[0]].xyz[1]])
        z2=np.array([mesh.pts[tri.iv[0]].xyz[2], mesh.pts[tri.iv[1]].xyz[2], mesh.pts[tri.iv[2]].xyz[2], mesh.pts[tri.iv[0]].xyz[2]]) 
        ax.plot(x2, y2, z2, color = 'g')
        # create vertices from points
        verts = [list(zip(x1, y1, z1))]
        # create 3d polygons and specify parameters
        srf = Poly3DCollection(verts, alpha=.75, facecolor='#800000')
        # add polygon to the figure
        plt.gca().add_collection3d(srf)
    plt.show()




    

    




        


    
