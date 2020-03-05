#ifndef QUIZ_H
#define QUIZ_H
#include "genDLList.h"
#include <string>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
char GUESS;
int POINTS=0;
int count_of_movies=0;
int Type_of_question;
string GLOBAL_MODIFY;

class Question              //sorular için ayrı bi class var burda sorunun hazırlanısı ve şıklar belli olcak
{
public:
    void setValue(string,string,string,string,string,string,int);
	void askQuestion();
    void Player_Guess();
private:
	string Question_Text;
	string Answer_1;
	string Answer_2;
	string Answer_3;
	string Answer_4;
	string Correct_Answer;
    char right_chic;
    char right_chic2;

    int Question_Score;


};

void Question::setValue(string q,string a1,string a2,string a3,string a4,string ca,int pa)
{
	Question_Text=q;
	Answer_1=a1;
	Answer_2=a2;
	Answer_3=a3;
	Answer_4=a4;
	Correct_Answer=ca;
    Question_Score=pa;
}

void Question::askQuestion()
{   int random_answer,i,m,count=0,memory[4]={99,98,97,96};      //bu memoryinin içini doldurarak randım attıgı şıkkı bır daha atmasın dıye
    char j;
    string random_answers[4]={Answer_1,Answer_2,Answer_3,Answer_4}; //aslında hep dorduncu cevap dogru cevap seklınde buraya yollanıyor
    cout<<Question_Text<<endl;                  //soru texti
    cout<<endl;
    for(i=0,j='A';i<4;i++,j++)
    {   count=0;
        random_answer=(rand()%(3-0+1)+0);               //burda amac şıkların yerını karıstırmak
        for(m=0;m<4;m++)
        {
            if(random_answer != memory[m])
            {
                count++;
            }

            if(random_answer == memory[m])
            {
                random_answer=(rand()%(3-0+1)+0);           //eger aynı şıkkı bı kere random attıysa gene random atmalı
                m=-1;
                count=0;
            }

            if(count==4)
            {
                memory[i]=random_answer;
            }

        }

        cout<<j<<". "<<random_answers[random_answer]<<endl;
        if(random_answers[random_answer]==Correct_Answer)
        {
            right_chic=j;
            right_chic2=tolower(j);                         //cevap şıkkı kucuk veya buyuk farketmesın dıye

        }
    }


    //cout<<"Correct answer is "<<Correct_Answer<<endl;                //YOU CAN UNCOMMAND THIS PART IF YOU WANT TO SEE THE ANSWERS WHILE PLAYING
    cout<<endl;
    cout<<"(+"<<Question_Score<<")"<<endl;

}
void Question::Player_Guess()                               //kullanıcının dogru cevap verip vermedıgı burda karsılastırılıyor
{
    if(GUESS==right_chic || GUESS==right_chic2)
    {
        cout<<"YOU ARE CORRECT :) "<<endl;
        POINTS=POINTS+10;
        cout<<endl;
        cout<<"Current point is : "<<POINTS<<endl;
    }
    else
    {
        cout<<"SORRY YOU ARE WRONG :( "<<endl;
        cout<<"Correct answer is "<<Correct_Answer<<endl;
        cout<<endl;
        cout<<"Current point is : "<<POINTS<<endl;
    }
}
class quiz
{

public:

    string Modify_movie(string movie_name, string new_movie_year);
    string find_random_movie();
    string find_movie_year(string movie_line);
    string find_movie_name(string movie_line);
    string Remove_movie(string movie_name);
    string Random_movie();
    void print_List();
    void AddMainMovies(string main_movie_name);
    void which_year_question(string random_movie);
    void which_movie_question(string random_movie);
    void Player_Answer(char guess);
    void Final_Score();
    void Print_movies_according_year(string input_year);
    int is_it_already_exist(string movie_name);
    int Good_input_for_add_movie(string movie_name);

private:
        DoublyLinkedList<string> movies_list2;
        Question q1;
        Question q2;



};
void quiz::print_List()
{
        movies_list2.printAll();
}

