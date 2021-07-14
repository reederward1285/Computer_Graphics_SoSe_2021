__author__ = "David Melamend, Reeder Ward, Majbrit Schoettner"
__email__ = "dmelamed@stud.hs-bremen.de, rward@stud.hs-bremen.de, mshoettner@stud.hs-bremen.de"
__title__ = "Implement Toolchain for .OBJ Objects in PyQt5 GUI to Create a 3D Modelling Software"
__course__ = "Computer Graphics"

class Triangle:    
    def __init__(self, i, j, k):
        self.iv = [int(i), int(j), int(k)]
        self.it = [0, 0, 0]
        self.ie = [0, 0, 0]
        #print("Triangle created")

    # print indices of vertices
    def printIV(self):
        print("iv = [ ", self.iv[0],"; ", self.iv[1],"; ", self.iv[2]," ]")

    # print indices of neighbor triangles
    def printIT(self):
        print("it = [ ", self.it[0],"; ", self.it[1],"; ", self.it[2]," ]")

    # print indices of edges
    def printIE(self):
        print("ie = [ ", self.ie[0],"; ", self.ie[1],"; ", self.ie[2]," ]")


