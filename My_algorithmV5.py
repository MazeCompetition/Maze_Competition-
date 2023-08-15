import numpy as np
from gpiozero import LED , Button , Motor , Robot , DistanceSensor
from time import sleep
 

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



    def north_updater(self , usual_action , north):
        #this function will return new north depend on the previouse north and taken action
        #parameters :
        # usual_action: taked action , north: north at the usual action
        #return : 
        # updated north after taking usual_action with the north 
        #if action is B or F north does not change
        if north == 'F' and usual_action == 'F' :
            new_north = 'F'
        if north == 'F' and usual_action == 'B' :
            new_north = 'B'
        if north == 'F' and usual_action == 'R' :
            new_north = 'L'
        if north == 'F' and usual_action == 'L' :
            new_north = 'R'
        ###############################################
        if north == 'B' and usual_action == 'F' :
            new_north = 'B'
        if north == 'B' and usual_action == 'B' :
            new_north = 'F'
        if north == 'B' and usual_action == 'R' :
            new_north = 'R'
        if north == 'B' and usual_action == 'L' :
            new_north = 'L'
        ##################################################
        if north == 'R' and usual_action == 'F' :
            new_north = 'R'
        if north == 'R' and usual_action == 'B' :
            new_north = 'L'
        if north == 'R' and usual_action == 'R' :
            new_north = 'F'
        if north == 'R' and usual_action == 'L' :
            new_north = 'B'
        ################################################
        if north == 'L' and usual_action == 'F' :
            new_north = 'L'
        if north == 'L' and usual_action == 'B' :
            new_north = 'R'
        if north == 'L' and usual_action == 'R' :
            new_north = 'B'
        if north == 'L' and usual_action == 'L' :
            new_north = 'F'
            
        return new_north  


    def reverse_direction(self , direction):
        if direction == 'R':
            return 'L'
        elif direction == 'L':
            return 'R'
        elif direction == 'F':
            return 'B'
        elif direction == 'B':
            return 'F'


def compass_direction_to_usual_direction(self , comp_action,north = 'F'):
    """
    this functtion will convert from ['E','N','S','W'] to ['F','B','L' ,'R']
    parameters:
        # it will recieve compase direction and
        # where is the north of robot for example may be the north is in front or backward 
        or right or left of the robot
    return:
        #usual direction which is one of ['F','B','L' ,'R']
        #new north direction 
    """
    #IMPORTANT NOTE : CODE DEPEND ON THE FOLLOWING ORDER OF COMP_ACTION AND USUAL_ACTION LISTS
    #DO NOT CHANGE THE FOLLOWING ORDER
    comp_actions = np.array(['E','W','N','S'])
    usual_actions = np.array(['R','L','F','B' ])
    
    if north == 'F':
        ##same index
        usual_action = usual_actions[np.where(comp_actions == comp_action)[0][0]]
        
        
    elif north == 'B':
        usual_action = usual_actions[np.where(comp_actions == comp_action)[0][0]]
        usual_action = reverse_direction(usual_action)
        
    elif north == 'R':
        if comp_action == 'N' or comp_action == 'S':
            usual_action = usual_actions[np.where(comp_actions == comp_action)[0][0]-2]
            
        elif comp_action == 'W':
            usual_action = 'F'
            
        elif comp_action == 'E':
            usual_action = 'B'
    elif north == 'L':
        if comp_action == 'N':
            usual_action = 'L'
        elif comp_action == 'S':
            usual_action = 'R'
        elif comp_action == 'E':
            usual_action = 'F'
        elif comp_action == 'W':
            usual_action = 'B'
    
    new_north = north_updater(usual_action , north)
    return usual_action , new_north 



    def MoveNorth(self , usaual_action):

            
       if usaual_action == 'F':
            pass
        elif usaual_action == 'B':
            self.robot.left()
            sleep(1)
        elif usaual_action == 'R':
            self.robot.right()
            sleep(1)    
        elif usaual_action == 'L':
            self.robot.left()
            sleep(1)
            
        moveforward()   


    def MoveEast(self ,usaual_action):
            
        if usaual_action == 'F':
            pass
        elif usaual_action == 'B':
            self.robot.left()
            sleep(1)
        elif usaual_action == 'R':
            self.robot.right()
            sleep(1)    
        elif usaual_action == 'L':
            self.robot.left()
            sleep(1)

        moveforward() 


    def MoveWest(self , usaual_action):
        
       if usaual_action == 'F':
            pass
        elif usaual_action == 'B':
            self.robot.left()
            sleep(1)
        elif usaual_action == 'R':
            self.robot.right()
            sleep(1)    
        elif usaual_action == 'L':
            self.robot.left()
            sleep(1)
        moveforward() 


    def MoveSouth(self , usaual_action):

       if usaual_action == 'F':
            pass
        elif usaual_action == 'B':
            self.robot.left()
            sleep(1)
        elif usaual_action == 'R':
            self.robot.right()
            sleep(1)    
        elif usaual_action == 'L':
            self.robot.left()
            sleep(1)
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
            north = 'F'
            while(currentstate != end_state):
                #print(currentstate)
                #select the action 
                SelectedAction = []
                for a in self.actions:
                    if(self.rewards[currentstate][a] == 1):
                        SelectedAction.append(a)   
                
                    
                action = np.random.choice(SelectedAction)
                
                usaual_action , north = self.compass_direction_to_usual_direction(self , comp_action,north)
                
                #The next state
################Dependant on the oriantation
                if action == 'E':
                    nextstate = (currentstate[0],currentstate[1]+1)
                    self.MoveEast(usaual_action)
                elif action == 'W':
                    nextstate = (currentstate[0],currentstate[1]-1)
                    self.MoveWest(usaual_action)
                elif action == 'N':
                    nextstate = (currentstate[0]-1,currentstate[1])
                    self.MoveNorth(usaual_action)
                elif action == 'S':
                    nextstate = (currentstate[0]+1,currentstate[1])
                    self.MoveSouth(usaual_action)



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