void quiz::AddMainMovies(string main_movie_name)
{

    movies_list2.addToDLLTail(main_movie_name);
    count_of_movies++;
}
string quiz::find_random_movie()                    //listeden random bı fılm secmek ıcın doubly lınked lıste random bı node bulunuyor
{
    int random_movie;
    srand(time(NULL));
   // cout<<"count of movies: "<<count_of_movies<<endl;
    random_movie=rand()%(count_of_movies);
   // cout<<"random movie number"<<random_movie<<endl;
    string *a;
    string b;
    a=movies_list2.find(random_movie);


    b=*a;

    return b;



}

string quiz::Random_movie()             //yukarda bulunan nod string olarak random movie burda alınıyor mainde cagırmak ıcım daha kolay
{
    string random_movie;
    random_movie=find_random_movie();
    return random_movie;
}

string quiz::find_movie_name(string movie_line)             //text dosyasında movie name ve date i birlesik oldugundan burda sadece film ismini alıyor
{
    string movie_name;

    size_t pos = movie_line.find("/");
    movie_name=movie_line.substr (0,pos);

    return movie_name;
}

string quiz::find_movie_year(string movie_line)         //burdada film ismiyle tarihi ayırarak filmin tarihini buluyor
{
   string movie_year;

    size_t pos = movie_line.find("/");
    movie_year=movie_line.substr (pos+1);
    return movie_year;
}

void quiz::Player_Answer(char guess)
{
    GUESS=guess;
    if(Type_of_question==1)             //hangi yıl sorusu
    {
        q1.Player_Guess();
    }

    if(Type_of_question==2)         //hangi film sorusu
    {
        q2.Player_Guess();
    }
}

void quiz::which_year_question(string random_movie)         //hangi yıl sorusu hazırlanısı
{
    Type_of_question=1;
    string MOVIE_NAME=find_movie_name(random_movie);            //ilk olarak random bı film alınıyor ve name ile date i ayrılıyor
    string MOVIE_YEAR=find_movie_year(random_movie);
    string other_movie_years[4]={"0","1","2",MOVIE_YEAR};
    for(int i=0;i<3;i++)
    {
        int count=0;                                        //diger sıklar ıcın de random year gereklı ancak dogru sıkdan ıkı tane olamaz bu yuzden memoryde
        string A=find_random_movie();                       //şıklar ıcın alınan random yearlar tutuluyor ve karsılastırılıyor
        string B=find_movie_year(A);

        for(int j=0;j<4;j++)
        {
            if(B!=other_movie_years[j])
            {
                count++;
            }

            if(j==3 && count!=4)
            {
                 A=find_random_movie();
                 B=find_movie_year(A);                  //eger bızım fılmın yılıysa bı random daha at
                 j=-1;
                 count=0;

            }

            if(count==4)
            {
                other_movie_years[i]=B;
            }


        }


    }
                                                                    //sorusu bızım fılm ve random movie yearlar sorulmak uzere question classına gıdııyor


    q1.setValue("Which year was the movie '" + MOVIE_NAME + "' released?",other_movie_years[0],other_movie_years[1],other_movie_years[2],MOVIE_YEAR,MOVIE_YEAR,10);
    q1.askQuestion();

}

void quiz::which_movie_question(string random_movie)        //bu yılda hangi film cıktı sorusu
{
       Type_of_question=2;
       string MOVIE_NAME=find_movie_name(random_movie);         //random bı fılm alınıyor ve tarihi ile ısmını ayırıyoruz
       string MOVIE_YEAR=find_movie_year(random_movie);
       string other_movie_names[4]={"0","1","2",MOVIE_NAME};        //aynı yılda bı kac fılm cıkmıs olabılır bunlar sıkkımızda olmamalı o yuzden memory tutuyoruz
       for(int i=0;i<3;i++)                                         //sıklarda ıkı tane aynı fılmı gormekte ıstemeyız
       {
           int count=0;
           string A=find_random_movie();
           string B=find_movie_name(A);
           string C=find_movie_year(A);
           for(int j=0;j<4;j++)
           {
               if(B!=other_movie_names[j] && C!=MOVIE_YEAR)         //dıger sıklar ıcın alınan fılm bızım fılmımızle aynısı olmamalı ve tarıhlerı aynı olmamalı
               {
                   count++;
               }

               if(j==3 && count!=4)
               {
                    A=find_random_movie();
                    B=find_movie_name(A);
                    C=find_movie_year(A);
                    j=-1;
                    count=0;

               }

               if(count==4)
               {
                   other_movie_names[i]=B;
               }


           }


       }



       q2.setValue("Which year the following movies was released in " + MOVIE_YEAR + "?",other_movie_names[0],other_movie_names[1],other_movie_names[2],MOVIE_NAME,MOVIE_NAME,10);
       q2.askQuestion();
}

