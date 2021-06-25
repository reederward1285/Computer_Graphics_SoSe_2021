from vertex import vertex
import re

class readObj:
    def __init__(self, Points, Tris):
        super().__init__()
        self.Points = Points
        self.Tris = Tris

    @staticmethod
    def ReadBlend(self, fname):
        vectors = []
        tris = []


        file = open(fname, "r")

        currentLine = file.readline()

        while (currentLine):
            # sort into vertices and faces
            if (currentLine.find("v", 0, len(currentLine)) != -1):
                #vectors.append(currentLine)
                #self.Points.append()
                #numbers = [double(word) for word in currentLine.split() if word.isdigit()]
                
                numbers = re.findall(r'\d+(?:\.\d+)?', currentLine)
                testObj = vertex(0.0, 0.0, 0.0)
                newVertex = vertex(float(numbers[0]), float(numbers[1]), float(numbers[2]))
                self.Points.append(newVertex)
                                
            elif (currentLine.find("f", 0, len(currentLine)) != -1):
                self.Tris.append(currentLine)

            currentLine = file.readline()

    def getPoints():
        return self.Points

    def getTris():
        return self.Tris