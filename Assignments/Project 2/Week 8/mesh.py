import math
from triangle import Triangle
from vertex import vertex

class Mesh:    
    def __init__(self, pts, tris):
        self.pts = pts
        self.tris = tris
        self.valences = []
        self.nvec = []
        #print("Mesh created")

    def connectAlg(self):
        """connectAlg finds neigbor Triangles of every Triangle and no. of triangles for every point

        """
        # delete old no. of triangles for every point
        self.valences.clear()
        # fill vector of no. of triangles for every point with 0
        for i in range(0, len(self.pts)):
            self.valences.append(0)
        # for every Triangle in tris find the 3 neighbor Triangles
        for t in range(0, len(self.tris)):
            for tn in range(0, len(self.tris)):
                # For first, second and third point of triangle test if it occurs in the other triangle
                test1 = (self.tris[t].iv[0]==self.tris[tn].iv[0] or self.tris[t].iv[0]==self.tris[tn].iv[1] or self.tris[t].iv[0]==self.tris[tn].iv[2])
                test2 = (self.tris[t].iv[1]==self.tris[tn].iv[0] or self.tris[t].iv[1]==self.tris[tn].iv[1] or self.tris[t].iv[1]==self.tris[tn].iv[2])
                test3 = (self.tris[t].iv[2]==self.tris[tn].iv[0] or self.tris[t].iv[2]==self.tris[tn].iv[1] or self.tris[t].iv[2]==self.tris[tn].iv[2])
                # find t0!=t containing b and c (CG21_1 page 19)
                if(test2 and test3 and not test1):
                    self.tris[t].it[0]=tn;        
                # find t1!=t containing c and a (CG21_1 page 19)
                if(test3 and test1 and not test2):
                    self.tris[t].it[1]=tn;
                # find t2!=t containing a and b (CG21_1 page 19)
                if(test1 and test2 and not test3):
                    self.tris[t].it[2]=tn;
            # increase no. of triangles for the point of the triangle
            self.valences[self.tris[t].iv[0]] += 1;
            self.valences[self.tris[t].iv[1]] += 1;
            self.valences[self.tris[t].iv[2]] += 1;
        # output results
        print("Valence list (First vertex has index 0):")
        for i in range(0, len(self.pts)):
            print("  vertex ", i, ": ", self.valences[i])
        print("Neighbor triangles of triangles (First triangle has index 0): ")
        for i in range(0, len(self.tris)):
            print("  Triangle ", i,  ": ", end=" ")
            self.tris[i].printIT()

    def createNewTriangles(self):
        """createNewTriangles calculates smaller triangles with new corners
        """
        trisnew = []
        for t in self.tris:
            # calculate middle triangle
            t2 = Triangle(t.ie[0], t.ie[1], t.ie[2])
            # calculate triangles around the middle triangle
            t0 = Triangle(t.ie[1], t.ie[0], t.iv[2])
            t1 = Triangle(t.iv[0], t.ie[2], t.ie[1])
            t3 = Triangle(t.ie[2], t.iv[1], t.ie[0])        
            trisnew.append(t0)
            trisnew.append(t1)
            trisnew.append(t2)
            trisnew.append(t3)   
        self.tris = trisnew

    def beta_n(self, n):
        """beta_n calculates beta from the number of triangles for every point

        Args:
            n (int): number of triangles for every point
        
        Return:
            float: beta

        """
        alpha = (3.0/8.0) + pow((3.0/8.0) + (1.0/4.0) * (math.cos(2.0*math.pi/n)), 2)
        beta = (8.0/5.0) * alpha - (3.0/5.0)
        return beta

    def loopSubdivisionAlg(self):
        """loopSubdivisionAlg calculates edge points according to Mr. Loop's method
        """
        # variable for new vertex
        d = vertex(0, 0, 0)
        oldPtsSize = len(self.pts)
        # matrix indices of iv
        mv = [[1, 2, 0], [2, 0, 1], [0, 1, 2]]
        # for every triangle calculate edge points
        for i in range(0, len(self.tris)):
            t = self.tris[i]
            # for the 3 edge points of a triangle
            for j in range (0, 3):
                i1 = mv[j][0]
                i2 = mv[j][1]
                i3 = mv[j][2]
                # neighbor Triangle
                n = self.tris[t.it[j]]
                # calculate edge point if index of triangle is smaller than index of neighbor
                # otherwise the edge point is already calculated
                if(i<t.it[j]):
                    # find vertex in neighbor Triangle that is not in Triangle t
                    test1 = t.iv[i1]==n.iv[0] or t.iv[i2]==n.iv[0]
                    test2 = t.iv[i1]==n.iv[1] or t.iv[i2]==n.iv[1]
                    test3 = t.iv[i1]==n.iv[2] or t.iv[i2]==n.iv[2]
                    if(not test1):
                        d = self.pts[n.iv[0]]
                    elif(not test2):
                        d = self.pts[n.iv[1]]
                    elif(not test3):
                        d = self.pts[n.iv[2]]
                    d.printXYZ
                    # with formula
                    e = (self.pts[t.iv[i3]] + self.pts[t.iv[i1]]*3 + self.pts[t.iv[i2]]*3 +d) * 0.125
                    self.tris[i].ie[j] = len(self.pts)
                    self.pts.append(e);
                    # fill ie in neighbor Triangle
                    if(i==n.it[0]):
                        self.tris[t.it[j]].ie[0] = len(self.pts)-1
                    elif(i==n.it[1]):
                        self.tris[t.it[j]].ie[1] = len(self.pts)-1
                    elif(i==n.it[2]):
                        self.tris[t.it[j]].ie[2] = len(self.pts)-1
        # output results
        print("Triangle edge vertex index: ")
        for i in range(0, len(self.tris)):
            print("  Triangle ", i,  ": ", end=" ")
            self.tris[i].printIE()
        # multiply every vertex with beta
        for i in range(0, oldPtsSize):
            n = self.valences[i] # n = valence of v_i
            beta = self.beta_n( n)
            #print("beta ", beta)
            self.pts[i] = self.pts[i]*beta
            # self.pts[i] *= beta # v_i *= beta(n)
        # vertex mask
        # for first second and third point of every triangle
        for i in range(0, len(self.tris)): 
            self.pts[self.tris[i].iv[0]] +=  ( ( (1.0 - self.beta_n(self.valences[self.tris[i].iv[0]])) / (self.valences[self.tris[i].iv[0]])) * ((self.pts[self.tris[i].ie[1]]+self.pts[self.tris[i].ie[2]]) / 2.0))
            self.pts[self.tris[i].iv[1]] +=  ( ( (1.0 - self.beta_n(self.valences[self.tris[i].iv[1]])) / (self.valences[self.tris[i].iv[1]])) * ((self.pts[self.tris[i].ie[2]]+self.pts[self.tris[i].ie[0]]) / 2.0))
            self.pts[self.tris[i].iv[2]] +=  ( ( (1.0 - self.beta_n(self.valences[self.tris[i].iv[2]])) / (self.valences[self.tris[i].iv[2]])) * ((self.pts[self.tris[i].ie[0]]+self.pts[self.tris[i].ie[1]]) / 2.0))
        self.createNewTriangles()

    def linearSubdivisionAlg(self):
        """linearSubdivisionAlg calculates edge points linear
        """

        # matrix indices of iv
        mv = [[1, 2], [2, 0], [0, 1]]
        # for every triangle calculate edge points
        for i in range(0, len(self.tris)):
            t = self.tris[i]
            # for the 3 edge points of a triangle
            for j in range (0, 3):
                i1 = mv[j][0]
                i2 = mv[j][1]
                # neigbor Triangle
                n = self.tris[t.it[j]]
                # calculate edge point if index of triangle is smaller than index of neigbor
                # otherwise the edge point is already calculated
                if(i<t.it[j]):
                    # edge vertices
                    e = (self.pts[t.iv[i1]] + self.pts[t.iv[i2]]) * 0.5;
                    self.tris[i].ie[j] = len(self.pts)
                    self.pts.append(e);
                    # fill ie in neighbor Triangle
                    if(i==n.it[0]):
                        self.tris[t.it[j]].ie[0] = len(self.pts)-1
                    elif(i==n.it[1]):
                        self.tris[t.it[j]].ie[1] = len(self.pts)-1
                    elif(i==n.it[2]):
                        self.tris[t.it[j]].ie[2] = len(self.pts)-1
        # output results
        print("Triangle edge vertex index: ")
        for i in range(0, len(self.tris)):
            print("  Triangle ", i,  ": ", end=" ")
            self.tris[i].printIE()
        self.createNewTriangles()
    

    def normalVector(self):
        """normalVector calculates normal vector of every Triangle
        """
        for i in range(0, len(self.tris)):
            # read indices
            t1 = self.tris[i].iv[0]
            t2 = self.tris[i].iv[1]
            t3 = self.tris[i].iv[2]
            # Calculate vectors of the edges
            edge1 = self.pts[t2]-self.pts[t1]
            edge2 = self.pts[t3]-self.pts[t1]
            # Calculate normal vector
            normalvec = edge1%edge2;
            # save normal vector in Triangle class
            self.tris[i].nvec = normalvec
            # save normal vector in Mesh class vector
            self.nvec.append(normalvec)

    def scaleAlg(self, factor):
        """scale whole object
        Args: 
            factor(int): calculate scalefactor
        """
        scalefactor, center = self.calculateCenter(factor)
        for i in range(0, len(self.pts)):
            scalevertex = self.pts[i] - center
            expansion =  scalevertex * scalefactor
            self.pts[i] = self.pts[i] + expansion
        
    def xscaleAlg(self, factor):
        """scale whole object in x direction
        Args: 
            factor(int): calculate scalefactor
        """
        scalefactor, center = self.calculateCenter(factor)
        for i in range(0, len(self.pts)):
            scalex = self.pts[i].xyz[0] - center.xyz[0]
            expansion =  scalex * scalefactor
            self.pts[i].xyz[0] = self.pts[i].xyz[0] + expansion

    def yscaleAlg(self, factor):
        """scale whole object in y direction
        Args: 
            factor(int): calculate scalefactor
        """
        scalefactor, center = self.calculateCenter(factor)
        for i in range(0, len(self.pts)):
            scalex = self.pts[i].xyz[1] - center.xyz[1]
            expansion =  scalex * scalefactor
            self.pts[i].xyz[1] = self.pts[i].xyz[1] + expansion

    def zscaleAlg(self, factor):
        """scale whole object in z direction
        Args: 
            factor(int): calculate scalefactor
        """
        scalefactor, center = self.calculateCenter(factor)
        for i in range(0, len(self.pts)):
            scalex = self.pts[i].xyz[2] - center.xyz[2]
            expansion =  scalex * scalefactor
            self.pts[i].xyz[2] = self.pts[i].xyz[2] + expansion

    def maniAlg(self, factor, point):
        """manipulate one point
        Args: 
            factor(int): calculate scalefactor
            point(int): point to be manipulated
        """
        scalefactor, center = self.calculateCenter(factor)
        scalevertex = self.pts[point] - center
        expansion =  scalevertex * scalefactor
        self.pts[point] = self.pts[point] + expansion

    def xmaniAlg(self, factor, point):
        """manipulate one point in x direction
        Args: 
            factor(int): calculate scalefactor
            point(int): point to be manipulated
        """
        scalefactor, center = self.calculateCenter(factor)
        scalex = self.pts[point].xyz[0] - center.xyz[0]
        expansion =  scalex * scalefactor
        self.pts[point].xyz[0] = self.pts[point].xyz[0] + expansion

    def ymaniAlg(self, factor, point):
        """manipulate one point in y direction
        Args: 
            factor(int): calculate scalefactor
            point(int): point to be manipulated
        """
        scalefactor, center = self.calculateCenter(factor)
        scalex = self.pts[point].xyz[1] - center.xyz[1]
        expansion =  scalex * scalefactor
        self.pts[point].xyz[1] = self.pts[point].xyz[1] + expansion

    def zmaniAlg(self, factor, point):
        """manipulate one point in z direction
        Args: 
            factor(int): calculate scalefactor
            point(int): point to be manipulated
        """
        scalefactor, center = self.calculateCenter(factor)
        scalex = self.pts[point].xyz[2] - center.xyz[2]
        expansion =  scalex * scalefactor
        self.pts[point].xyz[2] = self.pts[point].xyz[2] + expansion

    def calculateCenter(self, factor):
        """calculate center of an object and scalefactor
        Args:
            factor(int): factor to calculate scalefactor
        Return:
            float: scalefactor
            vertex: center
        """
        if (factor > 0):
            scalefactor = factor/100.0 -1
            center = vertex(0, 0, 0)
            for v in self.pts:
                center += v
            center = center / len(self.pts)            
        else:
            print("Input must be greater than 0!")
            scalefactor = 1
        return scalefactor, center

        







        
        