void quiz::Final_Score()
{
    cout<<"                                           ********************"<<endl;
    cout<<"QUIZ ENDS.I HOPE YOU ENJOYED. HERE IS YOUR **FINAL SCORE : "<<POINTS<<" *"<<endl;            //10 soru sonucunda alınan toplam puan
    cout<<"                                           ********************"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    POINTS=0;
}

void quiz::Print_movies_according_year(string input_year)       //verilen yıla gore fılm ısımlerı basma
{
    int exist=0;
    string *a;
    string movie,movie_name;
    cout<<"Movies that has been realeased in "<<input_year<<" are : "<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    if(input_year.size() < 4)
    {
        cout<<"ERROR NOT A VALID YEAR"<<endl;           // 1 yılında fılm cıkamayacagına gore en az dort basamaklı bı yıl valıd input
    }
    else
    {
        for(int i=0;i<count_of_movies;i++)
        {
            a=movies_list2.find(i);
            movie=*a;                                       //yılı verıldıgı ıcın sadece fılm ısmını basıyoruz
            size_t pos = movie.find(input_year);
            if(pos<100)
            {
            movie_name=movie.substr(0,pos-1);
            cout<<movie_name<<endl;
            exist=1;
            }

        }
          cout<<endl;
        if(exist==0)
        {
            cout<<"--------------------------------------------------"<<endl;
            cout<<"SORRY.There is no such movie in list "<<endl;                        //listede o yılla aıt herhangı bı fılm yoksa
             cout<<"--------------------------------------------------"<<endl;
            cout<<endl;
        }
    }
}

string quiz::Remove_movie(string movie_name)                //doubly linked listimizden ismi girilen filmi silcez
{
   string *a,movie;
   string no="no";
    int exist=0;
    char answer;
    int thisismymovie;
    for(int i=0;i<count_of_movies;i++)
    {
        a=movies_list2.find(i);
        movie=*a;                                       //filmler arasında ıstene fılm aranıyor
        size_t pos = movie.find(movie_name);
        if(pos<100)
        {

            cout<<endl;
            cout<<"The movie you entered is "<<movie<<" (yes:1 no:0)"<<endl;            //eger partial bi isim girildiyse istediginiz film bu mu did you mean?
            cout<<endl;
            cout<< "ENTER : ";
            cin>>thisismymovie;
            cout<<endl;
            if(thisismymovie==1)
            {
                exist=1;
                cout<<endl;
                cout<<"You sure want to remove this movie?  (Y/N) "<<endl;          //filmi  son bi kere daha kaldırılıp kaldırılmacagını soruyor
                cout<<"ENTER : ";
                cin>>answer;
                cout<<endl;
                if(answer=='Y' || answer=='y')              //kucuk buyuk harf cevap farketmez
                {
                    movies_list2.deleteNode(movie);
                    count_of_movies--;                      //filmi linked listimizden cıkardık
                    return movie;
                }

                if(answer=='N' || answer=='n')
                {
                    cout<<"Movie will not remove"<<endl;            //filmi cıkarmaktan vazgecıldı
                    return no;
                }

                else
                {
                    cout<<"ERROR UNVALID INPUT"<<endl;          //son kararınız mı sorusuna unvalid bi input girildi
                    return no;
                }

            }
        }

    }

   if(exist==0)
    {
        cout<<endl;
        cout<<"SORRY.THERE IS NO SUCH MOVIE"<<endl;         //cıkarmak ıstedıgı fılm zaten listemizde yok
        return no;


    }
}

