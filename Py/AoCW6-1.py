class Planet(object):
    def __init__(self, identifier) :
        self.__identifier = identifier
        self.__orbits = []
        self.parent = None
        self.parents = 0

    def getIdentifier(self) :
        return self.__identifier

    def getOrbits(self) :
        return self.__orbits

    def addOrbit(self, planet) :
        self.__orbits += [planet]

    def setOrbits(self, orbits) :
        self.__orbits = orbits

def main() :
    file = open("planets.txt", "r")
    lines = file.readlines()
    data = {}
    central = None
    planetYou = None
    planetSanta = None
    
    for line in lines :
        lineData = line.split(")")
        identifierA = lineData[0]
        identifierB = lineData[1].splitlines()[0]
        planetA = getPlanet(identifierA, data)
        planetB = getPlanet(identifierB, data)

        planetB.parent = planetA
        
        if identifierA == "COM" :
            central = planetA

        if identifierA == "SAN" :
            planetSanta = planetA

        if identifierB == "SAN" :
            planetSanta = planetB

        if identifierA == "YOU" :
            planetYou = planetA

        if identifierB == "YOU" :
            planetYou = planetB
        
        planetA.addOrbit(identifierB)
        data[identifierA] = planetA
        data[identifierB] = planetB

    parentsA = getParents(planetYou)
    parentsB = getParents(planetSanta)
    sharedParent = [i for i in parentsA if i in parentsB][0]
    counter = getNumberOfNodesBetween(planetYou.parent, sharedParent) + getNumberOfNodesBetween(planetSanta.parent, sharedParent)
    print(counter)
    
def getNumberOfNodesBetween(planetA, planetB) :
    counter = 0

    while(planetA != planetB) :
        counter += 1
        planetA = planetA.parent
    
    return counter
    
def getParents(planet) :
    parents = []

    while(planet.parent != None) :
        parents += [planet.parent]
        planet = planet.parent

    return parents
    
def planetCounter(parent, data, counter) :
    for child in parent.getOrbits() :
        childPlanet = data[child]
        childPlanet.parents = parent.parents + 1
        counter = counter + childPlanet.parents
        counter = planetCounter(childPlanet, data, counter)
    return counter
    
def getPlanet(planetId, data) :
    try :
        return data[planetId]
    except :
        return Planet(planetId)
    
if __name__ == '__main__' :
    main()
