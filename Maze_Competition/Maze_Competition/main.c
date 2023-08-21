/*
 * DRIVERS.c
 *
 * Created: 2/6/2023 4:11:34 PM
 * Author : Bishoy Refaat
 */ 


//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "ATMEGA32.h"
#include "GPIO.h"
#include "LCD_DRIVER.h"
#include "TIMERs.h"
#include "DC_Motor.h"
#include "Ultrasonic.h"
#include <time.h>
#include <stdlib.h>

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|

#define length   5 
#define width    5


//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|

// this array will be used to track the paths that robot will take 
// it will contain 0 == not visited ... 1 == visitet once  ... 2 == visited twice 
uint8_t  maze_visited_status[length][width] = {0};
uint8_t  track_memory[length*width][2] = {0} , track_counter=0 , End_of_maze = 0 ;
uint8_t  current_state[2] = {0};
uint8_t  Previous_state[2] = {0};


uint8_t comp_actions[4] = {'E','W','N','S'};
uint8_t actions[4] = {'E','W','N','S'};

uint8_t usual_actions[4] = {'R','L','F','B'};
uint8_t	new_north = 'F' , usual_action , comp_action;
	
uint8_t state[3]= {0};	



//		|-----------------------------------------------|
//		|=============FUNCTIONS DECLERATIONS============|
//		|-----------------------------------------------|

void LCDInit();
void get_status(void);
uint8_t get_random_action(uint8_t upper );
uint8_t index_of(uint8_t * arr , uint8_t element);
void take_action (void);
uint8_t get_index(int8_t in);
void current_state_update(uint8_t action );
uint8_t north_updater(uint8_t usual_action ,uint8_t north);
uint8_t reverse_usaual_direction(uint8_t direction);
uint8_t reverse_Copass_direction(uint8_t direction);
void compass_direction_to_usual_direction(uint8_t comp_action,uint8_t north );
void usual_direction_to_compass_direction(uint8_t usual_action,uint8_t north);
uint8_t GoLow ();
uint8_t GoBack();
uint8_t Exit_Found();
uint8_t MarkedState();
void StateToAction();
uint8_t deadend();


int main(void)
{
	srand(time(NULL));
	LCDInit();

//	DC_Motors_Init();
    Ultrasonic_Init();
uint16_t mm;
// 
// 	while (Exit_Found() == 0 /* edited*/)
// 	{
//           take_action();
//     }
// 	

	while (1)
	{
//  		 Car_MoveTo_Right();
// // 		 _delay_ms(100000);
// // 		  Car_MoveTo_Left();
// // 		 _delay_ms(100000); 
// // 		  Car_MoveTo_Forward();
// // 		  _delay_ms(100000);
// // 		  Car_MoveTo_Backward();


LCD_WRITE_NUM( Ultrasonic_Read(1));
_delay_ms(20000);
LCD_WRITE_COMMAND(LCD_Clear_Display);

LCD_WRITE_NUM(Ultrasonic_Read(2));
_delay_ms(20000);
LCD_WRITE_COMMAND(LCD_Clear_Display);

LCD_WRITE_NUM(Ultrasonic_Read(3));
_delay_ms(20000);
LCD_WRITE_COMMAND(LCD_Clear_Display);
		  
		  
	}
	 return 0 ;
}

void StateToAction()
{
	if(Previous_state[0] > current_state[0])
	{
		comp_action = 'S';
		compass_direction_to_usual_direction(comp_action , new_north);
	}
	else if(Previous_state[0] < current_state[0])
	{
		comp_action = 'N';
		compass_direction_to_usual_direction(comp_action , new_north);
	}
	else if	(Previous_state[1] > current_state[1])
	{
		comp_action = 'W';
		compass_direction_to_usual_direction(comp_action , new_north);
	}
	else if(Previous_state[1] < current_state[1])
	{
		comp_action = 'E';
		compass_direction_to_usual_direction(comp_action , new_north);
	}	
}
void LCDInit()
{
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_1;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_2;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_3;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);
	
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_4;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_5;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_6;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);
	
	LCD_INIT();
}


void get_status(void)
{
	
	if(Ultrasonic_Read(Front) > 12)
	   state[Front] = 'F' ;
	 else 
	   state[Front] = 0 ;
	 
	if(Ultrasonic_Read(Right) > 12)
	    state[Right] = 'R' ;
	else
		state[Right] = 0 ;
		
	if(Ultrasonic_Read(Left) > 12)
		state[Left] = 'L' ;
	else
		state[Left] = 0 ;	   
}
uint8_t get_random_action(uint8_t upper )
{
		return (rand()%upper);
}





