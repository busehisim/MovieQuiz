#include "quiz.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cctype>
#include "genDLList.h"


using namespace std;

int main()
{	
    quiz movies_list;
    string line;
    char question_answer,one_more_time='Y';
    int menu_answer=99;

    ifstream File_Read;
    File_Read.open("movies.txt");
    if (File_Read.is_open())
    {
        while (getline(File_Read,line))        //opens the file and reads the inputs in a string
        {


			movies_list.AddMainMovies(line);

        }
    
    File_Read.close();
	}
    else
    {
        cout<<"file is not open"<<endl;
    }

	
    //movies_list.print_List();        //uncommanla bütün yüklenmiş filmlerin listesini görebiliriz

    cout<<"*******WELCOME TO MOVIE QUIZ*******"<<endl;
    cout<<endl;
    cout<<"MENU"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;

    while(menu_answer!=6)
    {
        cout<<"choose one of the followings"<<endl;
        cout<<"1.Start the quiz"<<endl;
        cout<<"2.Add movies"<<endl;
        cout<<"3.Remove movie"<<endl;
        cout<<"4.Modify movie"<<endl;
        cout<<"5.List movies according to year"<<endl;
        cout<<"6.QUIT"<<endl;
        cout<<"7.ERROR CHECK LIST AND RULES"<<endl;
        cout<<endl;
        cout<<"Enter : ";
        cin>>menu_answer;
        cout<<endl;
        if(menu_answer<1 || menu_answer>7)                      //menu dısında bı secenekte error vercektır
        {
            cout<<"***ERROR***"<<endl;
            cout<<"SHUTTING DOWN THE PROGRAM"<<endl;
            return 0;
        }




        if(menu_answer==1)                                                          ///START GAME
        {   one_more_time='Y';
            while(one_more_time == 'Y' || one_more_time == 'y')      //10 soru bıttıkten sonra bir el daha oynamak ister mi?
            {
                cout<<"YOU ARE ABOUT TO GET START. ENJOY :)"<<endl;
                string movie_name_memory[10]={"1","2","3","4","5","6","7","8","9","10"};  //random filmler burda alınıp bi memoryde saklanıyor

                int count=0;
                for(int m=0;m<10;m++)
                 {                                                              //buranın amacı dusuk ıhtımal olsada aynı film sorusu gelmesın
                    count=0;
                    string random_movie=movies_list.Random_movie();
                    for(int j=0;j<10;j++)
                    {
                        if(random_movie!=movie_name_memory[j])
                        {
                            count++;
                        }

                        if(count==10)
                        {
                            movie_name_memory[m]=random_movie;
                        }

                        if(count!=10 && j==9)
                        {
                            random_movie=movies_list.Random_movie();
                            count=0;
                            j=-1;
                        }

                    }
                  }


                    int i,r;
                    for(i=1,r=0;i<=10;i++,r++)                  //10 adet soru sorulcak bir elde
                    {

                        cout<<"-------------------------------------------------------------"<<endl;
                        int random_question_type=(rand()%(1-0+1)+0);            //film ismine göre mi yoksa tarihine mi göre oldugu random secılıyor
                        if(random_question_type==0)                             //randomda hangi yılda soru seklı gelmisse
                        {
                            cout<<i<<". ";
                            movies_list.which_year_question(movie_name_memory[r]);
                            cout<<endl;
                            cout<<"Your answer is : ";
                            cin>>question_answer;
                            if ((question_answer >= 'A' && question_answer <= 'D') || (question_answer >= 'a' && question_answer <= 'd')) //şıklar büyük veya küçük girilebilir
                            {
                                movies_list.Player_Answer(question_answer);
                                cin.clear();
                                fflush(stdin);              //amac kullanıcı AAA girse dahi sonraki cin lerin yerine gecmemesi için
                            }
                            else
                            {
                                cout<<endl;
                                cout<<"***ERROR***"<<endl;   //A,B,C,D sıkları haricinde gecersiz bi input girildi kullanıcıya bir daha dogru girmesi icin soruluyor
                                int flag=0;
                                question_answer='e';
                                while(flag==0)
                                {
                                    cout<<endl;
                                    cout<<"Enter a valid input"<<endl;
                                    cout<<"Your new answer is : ";
                                    cout<<endl;
                                    cin>>question_answer;
                                    if ((question_answer >= 'A' && question_answer <= 'D') || (question_answer >= 'a' && question_answer <= 'd'))
                                    {
                                        flag=1;
                                    }
                                }
                                movies_list.Player_Answer(question_answer);                 //kullanıcın cevabı methoda giderek dogruluguna bakılıyor
                                cin.clear();
                                fflush(stdin);

                            }

                        }
                        if(random_question_type==1)                 //randomda hangi film su tarihte cekılmıstır sorusu gelmıstır
                        {
                            cout<<i<<". ";
                            movies_list.which_movie_question(movie_name_memory[r]);
                            cout<<endl;
                            cout<<"Your answer is : ";
                            cin>>question_answer;
                            if ((question_answer >= 'A' && question_answer <= 'D') || (question_answer >= 'a' && question_answer <= 'd'))
                            {
                                movies_list.Player_Answer(question_answer);
                                cin.clear();
                                fflush(stdin);                                      //amac kullanıcı AAA girse dahi sonraki cin lerin yerine gecmemesi için
                            }
                            else
                            {
                                cout<<endl;
                                cout<<"***ERROR***"<<endl;
                                question_answer='e';
                                int flag=0;
                                while(flag==0)
                                {
                                    cout<<endl;
                                    cout<<"Enter a valid input"<<endl;          //A,B,C,D sıkları haricinde gecersiz bi input girildi kullanıcıya bir daha dogru girmesi icin soruluyor
                                    cout<<"Your new answer is : ";
                                    cout<<endl;
                                    cin>>question_answer;
                                    if ((question_answer >= 'A' && question_answer <= 'D') || (question_answer >= 'a' && question_answer <= 'd'))
                                    {
                                        flag=1;
                                    }
                                }
                                movies_list.Player_Answer(question_answer);                 //kullanıcın cevabı methoda giderek dogruluguna bakılıyor
                                cin.clear();
                                fflush(stdin);
                            }

                         }
                        cout<<endl;
                        if(i!=10)
                        {
                            cout<<"here comes the next question"<<endl;
                        }

                    }
                    movies_list.Final_Score();              //10 soru sonrası final score gosterlıyor
                    cout<<endl;
                    cout<<"Play one more time? (Y/N)"<<endl;            //bir el daha ister misin sorusu
                    cout<<"Enter : ";
                    cin>>one_more_time;
                    if(one_more_time != 'Y' && one_more_time != 'y' && one_more_time != 'N' && one_more_time != 'n'  )
                    {
                        cout<<endl;
                        cout<<"***ERROR***"<<endl;
                        cout<<"GO BACK TO MAIN MENU"<<endl;

                    }
                    cin.clear();
                    fflush(stdin);
                    cout<<endl;
             }
        }

        if(menu_answer==2)                  /////ADD MOVIE
        {
            int approved,good_input;
            string input_movie;
            ofstream File_Write;
            cin.ignore();
            cout<<"Enter the movie you want to add to the list"<<endl;
            cout<<"The rule is enter the movie name , there shouldn't be space between date and movie name and put roman number if it is necessary. Example : The Godfather Part II/1974"<<endl;
            cout<<endl;
            cout<<"Enter : ";
            getline(cin, input_movie);

            int m;
            for(m=0;input_movie[m]!= '/';m++)                   //kullanıcı büyük küçük farketmez girdigini ilk harfleri büyük gerisi küçük seklınde donusturme
            {
                if(islower(input_movie[0]) && m==0)
                {
                    input_movie[0]=toupper(input_movie[0]);
                    m++;
                }

                else if(m==0)
                {
                    m++;
                }

                if(isspace(input_movie[m]))
                {
                    m++;
                    if(islower(input_movie[m]))
                    {
                        input_movie[m]=toupper(input_movie[m]);
                        m++;
                    }

                    else
                    {
                        m++;
                    }
                }

                if(isupper(input_movie[m]))
                {
                    input_movie[m]=tolower(input_movie[m]);
                }

            }


            good_input=movies_list.Good_input_for_add_movie(input_movie);       //eklenmek istenen filmin yazılması gereken sekılde yazılıp yazılmadıgı check
            if(good_input!=-1)
            {
               approved=movies_list.is_it_already_exist(input_movie);       //yazım seklı dogru pekı bu film zaten listede var mı?

                if(approved==1)
                {
                    cout<<"The movie already exist.You can't add the same movie!!!"<<endl;
                    cout<<endl;
                    cout<<"-------------------------------------------------------------"<<endl;

                }

                else
                {
                   File_Write.open("movies.txt", std::ios_base::app);           //text dosyasınada filmimiz ekleniyor
                    if (File_Write.is_open())
                    {
                           File_Write<<input_movie<<endl;
                           movies_list.AddMainMovies(input_movie); /// olmak zorundakı program bastan baslayıp listeyı almadıgı zamanda fılm eklenmıs olsun


                    File_Write.close();
                    }
                    else
                    {
                        cout<<"file is not open"<<endl;
                    }
                  //cout<<"YENI FILM LISTESI ---------------------------"<<endl;
                   //movies_list.print_List();
               }

            }
            else
            {
                cout<<endl;
                cout<<"***ERROR***"<<endl;                      //film istenilen sekılde girilmemistir
                cout<<"GO BACK TO MAIN MENU "<<endl;
                cout<<endl;
            }
        }

       if(menu_answer==3)               ///REMOVE A MOVIE
        {
            string movie_name,delete_line,line2;
            cin.ignore();
            cout<<"You are about to remove a movie from list"<<endl;
            cout<<"Please enter the movie name you want to remove from list"<<endl;
            cout<<endl;
            cout<<"!!!!!!WARNING : YOU CAN WRITE PARTIAL NAME OF THE MOVIE BUT YOU SHOULD WRITE THE EXACT NAME OF THE MOVIE AS IT IS IN THE LIST !!!!!!"<<endl;
            cout<<"ENTER : ";
            getline(cin,movie_name);

            int k;
            for(k=0;movie_name[k]!= '/';k++)          //kullanıcı büyük küçük farketmez girdigini ilk harfleri büyük gerisi küçük seklınde donusturme
            {
                if(islower(movie_name[0]) && k==0)
                {
                    movie_name[0]=toupper(movie_name[0]);
                    k++;
                }

                else if(k==0)
                {
                    k++;
                }

                if(isspace(movie_name[k]))
                {
                    k++;
                    if(islower(movie_name[k]))
                    {
                        movie_name[k]=toupper(movie_name[k]);
                        k++;
                    }

                    else
                    {
                        k++;
                    }
                }

                if(isupper(movie_name[k]))
                {
                    movie_name[k]=tolower(movie_name[k]);
                }

            }

            delete_line=movies_list.Remove_movie(movie_name);
            cout<<"------------"<<endl;
            //movies_list.print_List();

            if(delete_line != "no")
            {
                ifstream fin;                   //silinen filmi text dosyasındanda silme öncelikle bi tmpde o film olmadan butun filmler geneden yazılır
                fin.open("movies.txt");         //kayıtlı movie text silinir ardından tmp ın adı movie text olarak degıstırılır
                ofstream temp;
                temp.open("temp.txt");

                while (getline(fin,line2))
                {
                    if (line2 != delete_line)
                    {
                    temp << line2 << endl;
                    }
                }

                temp.close();
                fin.close();
                remove("movies.txt");
                rename("temp.txt","movies.txt");
             }

        }

        if(menu_answer==4)                  ///MODIFY MOVIE YEAR
        {
                string movie_name,new_movie_year,answer,line3,modify;
                cin.ignore();
                cout<<"You are about to modify the year of a movie you choose"<<endl;
                cout<<"Enter the movie name  you want to modify"<<endl;
                cout<<"!!!!!!WARNING : YOU CAN WRITE PARTIAL NAME OF THE MOVIE BUT YOU SHOULD WRITE THE EXACT NAME OF THE MOVIE AS IT IS IN THE LIST !!!!!!"<<endl;
                cout<<"ENTER : ";
                getline(cin,movie_name);

                int k;
                for(k=0;movie_name[k]!= '/';k++)                 //kullanıcı büyük küçük farketmez girdigini ilk harfleri büyük gerisi küçük seklınde donusturme
                {
                    if(islower(movie_name[0]) && k==0)
                    {
                        movie_name[0]=toupper(movie_name[0]);
                        k++;
                    }

                    else if(k==0)
                    {
                        k++;
                    }

                    if(isspace(movie_name[k]))
                    {
                        k++;
                        if(islower(movie_name[k]))
                        {
                            movie_name[k]=toupper(movie_name[k]);
                            k++;
                        }

                        else
                        {
                            k++;
                        }
                    }

                    if(isupper(movie_name[k]))
                    {
                        movie_name[k]=tolower(movie_name[k]);
                    }

                }

                answer=movies_list.Modify_movie(movie_name,"no");       //check if the movie that user want to modify is a valid movie
                cin.ignore();
                int counter=0;
                if(answer != "no")
                {
                    cout<<"ENTER THE NEW YEAR YOU WANT : ";
                    getline(cin,new_movie_year);
                    for(int i=0;new_movie_year[i]!='\0';i++)
                    {
                        if(isdigit(new_movie_year[i])==1)                   //if its not a year check
                        {
                             counter++;
                        }
                    }

                    if(counter==new_movie_year.size())
                    {
                       modify=movies_list.Modify_movie(movie_name,new_movie_year);
                    }

                     else
                    {
                        cout<<"***ERROR WRONG INPUT***"<<endl;          //user did not entered a year
                        modify="no";
                    }

                    cout<<"------------"<<endl;

                    if(modify != "no")                              //modife edilmiş film text dosyasına kaydetmek
                    {
                        string modified_version=movie_name+'/'+new_movie_year;
                        ifstream Fin;
                        Fin.open("movies.txt");
                        ofstream temp;
                        temp.open("temp.txt");
                        if (temp.is_open())
                        {
                            while (getline(Fin,line3))
                            {
                                if (line3 != modify)
                                {
                                temp << line3 << endl;
                                }
                            }

                            temp<<modified_version<<endl;
                            temp.close();
                            Fin.close();
                            remove("movies.txt");
                            rename("temp.txt","movies.txt");
                         }

                        else
                         {
                             cout<<"file is not open"<<endl;
                         }
                    }
                }

        }

        if(menu_answer==5)                  ///LIST ACCORDING TO YEAR
        {
                string input_year;
                cout<<"Enter the year you want to print :";
                cin>>input_year;
                cout<<endl;
                movies_list.Print_movies_according_year(input_year);
                cout<<"-------------------------------------------------------------"<<endl;

        }

        if(menu_answer==6)        ////QUIT
        {
            cout<<"BYE BYE"<<endl;
            return 0;
        }

        if(menu_answer==7)
        {
            cout<<"1. SIKLAR KUCUK BUYUK FARK ETMEZ UNVALID SIKTA KULLANICIYA TEKRAR SORAR CEVABI"<<endl;
            cout<<"2. Y/N yada y/n KABULDUR HERHANGI BASKA BISEYDE ERROR VERIR"<<endl;
            cout<<"3. ADD MOVIE ZATEN BOYLE BI FILM VAR"<<endl;
            cout<<"4. ADD MOVIE ISTENILEN SEKILDE INPUT GIRILMEZSE ERROR VE KULLANICI HATASINI SOYLER"<<endl;
            cout<<"5. REMOVE VE MODIFY DA PARTIAL FILM ISMI GIRILEBILIR DID YOU MEAN DIYE SORAR"<<endl;
            cout<<"6. LIST MOVIE DE 4 HANEDEN AZ YILI KABUL ETMEZ"<<endl;
            cout<<"7. QUIZDE CEVABA AAA GIRILSE DAHI DIGER SORULARI OTOMATIK CEVAPLAMAZ BU YYYY ICINDE DAHIL"<<endl;
            cout<<"8. QUIZDE AYNI SORUYU BIR DAHA SORMAZ"<<endl;
            cout<<"9. REMOVE VE MODIFYDA ISLEM ONCESI SON BI KERE EMIN MISINIZ DIYE SORAR VE YANLIS INPUTTA ERROR VERIR"<<endl;
            cout<<"10. FILM TARIHINI ZATEN KENDI TARIHIYLE DEGISTIRMEYE CALISIRSA UYARI VERIR"<<endl;
            cout<<""<<endl;
        }




    }

return 0;
}
