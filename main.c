/*
    prototype game with an overworld map by Eli Canup
    Change Log:
        4-30-15
            Initial changes
        5-12-15
            fixed map issue
        5-13-15
            added movement system
            changed the map and made it bigger
    To-Do list:


    Documentation:
        Variables:
            -map-an array to hold the map layout.
                *map values:
                    >0=player, P
                    >1=water, ~
                    >2=grass, "
                    >3=dirt, X
                    >4=sand, .
                    >5=trees, !
            -player- a list used to store the player's current position
                    >0=X position
                    >1=Y position
                    >2=Health


*/
#include <stdio.h>
#include <stdlib.h>
#include "mapgame.h"
#define X 0
#define Y 1
#define hp 2
#define MAPX 30        //                   10                  20
#define MAPY 30        //0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
int map[MAPX][MAPY]={   {1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//0
                        {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//1
                        {1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//2
                        {1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//3
                        {1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//4
                        {1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},//5
                        {1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5},//6
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5},//7
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5},//8
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5},//9
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5},//10
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5},//11
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5},//12
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5},//13
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5}};//14
int player[3]={15,7,100};
void mapdisplay();
int playerspot();
int battle();
void gameover();
void drawenemy(int enemy);
int score=0;
int main()
{
    srand(time(NULL));
    mapdisplay(map,player);
    mapdisplay(map,player);
    while(1)
    {
        clear_screen();
        printf("score=%d,hp=%d\n",score,player[hp]);
        mapdisplay(map,player);
        switch (getch())
        {
            case 'w':
            case 'W':
            if(player[Y]-1>=0)
            player[Y]--;
            break;

            case 's':
            case 'S':
            if(player[Y]<=MAPY/2-2)
            player[Y]++;
            break;

            case 'a':
            case 'A':
            if(player[X]-1>=0)
                player[X]--;
            break;

            case 'd':
            case 'D':
            if(player[X]<=MAPX-2)
            player[X]++;
            break;
        }
        if(rand() % 100 + 1<=12)
        {
            if(battle()==0)
            {
                gameover();
                return 0;
            }
        }
    }
    return 0;
}
int playerspot()
{
    return(map[player[Y]][player[X]]);
}

void mapdisplay(int map[MAPX][MAPY],int player[2])
{
    int i,j;
    for(j=0;j<MAPY/2;j++)
    {
        for(i=0;i<MAPX;i++)
        {
            if(i==player[X]&&j==player[Y])
                if(playerspot()!=1)
                    printf("%c",80);
                else
                    printf("@");
            else
            {
                switch(map[j][i])
                {
                    case 1:
                        printf("%c",126);
                        break;
                    case 2:
                        printf("%c",34);
                        break;
                    case 3:
                        printf("%c",38);
                        break;
                    //case 4:
                        //printf("%c",);
                        //break;
                    case 5:
                        printf("%c",33);
                        break;
                    default:
                        printf("%d",map[j][i]);
                }
            }
        }
        printf("\n");
    }
}
int battle()
{
    clear_screen();
    sleep(2);
    int enemy=rand() % 3 + 1;
    int action, enemyhealth, damage, damage2;
    drawenemy(enemy);
        switch(enemy)
        {
            case 1:
            printf("A wild snake appeared\n");
            enemyhealth=10;
            break;
            case 2:
            printf("An evil dragon appeared\n");
            enemyhealth=20;
            break;
            case 3:
            printf("A Hungry wolf appeared\n");
            enemyhealth=15;
            break;
        }
    sleep(1);
    while(1)
    {
        printf("What do you want to do? hp=%d\n",player[hp]);
        printf("1.Attack\t 2.dodge\n");
        switch (getch())
        {
            case '1':
                action=1;
                break;
            case '2':
                action=2;
                break;
            default:
                printf("That is not a real action\n");
                sleep(1);
                action=0;
                break;
        }
        if(action==0)
        {
            drawenemy(enemy);
            continue;
        }
        switch(enemy)
        {
            case 1:
            printf("The wild snake attacked.\n");
            break;
            case 2:
            printf("The evil dragon attacked.\n");
            break;
            case 3:
            printf("The hungry wolf attacked\n");
            break;
        }
        sleep(1);
        if(action==1)
        {
            damage=rand()%10+1;
            printf("The enemy did %d damage\n", damage);
            sleep(1);
            player[hp]-=damage;
            if(player[hp]<=0)
            {
                return 0;
            }
            else
            	damage2=rand()%15+1;
            printf("You attack!\n");
            sleep(1);
            if(rand()%2+1==1)
            {
                printf("you dealt %d damage to the enemy\n",damage2);
                enemyhealth-=damage2;
            }
            else
                printf("It missed!\n");
            sleep(1);
        }
        else if(action==2)
        {
            printf("It missed\n");
        }
        sleep(1);
        if(enemyhealth<=0)
        {
            printf("You win!\n");
            score++;
            sleep(1);
            return 1;
        }
        else if(player[hp]<=0)
        {
            return 0;
        }
        else
            drawenemy(enemy);
    }
}
void gameover()
{
    printf("Game over");
}
void drawenemy(int enemy)
{
    clear_screen();
    switch(enemy)
    {
        case 1:
        printf("\t            ____\n");
        printf("\t         .'`_ o `;__,\n");
        printf("\t.       .'.'` '---'  '\n");
        printf("\t.`-...-'.'\n");
        printf("\t `-...-'\n");
        break;

        case 2:
        printf("                  _ _\n");
        printf("          _     //` `\\\n");
        printf("      _,-\"\\%%   // /``\\`\\\n");
        printf(" ~^~ >__^  |%% // /  } `\\`\\\n");
        printf("        )  )%%// / }  } }`\\`\\\n");
        printf("       /  (%%/'/.\\_/\\_/\\_/\\`/\n");
        printf("      (    '         `-._`\n");
        printf("       \\     ,     (  \\   `-.__.-;%%>\n");
        printf("        /_`\\ \\      `\\ \\.\" `-..-'`\n");
        printf("       ``` /_/`\"-=-'`/_/\n");
        printf("           ```       ```\n");



        break;

        case 3:
        printf("                              .\n");
        printf("                              ))\n");
        printf("        )\\\\                  //\n");
        printf("       _``\\`,- '''' ''- ,,,/ /\n");
        printf("  .---'a> , < ,<' << ,<, ' / \\\n");
        printf("  `v^w   ' , << ,< ' <  <  / \\\n");
        printf("   ````--' \\  ,,,---''/ <' //\n");
        printf("            !! ;;    ( '  / \\\n");
        printf("            !!</       \\ `\\ /\n");
        printf("          <</          / /</\n");
        printf("                      <</\n");
        break;
    }
}
