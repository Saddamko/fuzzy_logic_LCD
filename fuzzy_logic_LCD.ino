#include <LiquidCrystal.h>

//-------------------------**       FUZZY LOGIC
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//-------------------------**       DEFINES

#define PI 3.14159265358979323846
#define   rule_ant_max    2
#define   rule_con_max   1
#define   rule_count        25

LiquidCrystal lcd(12, 10, 11, 5, 4, 3, 2);

//-------------------------**       STRUCTURES

void setup()
{
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Привет, мир!");
  lcd.scrollDisplayRight(); 
      // wait a bit:
  delay(500);
  lcd.scrollDisplayLeft(); 
  delay(500);
  
}

void loop() 
{
 //FUZZY_SYSTEM();
  lcd.scrollDisplayRight(); 
      // wait a bit:
  delay(500);
  lcd.scrollDisplayLeft(); 
  delay(500);
}

struct SETS
{
    float x0,x1,x2,x3;
    int settype;
};

struct VARIABLES
{
    float minval;
    float maxval;
    int num_sets;
    int defuz_type;
    SETS set[10];
};

struct RULES
{
    int anticedent[2][3];
    int consequent[2][2];
    int and_or[2];
    int rule_strength;
};

//-------------------------**       VARIABLES

VARIABLES inputvar[3]=
{
    {-1.0000,1.0000,5,0,
    {{0.0000,0.0000,0.0000,0.0000,0},
    {-1.0000,-1.0000,-0.8000,-0.4000,0},
    {-0.8000,-0.4000,-0.4000,0.0000,0},
    {-0.4000,0.0000,0.0000,0.4000,0},
    {0.0000,0.4000,0.4000,0.8000,0},
    {0.4000,0.8000,1.0000,1.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0}}},
    {-1.0000,1.0000,5,0,
    {{-1.0000,-1.0000,-0.8000,-0.4000,0},
    {-1.0000,-1.0000,-0.8000,-0.4000,0},
    {-0.8000,-0.4000,-0.4000,0.0000,0},
    {-0.4000,0.0000,0.0000,0.4000,0},
    {0.0000,0.4000,0.4000,0.8000,0},
    {0.4000,0.8000,1.0000,1.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0}}},
    {-1.0000,1.0000,0,0,
    {{0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0}}}
};

VARIABLES outputvar[2]=
{
    {-1.0000,1.0000,7,0,
    {{0.0000,0.0000,0.0000,0.0000,0},
    {-1.0000,-1.0000,-0.8000,-0.5333,0},
    {-0.8000,-0.5333,-0.5333,-0.2667,0},
    {-0.5333,-0.2667,-0.2667,0.0000,0},
    {-0.2667,0.0000,0.0000,0.2667,0},
    {0.0000,0.2667,0.2667,0.5333,0},
    {0.2667,0.5333,0.5333,0.8000,0},
    {0.5333,0.8000,1.0000,1.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0}}},
    {-1.0000,1.0000,0,0,
    {{0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0},
    {0.0000,0.0000,0.0000,0.0000,0}}}
};

RULES rule[rule_count]=
{
    {{{0,1,0},{1,1,0}},{{0,0},{1,0}},{0,0},100},
    {{{0,1,0},{1,2,0}},{{0,0},{1,0}},{0,0},100},
    {{{0,1,0},{1,3,0}},{{0,0},{2,0}},{0,0},100},
    {{{0,1,0},{1,4,0}},{{0,0},{3,0}},{0,0},100},
    {{{0,1,0},{1,5,0}},{{0,0},{4,0}},{0,0},100},
    {{{0,1,0},{2,1,0}},{{0,0},{1,0}},{0,0},100},
    {{{0,1,0},{2,2,0}},{{0,0},{2,0}},{0,0},100},
    {{{0,1,0},{2,3,0}},{{0,0},{3,0}},{0,0},100},
    {{{0,1,0},{2,4,0}},{{0,0},{4,0}},{0,0},100},
    {{{0,1,0},{2,5,0}},{{0,0},{5,0}},{0,0},100},
    {{{0,1,0},{3,1,0}},{{0,0},{2,0}},{0,0},100},
    {{{0,1,0},{3,2,0}},{{0,0},{3,0}},{0,0},100},
    {{{0,1,0},{3,3,0}},{{0,0},{4,0}},{0,0},100},
    {{{0,1,0},{3,4,0}},{{0,0},{5,0}},{0,0},100},
    {{{0,1,0},{3,5,0}},{{0,0},{6,0}},{0,0},100},
    {{{0,1,0},{4,1,0}},{{0,0},{3,0}},{0,0},100},
    {{{0,1,0},{4,2,0}},{{0,0},{4,0}},{0,0},100},
    {{{0,1,0},{4,3,0}},{{0,0},{5,0}},{0,0},100},
    {{{0,1,0},{4,4,0}},{{0,0},{6,0}},{0,0},100},
    {{{0,1,0},{4,5,0}},{{0,0},{7,0}},{0,0},100},
    {{{0,1,0},{5,1,0}},{{0,0},{4,0}},{0,0},100},
    {{{0,1,0},{5,2,0}},{{0,0},{5,0}},{0,0},100},
    {{{0,1,0},{5,3,0}},{{0,0},{6,0}},{0,0},100},
    {{{0,1,0},{5,4,0}},{{0,0},{7,0}},{0,0},100},
    {{{0,1,0},{5,5,0}},{{0,0},{7,0}},{0,0},100}
};