string quiz::Modify_movie(string movie_name,string new_movie_year)          //ismi girilen filmin tarihinde bi degisiklik yapmak ıcın
{
     string *a,movie;
     string no="no";
     int exist=0;
     char answer;
     int thisismymovie;
     if(new_movie_year == "no")
     {
     for(int i=0;i<count_of_movies;i++)
     {
         a=movies_list2.find(i);
         movie=*a;
         size_t pos = movie.find(movie_name);
         if(pos<100)
         {
             if(new_movie_year == "no")
             {
                 cout<<"The movie you entered is "<<movie<<" (yes:1 no:0)"<<endl;       //filmin adı partial girilirse did you mean?
                 cout<<endl;
                 cout<< "ENTER : ";
                 cin>>thisismymovie;
                 cout<<endl;
                 if(thisismymovie==1)
                 {
                 exist=1;
                 string yes="yes";
                 GLOBAL_MODIFY=movie;
                 return yes;
                 }

             }
         }
     }

     }

             else
             {
                  if(find_movie_year(GLOBAL_MODIFY)==new_movie_year)        //degistirilmek istenen tarihi gene aynı yıl gırerse error
                  {
                      cout<<"IT IS ALREADY THAT YEAR?!?!"<<endl;
                      exist=1;
                      return no;
                  }
                  else
                  {
                     cout<<"You sure want to modify this movie?  (Y/N) "<<endl; //tarihin degistirilmesinden emin misin?
                     cout<<"ENTER : ";
                     cin>>answer;
                     cout<<endl;
                     exist=1;

                     if(answer=='Y' || answer=='y')
                     {
                         movie_name=find_movie_name(GLOBAL_MODIFY);
                         string modified_version=movie_name+'/'+new_movie_year;         //filmi tarihi yenilenmis bi şekılde linked listimize atıyor
                         movies_list2.deleteNode(GLOBAL_MODIFY);
                         movies_list2.addToDLLTail(modified_version);
                         return GLOBAL_MODIFY;
                     }

                     if(answer=='N' || answer=='n')
                     {
                         cout<<"Movie will not modify"<<endl;       //tarihi degistirmekten vazgecildi
                         return no;
                     }

                     else
                     {
                         cout<<"ERROR UNVALID INPUT"<<endl;         //unvalid bi giris yapıldı

                         return no;
                     }
                 }
             }






    if(exist==0)
     {
         cout<<endl;
         cout<<"SORRY.THERE IS NO SUCH MOVIE"<<endl;                //ismi girilen film listemizde yer almıyor
         cout<<"****Press enter for continue****"<<endl;
         return no;


     }
}

int quiz::is_it_already_exist(string movie_name)            //filmin zaten listede olup olmadıgı check edılıyor add movie ıcın
{
     int approved;
     approved=movies_list2.isInList(movie_name);
     return approved;

}

int quiz::Good_input_for_add_movie(string movie_name)       //add movie icin good input checki ıstenılen sekılde gırmeyınce error verıp kullanıcının
{                                                           //nerde hatalı oldugunu neyı koymayı unuttugunu gosteren
     int count=0;
     size_t pos2=101,pos3=101,pos4=101;
     size_t pos = movie_name.find("/");

     if(pos>100)
     {
         cout<<"YOU FORGOT TO PUT '/'  "<<endl;             //fillm adı ve tarihi ayırmak icin gerekn "/" konmamıssa
         return -1;
     }
     else
     {
        for(char i='A';i<='Z' && pos2>100 && pos3>100 ;i++)
        {
            pos2 = movie_name.find(i);                          //herhangi bi film adı girilmemis ise
            char lower=tolower(i);
            pos3 = movie_name.find(lower);
        }

        if(pos2>100 && pos3>100)
        {
            cout<<"YOU FORGOT TO PUT MOVIE NAME"<<endl;
            return -1;
        }

        else
        {

             for(char j='0';count<10 && pos4>100 ;j++)              //herhangi bi tarih girilmemisse
             {
                 pos4=movie_name.find(j);
                 count++;

             }

             if(pos4>100)
             {
                 cout<<"YOU FORGOT TO PUT DATE"<<endl;
                 return -1;
             }
                string no_space=movie_name.substr(pos+1,1);         //film adı ve "/" den sonra bosluk bırakılmamsı grektıgını uyarıyor
             if(no_space==" ")
             {
                 cout<<"DO NOT PUT SPACE BETWEEN '/' AND YEAR!!! DO LIKE : Titanic/1991"<<endl;
                 return -1;
             }

             else
             {
                 return 1;
             }

        }


     }
}

#endif 