uint8_t north_updater(uint8_t usual_action ,uint8_t north)
{
	//this function will return new north depend on the previous north && taken action
	//parameters :
	// usual_action: taked action , north: north at the usual action
	//return :
	if (north == 'F' && usual_action == 'L')
	new_north = 'R';
	//##################################################
	// updated north after taking usual_action with the north
	//if action is B or F north does not change
	if (north == 'F' && usual_action == 'F' )
	new_north = 'F';
	if (north == 'F' && usual_action == 'B')
	new_north = 'B';
	if (north == 'F' && usual_action == 'R')
	new_north = 'L';
	if (north == 'B' && usual_action == 'F')
	new_north = 'B';
	if (north == 'B' && usual_action == 'B')
	new_north = 'F';
	if (north == 'B' && usual_action == 'R')
	new_north = 'R';
	if (north == 'B' && usual_action == 'L')
	new_north = 'L';
	//##################################################
	if (north == 'R' && usual_action == 'F')
	new_north = 'R';
	if (north == 'R' && usual_action == 'B')
	new_north = 'L';
	if (north == 'R' && usual_action == 'R')
	new_north = 'F';
	if (north == 'R' && usual_action == 'L')
	new_north = 'B';
	//################################################
	if (north == 'L' && usual_action == 'F')
	new_north = 'L';
	if (north == 'L' && usual_action == 'B')
	new_north = 'R';
	if (north == 'L' && usual_action == 'R')
	new_north = 'B';
	if (north == 'L' && usual_action == 'L')
	new_north = 'F';
	
	return new_north ;
}


uint8_t reverse_usaual_direction(uint8_t direction)
{
	if (direction == 'R')
	return 'L';
	else if (direction == 'L')
	return 'R';
	else if (direction == 'F')
	return 'B';
	else if (direction == 'B')
	return 'F';
	
	return 'R';
}

uint8_t reverse_Copass_direction(uint8_t direction)
{
	if (direction == 'W')
	return 'E';
	else if (direction == 'N')
	return 'S';
	else if (direction == 'S')
	return 'N';
	else if (direction == 'E')
	return 'W';
	
	return 'W'; 
}

void compass_direction_to_usual_direction(uint8_t comp_action,uint8_t north )
{
	
	//this function will convert from ['E','N','S','W'] to ['F','B','L' ,'R']
	//parameters:
	//    # it will receive compass direction &&
	//    # where is the north of robot for example may be the north is in front or backward
	//    or right or left of the robot
	//return:
	//    #usual direction which is one of ['F','B','L' ,'R']
	//    #new north direction
	//
	//#IMPORTANT NOTE : CODE DEPEND ON THE FOLLOWING ORDER OF COMP_ACTION && USUAL_ACTION LISTS
	//#DO NOT CHANGE THE FOLLOWING ORDER
	
	
	

	if (north == 'F')
	{
		//same index
		usual_action = usual_actions[index_of(comp_actions,comp_action)];
	}
	
	
	else if (north == 'B')
	{
		usual_action = usual_actions[index_of(comp_actions,comp_action)];
		usual_action = reverse_usaual_direction(usual_action);
	}
	else if (north == 'R')
	{
		if (comp_action == 'N' || comp_action == 'S')
		{
			usual_action = usual_actions[index_of(comp_actions,comp_action)-2];
		}
		
		else if (comp_action == 'W')
		{
			usual_action = 'F';
		}
		
		else if (comp_action == 'E')
		{
			usual_action = 'B';
		}
	}
	else if (north == 'L')
	{
		if (comp_action == 'N')
		{
			usual_action = 'L';
		}
		else if (comp_action == 'S')
		{
			usual_action = 'R';
		}
		else if (comp_action == 'E')
		{
			usual_action = 'F';
		}
		else if (comp_action == 'W')
		{
			usual_action = 'B';
		}
	}
	new_north = north_updater(usual_action , north);
}