float INPUT_DATA[3];
float OUTPUT_DATA[2];
int connec_tive=0;
int implica_tion=0;
int agriga_tion=0;

//-------------------------**       PROTOTYPES

void FUZZY_SYSTEM(void);
float SETGEN(float x,struct SETS *fuzzyset);
float SETGEN_SIGMOID(float x,struct SETS *fuzzyset);
float SETGEN_TRAPIZOID(float x,struct SETS *fuzzyset);
float CONNECTIVE(float x,float y,int type);
float IMPLICATION (float x,float y);
float AGRIGATION(float x,float y);
float MIN(float x,float y);
float MAX(float x,float y);
float PRODUCT(float x,float y);
float SUM(float x,float y);


//-------------------------**       FUNCTIONS

void FUZZY_SYSTEM(void)
{
register int rule_num,space_num;
int ant_num,con_num;
int var_num,set_num,contype;
float predicate;
float domval,valmax,valmin;
float u_output[2][10];
float denominator[2];
float numerator[2];
float output_space[100];
lcd.print("Start!");
delay (1000);
    for (con_num=0;con_num<2;con_num++)
    {
        OUTPUT_DATA[con_num]=0.0;
        for (set_num=0;set_num<10;set_num++)
        {
            u_output[con_num][set_num]=0.0;
        }
    }
    for (rule_num=0;rule_num<rule_count;rule_num++)
    {
        if(rule[rule_num].and_or[0]==0) predicate=1;//and MIN & Product
        if((rule[rule_num].and_or[0]==1)&&(connec_tive==0)) predicate=0;//or MAX
        if((rule[rule_num].and_or[0]==1)&&(connec_tive==1)) predicate=-1;//or SUM
        for(ant_num=0;ant_num<=rule_ant_max-1;ant_num++)
        {
            var_num=rule[rule_num].anticedent[0][ant_num];
            set_num=rule[rule_num].anticedent[1][ant_num];
            contype=ant_num-1;
            if (contype==-1) contype=0;
            predicate=CONNECTIVE(predicate,SETGEN(INPUT_DATA[var_num],&inputvar[var_num].set[set_num]),rule[rule_num].and_or[contype]);
            predicate=predicate*(rule[rule_num].rule_strength/100);
        }
        if(predicate>0)
        {
            for(con_num=0;con_num<=rule_con_max-1;con_num++)
            {
                set_num=rule[rule_num].consequent[1][con_num];
                u_output[con_num][set_num]=AGRIGATION(u_output[con_num][set_num],IMPLICATION(1.00,predicate));
            }
        }
    }
    for(con_num=0;con_num<=rule_con_max-1;con_num++)
    {
        denominator[con_num]=0.0;
        numerator[con_num]=0.0;
        if (outputvar[con_num].defuz_type==0)//COG
        {
            valmax=outputvar[con_num].maxval;
            valmin=outputvar[con_num].minval;
            for(space_num=0;space_num<=100;space_num++)
            {
                output_space[space_num]=0.0;
                domval=((valmax-valmin)*space_num/100)+valmin;
                for(set_num=1;set_num<=outputvar[con_num].num_sets;set_num++)
                {
                    output_space[space_num]=AGRIGATION(output_space[space_num],IMPLICATION(u_output[con_num][set_num],SETGEN(domval,&outputvar[con_num].set[set_num])));
                }
                denominator[con_num]=denominator[con_num]+output_space[space_num];
                numerator[con_num]=numerator[con_num]+(domval*output_space[space_num]);
            }
        }
        if (outputvar[con_num].defuz_type==1)//COGS (singleton)
        {
            for(set_num=1;set_num<=outputvar[con_num].num_sets;set_num++)
            {
                denominator[con_num]=denominator[con_num]+u_output[con_num][set_num];
                numerator[con_num]=numerator[con_num]+(u_output[con_num][set_num]*outputvar[con_num].set[set_num].x2);
            }
        }
        if (denominator[con_num]==0.0) denominator[con_num]=1.0;//Prevent divide by zero
        OUTPUT_DATA[con_num]=numerator[con_num]/denominator[con_num];
        lcd.setCursor(0, 1);
        lcd.print(OUTPUT_DATA[con_num]);
    }
lcd.print("Stop!");
delay (1000);
}

