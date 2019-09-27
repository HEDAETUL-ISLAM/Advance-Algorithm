import random

class Environment(object):
    def __init__(self):
        # set location and conditions 0 for clean 1 for dirty
        self.locationCondition = {'A':'0', 'B': '0'}

        self.locationCondition['A'] = random.randint(0,1)
        self.locationCondition['B'] = random.randint(0,1)

class SimpleReflesVaccumeAgent(Environment):
    def __init__(self, Environment):
        print (Environment.locationCondition)
        score = 0
        vacumeLocation = random.randint(0,1) #move vacume randomly 
        
        if vacumeLocation == 0:
            print ("vaccume in randomly placed in location A")
            if Environment.locationCondition['A'] == 1:
                print ("location A is dirty")
                Environment.locationCondition['A'] = 0
                score += 1
                print( "location A has been cleaned")
                print ("moving to position B")
                score -= 1
                if Environment.locationCondition['B'] == 1:
                    print ("location B is dirty")
                    Environment.locationCondition['B'] = 0
                    score += 1
                    print ("location B has been cleaned")

            else:
                score -= 1
                print("moving location B")
                if Environment.locationCondition['B'] == 1:
                    print("location B is dirty")
                    Environment.locationCondition['B'] = 0
                    score += 1
                    print("Location B has been cleared")

        elif vacumeLocation == 1:
            print ("Vaccume randomly placed in location B")
            if Environment.locationCondition['B'] == 1:
                print("Location B is dirty")
                Environment.locationCondition['B'] = 0
                score += 1
                print("Location B has cleaned")
                score -= 1
                print("Moving location A")
                if Environment.locationCondition['A'] == 1:
                    print ("location A is dirty")
                    Environment.locationCondition['A'] = 0
                    score += 1
                    print ("location A has been cleaned")

            else:
                print("moveing to A")
                score -= 1
                if Environment.locationCondition['A'] == 1:
                    print("Location is dirty")
                    Environment.locationCondition['A'] = 0
                    score += 1
                    print("Location A has been cleaned")
        
        print (Environment.locationCondition)
        print("Performance MeasureL : " +str(score))

theEnvironment = Environment()
theVacume = SimpleReflesVaccumeAgent(theEnvironment)
