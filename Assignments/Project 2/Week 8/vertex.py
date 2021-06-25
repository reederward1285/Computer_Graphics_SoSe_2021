class vertex:    
    def __init__(self, x, y, z):
        self.xyz = [float(x), float(y), float(z)]
        #print("Vertex created")

    # print coordinates
    def printXYZ(self):
        print("xyz = [ ", self.xyz[0],"; ", self.xyz[1],"; ", self.xyz[2]," ]")

    # +
    def __add__(self, other):
        return Vertex(self.xyz[0] + other.xyz[0], self.xyz[1] + other.xyz[1], self.xyz[2] + other.xyz[2])

    # -
    def __sub__(self, other):
        return Vertex(self.xyz[0] - other.xyz[0], self.xyz[1] - other.xyz[1], self.xyz[2] - other.xyz[2])

    # +=
    def __iadd__(self, other):
        self.xyz[0] = self.xyz[0] + other.xyz[0]
        self.xyz[1] = self.xyz[1] + other.xyz[1]
        self.xyz[2] = self.xyz[2] + other.xyz[2]
        return self

    # -=
    def __isub__(self, other):
        self.xyz[0] = self.xyz[0] - other.xyz[0]
        self.xyz[1] = self.xyz[1] - other.xyz[1]
        self.xyz[2] = self.xyz[2] - other.xyz[2]
        return self

    # *=
    def __imul__(self, other):
        self.xyz[0] = self.xyz[0] * other
        self.xyz[1] = self.xyz[1] * other
        self.xyz[2] = self.xyz[2] * other
        return self

    # %
    def __mod__(self, other):
        return Vertex(self.xyz[1]*other.xyz[2] - self.xyz[2]*other.xyz[1], self.xyz[2]*other.xyz[0] - self.xyz[0]*other.xyz[2], self.xyz[0]*other.xyz[1] - self.xyz[1]*other.xyz[0])

    # /
    def __truediv__(self, other):
        return Vertex(self.xyz[0]/other, self.xyz[1]/other, self.xyz[2]/other)

    # * 
    def __mul__(self, other):
        if type(other) == Vertex:
            result = self.xyz[0] * other.xyz[0] + self.xyz[1] * other.xyz[1] + self.xyz[2] * other.xyz[2]
        else:
            result =Vertex(other*self.xyz[0], other*self.xyz[1], other*self.xyz[2])
        return result
    def __rmul__(self, other):
        return Vertex.__mul__(self,other) 



