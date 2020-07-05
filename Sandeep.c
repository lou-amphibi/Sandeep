#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LENGTH 24
#define WIDTH 10
#define START_L 8
#define START_W 10
#define INTERACT deepdesert[is-1][js]

void clear(void);
void about(void);
void sandcreate(void);
int move(int tile);
void statusbar(void);
void emptyobject(void);
void event(void);
void seacheck(char s[]);
void deepout(void);
int redbox(void);

int life=31;
int anybutton=0;
int psandcreate=0;
int flagpsand=0;
int is=START_L;
int js=START_W;

struct inventory
{
    int isitem1;
    char *item1;
     int isitem2;
    char *item2;
     int isitem3;
    char *item3;
}inv;


struct eventlist
{
    int Y;
    int Grace;
    int Korall;
    int K;
    int Rock;
    int J;
    int Bones;
    int Skull;
    int Water;
    int xx;
    int X;
    int twox;
    int Gem;
    int Seaimage;
}list;

char Sea[7]="nnnnnn";

char deepdesert[WIDTH][LENGTH]={
    {"- - - - - - - - - - - -"},
    {"- ...   ,    Y  **  & -"},
    {"- K Y   o   & ..     J-"},
    {"-       O      .....  -"},
    {"-   (((     =W  ...   -"},
    {"-  Y     @      .  &  -"},
    {"-&&   &     Y       Y -"},
    {"-      ~            Y -"},
    {"-  Xx     N      YYY% -"},
    {"- - - - - - - - - - - -"}
};

int main()
{
    int steps=0;
    int tile=0;
    emptyobject();
    about();

    while(life>0)
    {
    clear();
    sandcreate();
    statusbar();
    event();
    printf("Идем.. ");
    getchar();
    tile=getchar();
    move(tile);
    steps++;
    life--;
    }

    deepdesert[is][js]='Z';
    clear();
    sandcreate();
    seacheck(Sea);
    printf("          \x1b[32m%d и %c\n\x1b[0m", steps, anybutton);
    if (psandcreate==1)
        printf("\x1b[33;1mПройдет полдня и от него уж не останется следа\n\x1b[0m");
    if (is==2 && js==20 && (strcmp(Sea, "Korra")==0))
        printf("\x1b[33;1mПочти дойдя до океана, почти услышав шепот волн, я говорю с открытом сердцем, ни капли лжи и крови в нем\n\x1b[0m");
    if (redbox())
        printf("\t\t\t  \x1b[31;1mX\n");
    else
        deepout();
    putchar('\n');
    printf("\x1b[33;1mСмерть пришла и твой милый друг теперь\nв руках надежных\n\x1b[0m");
}


void about(void)
{
    printf("        \x1b[33;1mSandeep\x1b[0m\n");
    printf("\x1b[32;1mN \x1b[33;1mне мог жить столько, сколько бы хотел\n\x1b[32;1mИ \x1b[33;1mпроисходит то, что должно\nГде угасает радость утра\nЖизнь остается не у дел\x1b[0m\n");
    printf("W - Up\nA - Left\nS - Down\nX - Right\nРегистр не важен, приятно пошататься\n");
    printf("(почти) Любая клавиша для продолжения: ");
    anybutton=getchar();
    while (anybutton=='\n')
    {
        printf("Другую!\n");
        anybutton=getchar();
    }
}