void usual_direction_to_compass_direction(uint8_t usual_action,uint8_t north)
{
	//this function will convert from ['E','N','S','W'] to ['F','B','L' ,'R']
	//parameters:
	//    # it will receive compass direction &&
	//    # where is the north of robot for example may be the north is in front or backward
	//    or right or left of the robot
	//return:
	//    #usual direction which is one of ['F','B','L' ,'R']
	//    #new north direction
	//
	//#IMPORTANT NOTE : CODE DEPEND ON THE FOLLOWING ORDER OF COMP_ACTION && USUAL_ACTION LISTS
	//#DO NOT CHANGE THE FOLLOWING ORDER
	
	

	if (north == 'F')
	{
		//same index
		comp_action = comp_actions[index_of(usual_actions,usual_action)];
	}
	
	else if (north == 'B')
	{
		comp_action =comp_actions[index_of(usual_actions,usual_action)];
		comp_action = reverse_Copass_direction(usual_action);
	}
	else if (north == 'R')
	{
		if (usual_action == 'N' || usual_action == 'S')
		{
			comp_action = comp_actions[index_of(usual_actions,usual_action)-2];
		}
		
		else if (usual_action == 'F')
		{
			comp_action = 'W';
		}
		
		else if (usual_action == 'B')
		{
			comp_action = 'E';
		}
	}
	else if (north == 'L')
	{
		if (usual_action == 'L')
		{
			comp_action = 'N';
		}
		else if (usual_action == 'R')
		{
			comp_action = 'S';
		}
		else if (usual_action == 'F')
		{
			comp_action = 'E';
		}
		else if (usual_action == 'B')
		{
			comp_action = 'W';
		}
	}
	//new_north = north_updater(usual_action , north);
}

uint8_t index_of(uint8_t * arr , uint8_t element)
{
	for(uint8_t i = 0 ; i < 4 ; i++)
	{
		if(element == arr[i])
		{
			return i ;
		}
	}
	return -1 ; 
}


void current_state_update(uint8_t action )
{
	if(action == 'N')
	{
		current_state[0]++;
	}
	else if(action == 'S')
	{
		current_state[0]--;
	}
	else if(action == 'E')
	{
		current_state[1]++;
	}
	else if(action == 'W')
	{
		current_state[1]--;
	}			
}

uint8_t GoLow ()
{
	
	uint8_t i = 0 , OnesCount = 0 , ZerosCount = 0;
	uint8_t ZeroWays[3] = {0};
	uint8_t OneWays [3] = {0};
	for	(i = 0 ; i < 3 ; i++)
	{
		if(state[i] != 0)
		{
			usual_direction_to_compass_direction(state[i],new_north);
			if(comp_action == 'N')
			{
				if(maze_visited_status[get_index(1+current_state[0])][get_index(current_state[1])] == 0)
				{
					ZeroWays[ZerosCount++] = 'N';
				}
				else if (maze_visited_status[get_index(1+current_state[0])][get_index(current_state[1])] == 1)
				{
					OneWays[OnesCount++] = 'N';	
				}

			}
			else if(comp_action == 'S')
			{
				if(maze_visited_status[get_index(current_state[0] - 1)][get_index(current_state[1])] == 0)
				{
					ZeroWays[ZerosCount++] = 'S';
				}
				else if (maze_visited_status[get_index(current_state[0] - 1)][get_index(current_state[1])] == 1)
				{
					OneWays[OnesCount++] = 'S';	
				}

			}
			else if(comp_action == 'E')
			{
				if(maze_visited_status[get_index(current_state[0])][get_index(current_state[1] + 1)] == 0)
				{
					ZeroWays[ZerosCount++] = 'E';
				}
				else if (maze_visited_status[get_index(current_state[0])][get_index(current_state[1] + 1)] == 1)
				{
					OneWays[OnesCount++] = 'E';	
				}
			}
			else if(comp_action == 'W')
			{
				if(maze_visited_status[get_index(current_state[0])][get_index(current_state[1] - 1)] == 0)
				{
					ZeroWays[ZerosCount++] = 'W';
				}
				else if (maze_visited_status[get_index(current_state[0])][get_index(current_state[1] - 1)] == 1)
				{
					OneWays[OnesCount++] = 'W';	
				}
			}						
		}
	}
	if(ZeroWays[0] != 0)
	{
		comp_action = ZeroWays[get_random_action(ZerosCount)];
		compass_direction_to_usual_direction(comp_action,new_north);
		return 0;
	}
	else
	{
		comp_action = OneWays [get_random_action(OnesCount)];
		compass_direction_to_usual_direction(comp_action,new_north);
		return 1;
	}
	
}

uint8_t GoBack()
{
	if(maze_visited_status[get_index(Previous_state[0])][get_index(Previous_state[1])] == 1)
	{
		return 1 ;
	}
	else if (maze_visited_status[get_index(Previous_state[0])][get_index(Previous_state[1])] == 2)
	{
		Previous_state[0] = current_state[0];
		Previous_state[1] = current_state[1];
		return 0;
	}
	// edited 
	return 1;
}

