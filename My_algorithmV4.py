import numpy as np
import gpiozero
from pyamaze import maze , COLOR ,agent




Myend = (1,1)
Mystart = (5,5)


Maze = maze(5,5)
Maze.CreateMaze(loopPercent = 40 )
Agent = agent(Maze,footprints = True )


aaa = agent(Maze,footprints = True , color = 'red')

Maze.tracePath({aaa:Maze.path})


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




Mypath = []


class Qlearning():

    def __init__(self ,epsilon , alpha , gamma , actions , states , rewards , MazeMap):
        
        self.gamma = gamma
        self.actions = actions
        self.states = states
        self.alpha = alpha
        self.rewards = rewards
        self.MazeMap = MazeMap
        self.Q = np.zeros((len(states),len(actions)))
        self.epsilon = epsilon


        for a in range (25):
            MM = []
            for m in range(4):
                MM.append(self.MazeMap[states[a]][self.actions[m]])
            self.rewards.append(MM)
            index = 0
            for x in self.rewards[a]:
                if x != 0:
                    if self.actions[index] == 'E':
                        if (self.states[a][0],self.states[a][1]+1) == Myend:
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'W':
                        if (self.states[a][0],self.states[a][1]-1) == Myend:
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'N':
                        if (self.states[a][0]-1,self.states[a][1]) == Myend:
                            self.rewards[a][index] = 20
                    elif self.actions[index] == 'S':
                        if (self.states[a][0]+1,self.states[a][1]) == Myend:
                            self.rewards[a][index] = 20
                index += 1      
        
        
    def train(self,start,end,epochs):
        new_rewards = self.rewards.copy()       
        end_state = self.states[self.states.index(end)]
        currentstate = self.states[self.states.index(start)]
        
        
        for i in range (epochs):
            count = 0 
            while(currentstate != end_state):
                
                #print(currentstate)
                #select the action
                
                SelectedAction = []
                for a in self.actions:
                    if(self.MazeMap[currentstate][a] == 1):
                        SelectedAction.append(a)


                if (np.random.uniform(0, 1) < self.epsilon):
                    
                    action = np.random.choice(SelectedAction)
                    nextaction = np.random.choice(SelectedAction)

                else :
                    nextaction = self.actions[list(self.Q[self.states.index(currentstate)]).index(np.max(self.Q[self.states.index(currentstate)]))]
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

                predict =  self.Q[self.states.index(currentstate)][self.actions.index(action)]
                target = reward + self.gamma * self.Q[self.states.index(nextstate)][self.actions.index(nextaction)]

                
                self.Q[self.states.index(currentstate)][self.actions.index(action)] += alpha * (target - predict)
                currentstate = nextstate    
                count += 1
  

            currentstate = self.states[self.states.index(start)]    
            print(count)
        print(self.Q)    
        self.optimalpolicy(start,end)   
    

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



        


qlearn = Qlearning(epsilon ,alpha , gamma , actions ,states, rewards , Maze.maze_map)
qlearn.train( Mystart , Myend , 10)


print("Mypath" , Mypath)    
Maze.tracePath({Agent:Mypath})
Maze.run()


















 
