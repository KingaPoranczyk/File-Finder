#include "FileFinder.h"
#include <iostream>
//#include <windows.h>
#include <thread>
#include <chrono>
#include <filesystem>
#include <map>
#include <algorithm>
#include <vector>


using namespace std;
using namespace std::filesystem;

int main()
{
    cout << "=== FILE FINDER ===\n";
    this_thread::sleep_for(chrono::seconds(1));
    //Sleep(1000);

    string sciezka;
    cout << "Podaj folder: ";
    getline(cin >> ws,sciezka);

    if (exists(sciezka) && is_directory(sciezka)){
        cout << "Poprawnie podano sciezke: " << sciezka << endl;
    }else{
        cout << "Folder nie istnieje / Blednie wprowadzono sciezke." << endl;
        return 0;
    }

    //Sleep(1000);
    this_thread::sleep_for(chrono::seconds(1));
    //system("cls");
    system("clear");

    int wybor;
    do{
        //system("cls");
        system("clear");
        cout << "Wczytana sciezka: " << sciezka << endl;
        cout << "Co chcesz zrobic?\n";
        cout << "[1] Wyswietl wszystkie pliki.\n";
        cout << "[2] Wyszukaj plik po nazwie.\n";
        cout << "[3] Wyszukaj plik po rozszerzeniu.\n";
        cout << "[4] Pokaz pliki wieksze niz X Mb.\n";
        cout << "[5] Statystyki folderu.\n";
        cout << "[0] Zamknij program.\n";
        cin >> wybor;

        switch(wybor){
            case 0:
                break;
            case 1: {
                wyswietlPliki(sciezka);
                break;
            }
            case 2: {
                szukajPoNazwie(sciezka);
                break;
            }
            case 3: {
                rozszerzenieWyswietlanie(sciezka);
                break;
            }
            case 4:{
                wyswietlajPlikiWiekszeNiz(sciezka);
                break;
            }
            case 5:{
                statystykiFolderu(sciezka);
                break;
            }
            default:
                cout << "Niepoprawnie wprowadzony wybor";
                break;
        }
        if (wybor != 0) {
            cout << "\nAby wrocic do menu nacisnij dowolny klawisz...\n";
            cin.ignore();
            cin.get();
        }
    }while(wybor != 0);

    return 0;
}