uint8_t Exit_Found()
{
	get_status();
	if(Ultrasonic_Read(Front) > 55)
	{
		usual_action = 'F';
		// move to usual action
		Car_MoveTo(usual_action);
		return 1;
	}
	else if (Ultrasonic_Read(Right) > 55)
	{
		usual_action = 'R';
		// move to usual action
		Car_MoveTo(usual_action);
		return 1;
	}
	else if (Ultrasonic_Read(Left) > 55)
	{
		usual_action = 'L';
		// move to usual action
		Car_MoveTo(usual_action);
		return 1;
	}
	// edited
       return 0;
}

uint8_t MarkedState()
{
	int i = 0;
	for(i = 0 ; i < 3 ; i++)
	{
		if(state[i] !=0)
		{
			usual_direction_to_compass_direction(state[i],new_north);
			if(comp_action == 'N')
			{
				if(maze_visited_status[get_index(1+current_state[0])][get_index(current_state[1])] != 0)
				{
					return 1 ;
				}	
			}
			else if(comp_action == 'S')
			{
				if(maze_visited_status[get_index(current_state[0] - 1)][get_index(current_state[1])] != 0)
				{
					return 1 ;
				}	
			}
			else if(comp_action == 'E')
			{
				if(maze_visited_status[get_index(current_state[0])][get_index(current_state[1] + 1)] != 0)
				{
					return 1 ;
				}	
			}
			else if(comp_action == 'W')
			{
				if(maze_visited_status[get_index(current_state[0])][get_index(current_state[1] - 1)] != 0)
				{
					return 1 ;
				}	
			}
		}

	}
	return 0 ;
}

uint8_t deadend()
{
	if(Ultrasonic_Read(Front) <= 12 && Ultrasonic_Read(Left) <= 12 && Ultrasonic_Read(Right) <= 12)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void take_action (void)
{
	if (!deadend())
	{
		if(MarkedState())
		{
			if(GoBack())
			{

				track_memory[track_counter][0] = 0;
				track_memory[track_counter][1] = 0;
				track_counter--;
				maze_visited_status[get_index(current_state[0])][get_index(current_state[1])] = 2;

				Previous_state[0] = current_state[0];
				Previous_state[1] = current_state[1];

				current_state[0] = track_memory[track_counter][0];
				current_state[1] = track_memory[track_counter][1];
				
				StateToAction();
				// move to uaual action 
				Car_MoveTo(usual_action);
				//go back
				Car_MoveTo('B');
			}
			else
			{
				if(GoLow())
				{
//					if(Previous_state[0] == track_memory[track_counter-1][0] && Previous_state[1] == track_memory[track_counter-1][1])
//					{
						maze_visited_status[get_index(current_state[0])][get_index(current_state[1])] = 2;
						Previous_state[0] = current_state[0];
						Previous_state[1] = current_state[1];
						// move to uaual action 
						Car_MoveTo(usual_action);
						track_memory[track_counter][0] = 0;
						track_memory[track_counter][1] = 0;				
						track_counter--;
						current_state[0] = track_memory[track_counter][0];
						current_state[1] = track_memory[track_counter][1];
						StateToAction();
						// move to uaual action 
						Car_MoveTo(usual_action);
				//	}
				}
				else
				{
					
					Previous_state[0] = current_state[0];
					Previous_state[1] = current_state[1];
					current_state_update(comp_action);
					maze_visited_status[get_index(current_state[0])][get_index(current_state[1])] = 1;
					track_counter++;
					track_memory[track_counter][0] = current_state[0];
					track_memory[track_counter][1] = current_state[1];
					// move to uaual action 
					Car_MoveTo(usual_action);
				}				
			}
		}	
		else
		{
			GoLow();
			maze_visited_status[get_index(current_state[0])][get_index(current_state[1])] = 1;
			Previous_state[0] = current_state[0];
			Previous_state[1] = current_state[1];
			current_state_update(comp_action);
			track_counter++;
			track_memory[track_counter][0] = current_state[0];
			track_memory[track_counter][1] = current_state[1];
			// move to uaual action 
			Car_MoveTo(usual_action);
		}
	}
	else
	{
		maze_visited_status[get_index(current_state[0])][get_index(current_state[1])] = 2;
		Previous_state[0] = current_state[0];
		Previous_state[1] = current_state[1];
		track_memory[track_counter][0] = 0;
		track_memory[track_counter][1] = 0;				
		track_counter--;
		current_state[0] = track_memory[track_counter][0];
		current_state[1] = track_memory[track_counter][1];
		StateToAction();
		// move to uaual action 
		Car_MoveTo(usual_action);
		//Goback
		Car_MoveTo('B');
	}
}
uint8_t get_index(int8_t in)
{
	if(in > 0)
	{
		return in ;
	}
	else if(in < 0)
	{
		return in+5 ;
	}
    return 0;	
}