float SETGEN(float x,struct SETS *fuzzyset)
{
    if(fuzzyset->settype==0) return  SETGEN_TRAPIZOID(x,fuzzyset);
    else return  SETGEN_SIGMOID(x,fuzzyset);
}

float SETGEN_SIGMOID(float x,struct SETS *fuzzyset)
{
    if ((x<fuzzyset->x0)&&(fuzzyset->x0<fuzzyset->x1))
    {
        return 0;
    }
    else if ((x<fuzzyset->x0)&&(fuzzyset->x0>=fuzzyset->x1)&&(fuzzyset->x1<fuzzyset->x2))
    {
        return 1;
    }

    else if((fuzzyset->x0<=x)&&(x<fuzzyset->x1))
    {
        return (0.5+0.5*cos(((x-fuzzyset->x1)/(fuzzyset->x1-fuzzyset->x0))*PI));
    }
    else if((fuzzyset->x1<=x)&&(x<=fuzzyset->x2))
    {
        return 1;
    }
    else if((fuzzyset->x2<x)&&(x<=fuzzyset->x3))
    {
        return (0.5+0.5*cos(((x-fuzzyset->x2)/(fuzzyset->x3-fuzzyset->x2))*PI));
    }
    else if((fuzzyset->x3<x)&&(fuzzyset->x2<fuzzyset->x3))
    {
        return 0;
    }
    else if((fuzzyset->x3<x)&&(fuzzyset->x2>=fuzzyset->x3)&&(fuzzyset->x2>fuzzyset->x1))
    {
        return 1;
    }
    else return 1;
}

float SETGEN_TRAPIZOID(float x,struct SETS *fuzzyset)
{
    if ((x<fuzzyset->x0)&&(fuzzyset->x0<fuzzyset->x1))
    {
        return 0;
    }
    else if ((x<fuzzyset->x0)&&(fuzzyset->x0>=fuzzyset->x1)&&(fuzzyset->x1<fuzzyset->x2))
    {
        return 1;
    }
    else if((fuzzyset->x0<=x)&&(x<fuzzyset->x1))
    {
        return ((x-fuzzyset->x0)/(fuzzyset->x1-fuzzyset->x0));
    }
    else if((fuzzyset->x1<=x)&&(x<=fuzzyset->x2))
    {
        return 1;
    }
    else if((fuzzyset->x2<x)&&(x<=fuzzyset->x3))
    {
        return ((x-fuzzyset->x3)/(fuzzyset->x2-fuzzyset->x3));
    }
    else if((fuzzyset->x3<x)&&(fuzzyset->x2<fuzzyset->x3))
    {
        return 0;
    }
    else if((fuzzyset->x3<x)&&(fuzzyset->x2>=fuzzyset->x3)&&(fuzzyset->x2>fuzzyset->x1))
    {
        return 1;
    }
    else return 1;
}

float CONNECTIVE(float x,float y,int type)
{
    if(connec_tive==0)//zadah MIN/MAX
    {
        if(type==0)//AND connective
        {
            return MIN(x,y);
        }
        if(type==1)//OR connective
        {
            return MAX(x,y);
        }
    }
    if(connec_tive==1)//Algebraic product sum
    {
        if(type==0)//AND connective
        {
            return PRODUCT(x,y);
        }
        if(type==1)//OR connective
        {
            if (x==-1) return y;//compensate for initial value of running total for predicate
            else if(y==-1) return x;
            else return SUM(x,y);
        }
    }
    return -1;
}

float IMPLICATION(float x,float y)
{
    if(implica_tion==0)//Mamdani
    {
        return MIN(x,y);
    }
    if(implica_tion==1)//Larson
    {
        return PRODUCT(x,y);
    }
    return -1;
}

float AGRIGATION(float x,float y)
{
    if(agriga_tion==0)//Max
    {
        return MAX(x,y);
    }
    if(agriga_tion==1)//Sum
    {
        return SUM(x,y);
    }
    return -1;
}

float MIN(float x,float y)//Zadeh AND, Mandani implication
{
    if (x<y) return x;
    else return y;
}

float MAX(float x,float y)//OR
{
    if (x>y) return x;
    else return y;
}

float PRODUCT(float x,float y)//Algebraic Product....AND, Larson implication
{
    return (x*y);
}

float SUM(float x,float y)//Algebraic/Probalistic Sum..OR
{
    if(x==-1) return y;
    else if(y==-1) return x;
    else return ((x+y)-(x*y));
}


