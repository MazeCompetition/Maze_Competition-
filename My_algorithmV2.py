import numpy as np
from gpiozero import LED , Button , Motor , Robot , DistanceSensor
from i2clibraries import i2c_hmc5883l
 

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


rewards = [
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0],
    [0,0,0,0]
    ]

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

        while self.Compass_Read() != 0 :
            
            if self.Compass_Read() < 0:
                self.robot.right()
            elif self.Compass_Read() > 0:
                self.robot.left()

        moveforward()   


    def MoveEast(self):
        while self.Compass_Read() != 90 :
            
            if self.Compass_Read() < 90:
                self.robot.right()
            elif self.Compass_Read() > 90:
                self.robot.left()

        moveforward() 

    def MoveWest(self):
        
        while self.Compass_Read() != 180 :
            
            if self.Compass_Read() > 180:
                self.robot.right()
            elif self.Compass_Read() < 180:
                self.robot.left()

        moveforward() 


    def MoveSouth(self):

        while self.Compass_Read() != 270 :
            
            if self.Compass_Read() < 270:
                self.robot.right()
            elif self.Compass_Read() > 270:
                self.robot.left()

        moveforward() 



class Qlearning(Car):

    def __init__(self ,epsilon, alpha , gamma , actions , states , rewards):

        super.__init__()
        
        self.gamma = gamma
        self.actions = actions
        self.states = states
        self.alpha = alpha
        self.rewards = rewards
        self.epsilon = epsilon
        self.Q = np.zeros((len(states),len(actions)))

              
        
        
    def train(self,start,end,epochs):
        new_rewards = self.rewards.copy()       
        end_state = self.states[self.states.index(end)]
        currentstate = self.states[self.states.index(start)]
        
        for a in range (25):
            index = 0
            for x in new_rewards[a]:
                if x != 0:

####################Dependant on the oriantation
                    if self.actions[index] == 'E':
                        if (self.states[a][0],self.states[a][1]+1) == end:
                            self.new_rewards[a][index] = 20
                    elif self.actions[index] == 'W':
                        if (self.states[a][0],self.states[a][1]-1) == end:
                            self.new_rewards[a][index] = 20
                    elif self.actions[index] == 'N':
                        if (self.states[a][0]-1,self.states[a][1]) == end:
                            self.new_rewards[a][index] = 20
                    elif self.actions[index] == 'S':
                        if (self.states[a][0]+1,self.states[a][1]) == end:
                            self.new_rewards[a][index] = 20
                index += 1


        for i in range (epochs):

            self.button.wait_for_press()
            self.red.on()
            while(currentstate != end_state):
                #print(currentstate)
                #select the action 
                SelectedAction = []
                for a in self.actions:
                    if(self.rewards[currentstate][a] == 1):
                        SelectedAction.append(a)   
                if (np.random.uniform(0, 1) < self.epsilon):
                    
                    action = np.random.choice(SelectedAction)

                else :
                    action = self.actions[list(self.Q[self.states.index(currentstate)]).index(np.max(self.Q[self.states.index(currentstate)]))]
                if i == 5 :
                    self.epsilon = .2
                
                    
    
                #The next state
################Dependant on the oriantation
                if action == 'E':
                    nextstate = (currentstate[0],currentstate[1]+1)
                    self.MoveEast()
                elif action == 'W':
                    nextstate = (currentstate[0],currentstate[1]-1)
                    self.MoveWest()
                elif action == 'N':
                    nextstate = (currentstate[0]-1,currentstate[1])
                    self.MoveNorth()
                elif action == 'S':
                    nextstate = (currentstate[0]+1,currentstate[1])
                    self.MoveSouth()



                #Get the reward
                reward = new_rewards[self.states.index(currentstate)][self.actions.index(action)]
        
                           
                #temporal difference
                td = reward + self.gamma * np.max(self.Q[self.states.index(nextstate)]) - self.Q[self.states.index(currentstate)][self.actions.index(action)]
                self.Q[self.states.index(currentstate)][self.actions.index(action)] += alpha * td
                currentstate = nextstate    

  

            currentstate = self.states[self.states.index(start)]
            self.red.off()      
        self.optimalpolicy(start,end)
        button.wait_for_press()
        self.Go(Mypath) 
        self.ComeBack(Mypath)
        print("Done")


    def optimalpolicy(self ,start ,end):
        self.yellow.on()
        path = [start]
        temploc = start
        qlearn = self.Q.copy()
        count = 0
        
        while(temploc != end):
            
            NS = self.actions[list(self.Q[self.states.index(temploc)]).index(np.max(self.Q[self.states.index(temploc)]))]
           # print(NS)
           # print(temploc)    
            #['E','W','N','S']
############Dependant on the oriantation            
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
        self.yellow.off()

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





        


qlearn = Qlearning(epsilon , alpha , gamma , actions ,states, rewards)
qlearn.train(Mystart , Myend , Myepochs)