void sandcreate(void)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; deepdesert[i][j]!='\0'; j++)
        {
            if (deepdesert[i][j]=='-')
                printf("\x1b[40;31m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='&')
                printf("\x1b[40;35;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='.')
                printf("\x1b[40;33m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='N')
                printf("\x1b[40;32;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='Z')
                if (!psandcreate)
                    printf("\x1b[40;32;1m%c\x1b[0m", deepdesert[i][j]);
                else
                    printf("\x1b[40;33m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='%' && !list.Gem)
                printf("\x1b[40;36;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='%')
                printf("\x1b[40;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='Y')
                printf("\x1b[40;33;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='(' || deepdesert[i][j]=='@')
                printf("\x1b[40m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='K' || deepdesert[i][j]=='X' || deepdesert[i][j]=='x' || deepdesert[i][j]=='W' || deepdesert[i][j]=='=' || deepdesert[i][j]=='J')
                printf("\x1b[40;31;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='O' || deepdesert[i][j]=='o' || deepdesert[i][j]==',')
                printf("\x1b[40;34m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='*')
                printf("\x1b[40;32m%c\x1b[0m", deepdesert[i][j]);
             else if (deepdesert[i][j]=='~')
                printf("\x1b[40;34;1m%c\x1b[0m", deepdesert[i][j]);
            else if (deepdesert[i][j]=='0')
                printf("\x1b[40;34;1m%c\x1b[0m", deepdesert[i][j]);
            else
                printf("\x1b[40m%c\x1b[0m", deepdesert[i][j]);

        }
        putchar('\n');
    }
}


int move(int move)
{
    begin:
    if (move=='w' || move=='W')
    {
        if((deepdesert[is-1][js]==' ' || deepdesert[is-1][js]=='.') && is-1!=0)
        {
            if (deepdesert[is-1][js]==' ')
            {
                deepdesert[is][js]=' ';
                deepdesert[is-1][js]='N';
                if (psandcreate)
                    deepdesert[is][js]='.';
                is-=1;
                psandcreate=0;
                return 1;
            }
            else
            {
                if (psandcreate==0)
                {
                    deepdesert[is][js]=' ';
                    deepdesert[is-1][js]='N';
                    is-=1;
                    psandcreate=1;
                    return 1;
                }
                else if (psandcreate)
                {
                    deepdesert[is][js]='.';
                    deepdesert[is-1][js]='N';
                    is-=1;
                    psandcreate=1;
                    return 1;
                }
            }
        }
        else
        {
            printf("Перемещение невозможно/Illegal move.");
            printf("Идем.. ");
            getchar();
            move=getchar();
            goto begin;
        }
    }
    else if (move=='a' || move=='A')
    {
        if(deepdesert[is][js-1]==' ' || deepdesert[is][js-1]=='.')
        {
            if (deepdesert[is][js-1]==' ')
            {
                deepdesert[is][js]=' ';
                deepdesert[is][js-1]='N';
                if (psandcreate)
                    deepdesert[is][js]='.';
                js-=1;
                psandcreate=0;
                return 1;
            }
            else
            {
                if (psandcreate==0)
                {
                    deepdesert[is][js]=' ';
                    deepdesert[is][js-1]='N';
                    js-=1;
                    psandcreate=1;
                    return 1;
                }
                else if (psandcreate)
                {
                    deepdesert[is][js]='.';
                    deepdesert[is][js-1]='N';
                    js-=1;
                    psandcreate=1;
                    return 1;
                }
            }
        }
        else
        {
            printf("Перемещение невозможно/Illegal move. ");
            printf("Идем.. ");
            getchar();
            move=getchar();
            goto begin;
        }
    }
    else if (move=='s' || move=='S')
    {
        if((deepdesert[is+1][js]==' ' || deepdesert[is+1][js]=='.') && is+1!=9)
        {
            if (deepdesert[is+1][js]==' ')
            {
                deepdesert[is][js]=' ';
                deepdesert[is+1][js]='N';
                if (psandcreate)
                    deepdesert[is][js]='.';
                is+=1;
                psandcreate=0;
                return 1;
            }
            else
            {
                if (psandcreate==0)
                {
                    deepdesert[is][js]=' ';
                    deepdesert[is+1][js]='N';
                    is+=1;
                    psandcreate=1;
                    return 1;
                }
                else if (psandcreate)
                {
                    deepdesert[is][js]='.';
                    deepdesert[is+1][js]='N';
                    is+=1;
                    psandcreate=1;
                    return 1;
                }
            }
        }
        else
        {
            printf("Перемещение невозможно/Illegal move.");
            printf("Идем.. ");
            getchar();
            move=getchar();
            goto begin;
        }
    }
    else if (move=='x' || move=='X')
    {
        if(deepdesert[is][js+1]==' ' || deepdesert[is][js+1]=='.')
        {
            if (deepdesert[is][js+1]==' ')
            {
                deepdesert[is][js]=' ';
                deepdesert[is][js+1]='N';
                if (psandcreate)
                    deepdesert[is][js]='.';
                js+=1;
                psandcreate=0;
                return 1;
            }
            else
            {
                if (psandcreate==0)
                {
                    deepdesert[is][js]=' ';
                    deepdesert[is][js+1]='N';
                    js+=1;
                    psandcreate=1;
                    return 1;
                }
                else if (psandcreate)
                {
                    deepdesert[is][js]='.';
                    deepdesert[is][js+1]='N';
                    js+=1;
                    psandcreate=1;
                    return 1;
                }
            }
        }
        else
        {
            printf("Перемещение невозможно/Illegal move.");
            printf("Идем.. ");
            getchar();
            move=getchar();
            goto begin;
        }
    }
    else
    {
        printf("WASX для передвижения..");
        getchar();
        move=getchar();
        goto begin;
    }
    return 0;
}

void statusbar(void)
{
    printf("Статус бар:");
    if (life>20)
        printf("\x1b[32;1m Созерцание\n\x1b[0m");
    else if (life<=20 && life>5)
        printf("\x1b[33;1m Принятие\n\x1b[0m");
    else
        printf("\x1b[31;1m Смирение\n\x1b[0m");
    printf("Инвентарь: \x1b[40m%s\x1b[0m \x1b[40m%s\x1b[0m \x1b[40m%s\x1b[0m\n", inv.item1, inv.item2, inv.item3);
}

char** checkinv(char** check);
char** invclean(char **iclean);
char** invobserv(char **check, char *item);
char** deleteinv(char **check, char *item);

void event(void)
{
    char **check=NULL;
    // Прочие ивенты
    if (list.Bones==2)
    {
        printf("\x1b[33;1mА смерти страх, дает желание жить, я принимаю\x1b[0m\n");
            if (life<=5)
                life=7;
        list.Bones++;
    }

    if (psandcreate && (check=invobserv(check, "&"))!=NULL && life<3)
        printf("Откуда здесь полярный ветер? Все говорят, что дует он за миг до смерти\n");

    if (psandcreate && !flagpsand)
    {
        if (list.Water<1)
        {
            printf("\x1b[33;1mВ движении утопаешь быстрее, стоя на месте быстрее горишь\x1b[0m\n");
            flagpsand=1;
        }
        else
        {
            printf("\x1b[33;1mОтпивши жизни утонуть, привычка\x1b[0m\n");
            flagpsand=1;
        }
        life--;
    }

    else if(psandcreate)
        life--;

    if ((check=invobserv(check, "@"))!=NULL)
        if ((check=invobserv(check, "("))!=NULL)
            if ((check=invobserv(check, "\x1b[31;1mX"))!=NULL)
            {
                printf("\x1b[33;1mВам никогда не будет грустно, речное устье, песком забилось. \x1b[31;1mИ я смиряюсь\x1b[0m\n");
                if (life>5)
                    life=5;
            }

    if (is==7 && js==1)
        Sea[0]='K';
    else if (is==7 && js==2)
        Sea[1]='o';
    else if (is==7 && js==5)
        Sea[2]='r';
    else if (is==6 && js==18)
        Sea[3]='r';
    else if (is==3 && js==12)
        Sea[4]='a';
    else if (is==2 && js==20)
    {
            Sea[5]='l';
            Sea[6]='\0';
    }

    if (list.Seaimage==0 && strcmp(Sea, "Korral")==0)
    {
        printf("\x1b[33;1mЯ видел море, неумолимые видения, я \x1b[32;1mсозерцал. \x1b[33;1mМне хватит рук, чтобы забрать с собой его частичку?\x1b[0m\n");
        if ((check=checkinv(check))!=NULL)
            *check="\x1b[32;1m~";
        life+=10;
        list.Seaimage++;
    }

    // Основной ивент-лист
    if (INTERACT=='@') //Череп
    {
        printf("\x1b[33;1mЛег костьми усталый зверь и что-то резко зафонило\x1b[0m\n");
        if ((check=checkinv(check))!=NULL)
        {
            *check="@";
            INTERACT='^';
        }
    }
    else if (INTERACT=='^')
    {
        printf("\x1b[33;1mНет печальней мусора, чем остатки остатков былого величия\x1b[0m\n");
    }
    else if (INTERACT=='=') // Собиратель
    {
        if (life<4)
        {
            printf("\x1b[31;1mНи к черту здесь ходить убитым, я помогу тебе в пути\x1b[0m\n");
            life=1;
        }
        else
            printf("\x1b[33;1mНыне кузнец, но воровское прошлое мелькает между облаками\x1b[0m\n");
    }
    else if (INTERACT=='W')
    {
        printf("\x1b[31;1mПоследнее что ты нашел, окажется в моих карманах и странников в этих краях, как ни бывало\x1b[0m\n");
        if ((check=invclean(check))!=NULL)
        {
            if (strcmp(*check, "\x1b[32m*")==0)
                list.Grace=0;
            *check=" ";
                printf("\x1b[33;1mДуновение ветра, очень сухой воздух, смотри по сторонам, пока не поздно\x1b[0m\n");
        }
    }
    else if (INTERACT=='O') // Дерево
    {
        if ( ((check=invobserv(check, "\x1b[36;1m%"))!=NULL) && list.Gem==1)
        {
             printf("\x1b[33;1mВ твоих руках, его остатки, вся дурь осталось в голове, теперь, она в руках твоих\x1b[0m\n");
            *check="&";
            list.Gem++;
        }
        if (!list.Rock)
        {
            printf("\x1b[34;1mНадпись на старом древесном стволе: \x1b[33;1mСальпуги рыщут по ночам, а я зову на чай трех богатеев с бедняками\x1b[0m\n");
            list.Rock++;
        }
        else
            printf("\x1b[33;1mТишина - это насилие\x1b[0m\n");
    }
    else if (deepdesert[is+1][js+1]=='%' && !list.Gem) //Великан и камень
    {
        printf("\x1b[33;1mЗа спиной причудливого камня его тень и ледяные великаны\x1b[0m\n");
        if ((check=checkinv(check))!=NULL)
        {
            *check="\x1b[36;1m%";
            list.Gem++;
        }
    }
    else if(is==8 && js==21 && list.Gem==2)
        printf("\x1b[33;1mОстатки ледяного исполина не так ужасны, ведь \x1b[0mголова его \x1b[33;1mв твоей походной сумке к счаcтью\x1b[0m\n");
    else if(is==6 && js==18)
        printf("\x1b[33;1mТак много желтых кактусов, могли посадить рядом те, кто не был обделен умом, быть может лишь свободной волей, как рад я видеть, что их больше нет\x1b[0m\n");
    else if(INTERACT=='(') //Кости
    {
        if (list.Bones==-1)
        {
            printf("\x1b[33;1mНе сосчитать\x1b[0m\n");
            list.Bones++;
            INTERACT='#';
            if ((check=checkinv(check))!=NULL)
                *check="(";
        }
        else if (list.Bones==0)
        {
            printf("\x1b[33;1mСломанных ребер\x1b[0m\n");
            list.Bones++;
            INTERACT='#';

        }
        else if (list.Bones)
        {
            printf("\x1b[33;1mБратских народов\x1b[0m\n");
            list.Bones++;
            INTERACT='#';
        }
    }
    else if (INTERACT=='#')
        printf("\x1b[33;1mНет печали, они были из тех, кто ползал и лаял\x1b[0m\n");
    else if (INTERACT=='~') //Море
    {
        if (list.Water==-2)
        {
            printf("\x1b[33;1mКогда-то море и кипела жизнь, теперь лишь лужи и несколько ракушек, мой милый друг, мне все же лучше\x1b[0m\n");
            life+=5;
            list.Water++;
        }
        else if (list.Water==-1)
        {
            printf("\x1b[33;1mК чему нам почитать и уважать остатки океана, если жизни свет вот-вот угаснет\x1b[0m\n");
            life+=4;
            list.Water++;
        }
        else if (list.Water==0)
        {
            printf("\x1b[33;1mЯ чувствую себя убийцей, как подобает палачу, скажу: Мой друг, я не напился и уже видно не напьюсь\x1b[0m\n");
            life+=3;
            list.Water++;
            INTERACT='0';
        }
    }
    else if (INTERACT=='0')
        printf("\x1b[33;1mЯ бы хотел просить прощения, но чувствую, что не могу, остатки совести заели, не будет век теперь приливов, у моря, что давало жизнь\x1b[0m\n");
    else if (INTERACT=='&') //Кораллы
    {
        if (list.Korall<0)
        {
            printf("\x1b[35;1mОстатки рифов, \x1b[33;1mхотелось бы остаться с вами\x1b[0m\n");
            list.Korall++;
        }
        else if (list.Korall==0)
        {
            printf("\x1b[35;1mОстатки рифов, \x1b[33;1mвы удивительно добры\x1b[0m\n");
            list.Korall++;
            life+=4;
        }
        else if (list.Korall==1)
        {
            printf("\x1b[35;1mОстатки рифов, \x1b[33;1mтеперь я здешний\x1b[0m\n");
            life+=1;
            list.Korall++;
            if ((check=checkinv(check))!=NULL)
            {
                *check="\x1b[35;1m&";
            }
        }
        else
            printf("\x1b[35;1mОстатки рифов, \x1b[33;1mмне кажется, я помню океан, морских созданий косяки, ну или просто косяки\x1b[0m\n");
    }
    else if (deepdesert[is+1][js]=='x' && !list.xx)
    {
        printf("\x1b[33;1mЛегкий запах разложения перекрывает старый дезик\x1b[0m\n");
        list.xx++;
    }
    else if (deepdesert[is+1][js]=='X' && !list.X) //Мертвецы
    {
        printf("\x1b[33;1mЗаписка \x1b[31;1mХраните мои глупые стихи в старой коробке, туда же спрячьте все свои кинжалы\x1b[0m\n");
        list.X++;
        if ((check=checkinv(check))!=NULL)
            *check="\x1b[31;1mX";
    }
    else if (INTERACT=='K') //K
    {
        if (!list.K)
            printf("\x1b[31;1mСмотри на нас, мы все давно смирились\x1b[0m\n");
        else
            printf("\x1b[31;1mСмотри на нас убийца, мы все давно смирились\x1b[0m\n");
        if (list.Water==1 && !list.K)
        {
            printf("\x1b[31;1mПусты остатки океана, его наполнить нужно нам, отдав последнее, что есть в карманах, а может лишь кусок коралла\x1b[0m\n");
            if ((check=invobserv(check, "\x1b[35;1m&"))!=NULL)
            {
                *check="\x1b[33;1m!";
                deepdesert[7][7]='~';
                list.Water=-2;
                printf("\x1b[33;1mТеперь мой путь лежит в оазис, остатки от кораллов оставлены на память\x1b[0m\n");
                life+=1;
                list.K++;
            }
            else if ((check=invclean(check))!=NULL)
            {
                *check=" ";
                while((check=invclean(check))!=NULL)
                    *check=" ";
                deepdesert[7][7]='~';
                list.Water=-2;
                list.K++;
                printf("\x1b[33;1mЗияет черная дыра в авоське, добраться до оазиса и повторить все козни, так быстротечна память\x1b[0m\n");
            }
            else
            {
                printf("\x1b[31;1mНа что рассчитывал ты? Убийца у которого нет за душей и цента\x1b[0m\n");
                list.K++;
            }
        }
    }
    else if(INTERACT=='*')
    {
        if (!list.Grace)
        {
            if ( (check=checkinv(check))!=NULL)
            {
                *check="\x1b[32m*";
                list.Grace=1;
                printf("\x1b[33;1mЗеленый цвет ласкает мой усталый взор\x1b[0m\n");
                life+=1;
            }
            else
                 printf("\x1b[33;1mЯ\x1b[0m \x1b[32mчто-то \x1b[33;1mупускаю, мечта - освободить карманы\x1b[0m\n");
        }
        else if (list.Grace)
            printf("\x1b[33;1mПрекрасный шелест, ласкает душу запах и есть запал на пару благих дел\x1b[0m\n");
    }
    else if(INTERACT=='J')
    {
        if ((check=invobserv(check, "\x1b[32m*"))!=NULL && list.J==-2)
        {
            printf("\x1b[31;1mРад видеть, слышать и сказать, что до смирения один шаг остался, до поедающих твой труп червей. Раскуримся, сосед\x1b[0m\n");
            list.J++;
            check=deleteinv(check, "\x1b[32m*");
            list.Grace=0;
            life+=4;
        }
        else if ((check=invobserv(check, "\x1b[32m*"))!=NULL && list.J==-1)
        {
            printf("\x1b[31;1mНу раз так мило мы сидим, чтож, неоткажусь, дружище\x1b[0m\n");
            list.J++;
            check=deleteinv(check, "\x1b[32m*");
            list.Grace=0;
            life+=4;
        }
        else if ((check=invobserv(check, "\x1b[32m*"))!=NULL && list.J==0)
        {
            printf("\x1b[31;1mВедь этот K, каков глупец, все время ноет про смирение, но вижу я, что наше время, еще дает шанс закурить\x1b[0m\n");
            list.J++;
            check=deleteinv(check, "\x1b[32m*");
            list.Grace=0;
            life+=4;
        }
        else if ((check=invobserv(check, "\x1b[32m*"))!=NULL && list.J==1)
        {
            printf("\x1b[31;1mИ пусть с этим глупцом тут бывший вор да пара трупов, мы выкинем тяжести души, не пожалея и минуты!\x1b[0m\n");
            list.J++;
            check=deleteinv(check, "\x1b[32m*");
            list.Grace=0;
            if (life<=20)
                life=21;
            printf("\x1b[33;1mКак будто начал понимать! Спасибо, друг, я \x1b[32;1mсозерцаю\x1b[0m\n");
        }
        else if ((check=invobserv(check, "\x1b[32m*"))!=NULL && list.J==2)
            printf("\x1b[31;1mСпокойно парень, попридержи свою душонку, мне нужно спать и если вдруг ты доживешь, то приходи, друг, на рассвете\x1b[0m\n");
        else
              printf("\x1b[31;1mПоближе к морю бы вернуться, пески мозолят мне глаза и попадают не туда, где бы хотелось видеть их\x1b[0m\n");
    }
}

void finalsand(char *item, int isitem)
{
    char *staff[9]={"@", "\x1b[36;1m%", "&", "\x1b[35;1m&", "(", "\x1b[31;1mX", "\x1b[32;1m~", "\x1b[33;1m!", "\x1b[32m*"};
    if (isitem)
    {
        if (strcmp(item, staff[0])==0)
            printf("\x1b[32;1mРасколотое прошлое разлилось приливом, у берега с заплаканным лицом, застыло\x1b[0m\n");
        else if (strcmp(item, staff[1])==0)
            printf("\x1b[32;1mВоспоминаниями, ничем материальным\x1b[0m\n");
        else if (strcmp(item, staff[2])==0)
            printf("\x1b[32;1mИ \x1b[0mисполины \x1b[32;1mумирают, они не помнили, но знали\x1b[0m\n");
        else if (strcmp(item, staff[3])==0)
            printf("\x1b[32;1mСовсем как будто бы живые, но все давно уже мертвы, лишь память сохранять безумцы, которым некуда идти\x1b[0m\n");
        else if (strcmp(item, staff[4])==0)
            printf("\x1b[32;1mВ морях мы плавали и жили, на солнце превратимся в пыль\x1b[0m\n");
        else if (strcmp(item, staff[5])==0)
            printf("\x1b[32;1mПоследнее, что помню, как видел темноту и чувствовал ничего\x1b[0m\n");
        else if (strcmp(item, staff[6])==0)
            printf("\x1b[32;1mКак славно все же при себе иметь, кусочек океана, умирая в пыли и песке, вам рано, а мне пора уже идти\x1b[0m\n");
        else if (strcmp(item, staff[7])==0)
            printf("\x1b[32;1mОн называл меня убийцей, но отдал мне кусочек море, с ним сердце не начнет вновь биться, но я спокоен\x1b[0m\n");
        else if (strcmp(item, staff[8])==0)
            printf("\x1b[32;1mМы курили\x1b[0m\n");
    }
}

void deepout(void)
{
    finalsand(inv.item1, inv.isitem1);
    finalsand(inv.item2, inv.isitem2);
    finalsand(inv.item3, inv.isitem3);
}

int redbox(void)
{
    if (strcmp(inv.item1, "@")==0)
        if (strcmp(inv.item2, "(")==0)
            if (strcmp(inv.item3, "\x1b[31;1mX")==0)
            {
                printf("\x1b[31;1mТы отыскал мою коробку\nТы не найдешь тут красоты\nНо может быть найдешь заточку\nИ надпись \"Сломано\" внутри\x1b[0m\n");
                return 1;
            }
    return 0;
}

char** checkinv(char** check)
{
    if (inv.isitem1==0)
    {
        check=&inv.item1;
        inv.isitem1=1;
        return check;
    }
    else if (inv.isitem2==0)
    {
        check=&inv.item2;
        inv.isitem2=1;
        return check;
    }
    else if (inv.isitem3==0)
    {
        check=&inv.item3;
        inv.isitem3=1;
        return check;
    }
    return NULL;
}

char** invclean(char **iclean)
{
    if (inv.isitem3==1)
    {
        iclean=&inv.item3;
        inv.isitem3=0;
        return iclean;
    }
    else if (inv.isitem2==1)
    {
        iclean=&inv.item2;
        inv.isitem2=0;
        return iclean;
    }
    else if (inv.isitem1==1)
    {
        iclean=&inv.item1;
        inv.isitem1=0;
        return iclean;
    }
    return NULL;
}

char** invobserv(char **check, char *item)
{
    if (strcmp(inv.item1, item)==0)
    {
        check=&inv.item1;
        return check;
    }
    else if (strcmp(inv.item2, item)==0)
    {
        check=&inv.item2;
        return check;
    }
    else if (strcmp(inv.item3, item)==0)
    {
        check=&inv.item3;
        return check;
    }
    return NULL;
}

char** deleteinv(char **check, char *item)
{
    if (strcmp(inv.item1, item)==0)
    {
        inv.item1=" ";
        inv.isitem1=0;
        check=&inv.item1;
        return check;
    }
    else if (strcmp(inv.item2, item)==0)
    {
        inv.item2=" ";
        inv.isitem2=0;
        check=&inv.item2;
        return check;
    }
    else if (strcmp(inv.item3, item)==0)
    {
        inv.item3=" ";
        inv.isitem3=0;
        check=&inv.item3;
        return check;
    }
    return NULL;
}



void emptyobject(void)
{
    // Инвентарь
    inv.isitem1=0;
    inv.isitem2=0;
    inv.isitem3=0;

    inv.item1=" ";
    inv.item2=" ";
    inv.item3=" ";
    // Ивенты
    list.Y=-2;
    list.Grace=0;
    list.Korall=-3;
    list.K=0;
    list.Rock=0;
    list.J=-2;
    list.Bones=-1;
    list.Skull=0;
    list.Water=-2;
    list.X=0;
    list.xx=0;
    list.twox=0;
    list.Gem=0;
    list.Seaimage=0;
}


void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void seacheck(char *s)
{
    for(int i=0; s[i]!='\0'; i++)
    {
        if (s[i]=='n')
        {
            s[i]='\0';
            break;
        }
    }
}
