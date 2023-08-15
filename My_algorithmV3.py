import numpy as np
from gpiozero import LED , Button , Motor , Robot , DistanceSensor
from pyamaze import maze , COLOR ,agent
from i2clibraries import i2c_hmc5883l
 



Maze = maze(5,5)
Maze.CreateMaze(loopPercent = 40)
Agent = agent(Maze,footprints = True )
aaa = agent(Maze,footprints = True , color = 'red')

Maze.tracePath({aaa:Maze.path})
#Maze.run()

print(Maze.maze_map)

alpha = 0.6 #learning rate
gamma = 0.8 #discount rate
epsilon = 1 #discovery rate


actions = ['E','W','N','S']

states = (
    (1,1),(1,2),(1,3),(1,4),(1,5),
    (2,1),(2,2),(2,3),(2,4),(2,5),
    (3,1),(3,2),(3,3),(3,4),(3,5),
    (4,1),(4,2),(4,3),(4,4),(4,5),
    (5,1),(5,2),(5,3),(5,4),(5,5)
)


rewards = []




Mystart = (5,5)
Myend = (1,1)
Mypath = []
Myepochs = 10




class Car():

    def __init__(self):

        self.robot = Robot(left=(4, 14), right=(17, 18))
        self.red = LED(17)
        self.yellow = LED(17)
        self.button = Button(2)

        
    def Compass_Read():
    
        hmc5883l = i2c_hmc5883l.i2c_hmc5883l(0)
        hmc5883l.setContinuousMode()
        hmc5883l.setDeclination(4,31)
     
        return hmc5883l


    def MoveNorth(self):

        while Compass_Read() != 0 :
            
            if Compass_Read() < 0:
                self.robot.right()
            elif Compass_Read() > 0:
                self.robot.left()

        moveforward()   


    def MoveEast(self):
        while Compass_Read() != 90 :
            
            if Compass_Read() < 90:
                self.robot.right()
            elif Compass_Read() > 90:
                self.robot.left()

        moveforward() 

    def MoveWest(self):
        
        while Compass_Read() != 180 :
            
            if Compass_Read() > 180:
                self.robot.right()
            elif Compass_Read() < 180:
                self.robot.left()

        moveforward() 


    def MoveSouth(self):

        while Compass_Read() != 270 :
            
            if Compass_Read() < 270:
                self.robot.right()
            elif Compass_Read() > 270:
                self.robot.left()

        moveforward() 



class Qlearning(Car):

    def __init__(self ,epsilon , alpha , gamma , actions , states , rewards , MazeMap):
        
        self.gamma = gamma
        self.actions = actions
        self.states = states
        self.alpha = alpha
        self.rewards = rewards
        self.MazeMap = MazeMap
        self.Q = np.zeros((len(states),len(actions)))

        for a in range (25):
            MM = []
            for m in range(4):
                MM.append(self.MazeMap[states[a]][self.actions[m]])
            self.rewards.append(MM)
            print(MM)
            index = 0
            for x in self.rewards[a]:
                if x != 0:
                    if self.actions[index] == 'E':
                        if (self.states[a][0],self.states[a][1]+1) == (1,1):
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'W':
                        if (self.states[a][0],self.states[a][1]-1) == (1,1):
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'N':
                        if (self.states[a][0]-1,self.states[a][1]) == (1,1):
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'S':
                        if (self.states[a][0]+1,self.states[a][1]) == (1,1):
                            self.rewards[a][index] = 20
                index += 1      
        
        
    def train(self,start,end,epochs):
        new_rewards = self.rewards.copy()       
        end_state = self.states[self.states.index(end)]
        currentstate = self.states[self.states.index(start)]
        
        
        for i in range (epochs):

            while(currentstate != end_state):
                #print(currentstate)
                #select the action 
                SelectedAction = []
                for a in self.actions:
                    if(self.MazeMap[currentstate][a] == 1):
                        SelectedAction.append(a)   
                if (np.random.uniform(0, 1) < self.epsilon):
                    
                    action = np.random.choice(SelectedAction)

                else :
                    action = self.actions[list(self.Q[self.states.index(currentstate)]).index(np.max(self.Q[self.states.index(currentstate)]))]
                if i == 5 :
                    self.epsilon = .2
                
                

                #The next state
                if action == 'E':
                    nextstate = (currentstate[0],currentstate[1]+1)
                elif action == 'W':
                    nextstate = (currentstate[0],currentstate[1]-1)
                elif action == 'N':
                    nextstate = (currentstate[0]-1,currentstate[1])
                elif action == 'S':
                    nextstate = (currentstate[0]+1,currentstate[1])


                #Get the reward
                reward = new_rewards[self.states.index(currentstate)][self.actions.index(action)]
 
                
                #temporal difference
                td = reward + self.gamma * np.max(self.Q[self.states.index(nextstate)]) - self.Q[self.states.index(currentstate)][self.actions.index(action)]
                self.Q[self.states.index(currentstate)][self.actions.index(action)] += alpha * td
                currentstate = nextstate    
                
  

            currentstate = self.states[self.states.index(start)]    
             
        self.optimalpolicy(start,end)
        button.wait_for_press()
        self.Go(Mypath) 
        self.ComeBack(Mypath)   


    def optimalpolicy(self ,start ,end):
        path = [start]
        temploc = start
        qlearn = self.Q.copy()
        count = 0
        
        while(temploc != end):
            
            NS = self.actions[list(self.Q[self.states.index(temploc)]).index(np.max(self.Q[self.states.index(temploc)]))]
           # print(NS)
           # print(temploc)    
            #['E','W','N','S']
            if NS == self.actions[0]:
                temploc = (temploc[0],temploc[1]+1)
               # print(temploc)
            elif NS == self.actions[1]:
                temploc = (temploc[0],temploc[1]-1)
               # print(temploc)
            elif NS == self.actions[2]:
                temploc = (temploc[0]-1,temploc[1])
               # print(temploc)
            elif NS == self.actions[3]:
                temploc = (temploc[0]+1,temploc[1])
              #  print(temploc)
            path.append(temploc)
       # print(path)
        for k in path:
            Mypath.append(k)



    def Go(self,Path):
        state = Path[0]
        i = 1
        self.yellow.on()
        while state != Path[-1]:

############Dependant on the oriantation 
            NS = self.actions[list(self.Q[self.states.index(state)]).index(np.max(self.Q[self.states.index(state)]))]           
            if NS == 'E':
                    self.MoveEast()
                elif NS == 'W':
                    self.MoveWest()
                elif NS == 'N':
                    self.MoveNorth()
                elif NS == 'S':
                    self.MoveSouth()
            state = Path[i]
            i += 1        



        self.yellow.off()    

    
        

    def ComeBack(self,Path):
        self.red.on()
        state = Path[-2]
        i = -3
        while state != Path[0]:

############Dependant on the oriantation 
            NS = self.actions[list(self.Q[self.states.index(state)]).index(np.max(self.Q[self.states.index(state)]))]           
            if NS == 'E':
                    self.MoveWest()
                elif NS == 'W':
                    self.MoveEast()
                elif NS == 'N':
                    self.MoveSouth()
                elif NS == 'S':
                    self.MoveNorth()
            state = Path[i]
            i -= 1    
        self.red.off()             



        


qlearn = Qlearning(epsilon ,alpha , gamma , actions ,states, rewards , Maze.maze_map)
qlearn.train( (Mystart , Myend , Myepochs)




















 
