#include "FileFinder.h"
#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace std::filesystem;

void maleLiterki(string& tekst) {
    for (char& znak : tekst) {
        znak = tolower(znak);
    }
}

string formatujLiczbe(double liczba, string jednostka) {
    ostringstream text;
    text << fixed << setprecision(2) << liczba;
    return text.str() + " " + jednostka;
}


string formatujRozmiar(uintmax_t bajty) {
    if (bajty < 1024) {
        return to_string(bajty) + " B";
    }
    double kb = bajty / 1024.0;
    if (kb < 1024) {
        return formatujLiczbe(kb, "KB");
    }
    double mb = kb / 1024.0;
    if (mb < 1024) {
        return formatujLiczbe(mb, "MB");
    }
    double gb = mb / 1024.0;
    return formatujLiczbe(gb, "GB");
}



void wyswietlPliki(const string& sciezka) {
    vector<path> pliki;
    for (const auto& plik : recursive_directory_iterator(sciezka)){
        if (plik.is_regular_file()) {
            pliki.push_back(plik.path());
            }
        }

    int wyborSortowania;

    cout << "Jak posortowac pliki?\n";
    cout << "[1] Nazwa A-Z\n";
    cout << "[2] Nazwa Z-A\n";
    cin >> wyborSortowania;

    if (wyborSortowania == 1) {
        sort(pliki.begin(),pliki.end(),[](const path& a, const path& b) {
        return a.filename() < b.filename();
    });
    }else if (wyborSortowania == 2) {
        sort(pliki.begin(),pliki.end(),[](const path& a, const path& b) {
        return a.filename() > b.filename();
    });
    }


    for (const  path& p : pliki) {
        cout << "Plik: " << p.filename() << endl;
        cout << "Folder: " << p.parent_path() << endl;
    }
}



void szukajPoNazwie(const string& sciezka) {
    string szukana_nazwa;
    cout << "Podaj nazwe szukanego pliku: ";
    bool znaleziono = false;
    getline(cin >> ws, szukana_nazwa);

    maleLiterki(szukana_nazwa);

    for (const auto& plik : recursive_directory_iterator(sciezka)) {
        if (plik.is_regular_file()) {
            path szukany_plik = plik.path();
            string nazwa_pliku = szukany_plik.filename().string();

            maleLiterki(nazwa_pliku);

            if (nazwa_pliku.find(szukana_nazwa) != string::npos) {
                cout << "Znaleziono: " << szukany_plik.filename() << endl;
                cout << "Folder: " << szukany_plik.parent_path() << endl;
                znaleziono = true;
            }
        }
    }
    if (znaleziono == false) {
        cout << "Nie znaleziono pliku.\n";
    }
}



void rozszerzenieWyswietlanie(const string& sciezka) {
    string rozszerzenie;
    cout << "Podaj z jakim rozszerzeniem chcesz wyswietlic pliki: " << endl;
    getline(cin >> ws,rozszerzenie);
    maleLiterki(rozszerzenie);
    if (!rozszerzenie.empty() && rozszerzenie[0] != '.') {
        rozszerzenie = "." + rozszerzenie;
    }
    bool znaleziono = false;
    for (const auto& plik : recursive_directory_iterator(sciezka)){
        if (plik.is_regular_file()) {
            path szukane_rozszerzenie = plik.path();
            string rozszerzenie_pliku = szukane_rozszerzenie.extension().string();
            maleLiterki(rozszerzenie_pliku);
            if (rozszerzenie_pliku == rozszerzenie) {
                cout << "Znaleziono: " << szukane_rozszerzenie.filename() << " | " << szukane_rozszerzenie.extension() << endl;
                cout << "Folder: " << szukane_rozszerzenie.parent_path() << endl;
                znaleziono = true;
            }
        }
    }
    if (znaleziono == false) {
        cout << "Nie znaleziono plikow o rzadanym rozszerzeniu." << endl;
    }

}



void wyswietlajPlikiWiekszeNiz(const string& sciezka) {
    double minimalny_rozmiar;
    cout << "Wyszukaj pliki majace wiecej Mb niz: ";
    cin >> minimalny_rozmiar;
    vector<path> pliki;
    for (const auto& plik : recursive_directory_iterator(sciezka)) {
        path p = plik.path();
        if (is_regular_file(p)) {
            double size = file_size(p)/(1024.0*1024.0);
            if (size >= minimalny_rozmiar) {
                pliki.push_back(p);
            }
        }
    }
    if (pliki.empty()) {
        cout << "Takie pliki nie istnieja." << endl;
        return;
    }
    int wyborSortowania;

    cout << "Jak posortowac pliki?\n";
    cout << "[1] Rosnaco\n";
    cout << "[2] Malejaco\n";
    cin >> wyborSortowania;

    if (wyborSortowania == 1) {
        sort(pliki.begin(),pliki.end(),[](const path& a, const path& b) {
        return file_size(a) < file_size(b);
    });
    }else if (wyborSortowania == 2) {
        sort(pliki.begin(),pliki.end(),[](const path& a, const path& b) {
        return file_size(a) > file_size(b);
    });
    }
    for (const path& p : pliki) {
        cout << "Plik: " << p.filename() << " | " << formatujRozmiar(file_size(p)) << endl;
        cout << "Folder: " << p.parent_path() << endl;
    }
}



void statystykiFolderu(const string& sciezka) {
    cout << "== STATYSTYKI FOLDERU ==\n";
    map<string,int> rozszerzenia;
    int liczba_plikow=0;
    uintmax_t laczny_rozmiar=0;
    int liczba_folderow=0;
    uintmax_t najwiekszy_rozmiar=0;
    string nazwa_najwiekszego_pliku;
    for (const auto& plik : recursive_directory_iterator(sciezka)) {
        path p = plik.path();
        if (plik.is_regular_file()) {
            liczba_plikow++;
            uintmax_t size = file_size(p);
            laczny_rozmiar += size;
            string ext = p.extension().string();
            maleLiterki(ext);
            if (ext.empty()) {
                ext = "bez rozszerzenia";
            }
            rozszerzenia[ext]++;
            if (size > najwiekszy_rozmiar) {
                nazwa_najwiekszego_pliku = p.filename();
                najwiekszy_rozmiar = size;
            }
        } else if (plik.is_directory()) {
            liczba_folderow++;
        }
    }
    cout << "Liczba plikow: " << liczba_plikow << endl;
    cout << "Laczny rozmiar plikow: " << formatujRozmiar(laczny_rozmiar) << endl;
    cout << "Liczba folderow: " << liczba_folderow << endl;
    cout << "Najwiekszy rozmiarowo plik: " << nazwa_najwiekszego_pliku << endl;
    cout << "Rozmiar najwiekszego pliku: " << formatujRozmiar(najwiekszy_rozmiar) << endl;
    cout << "Rozszerzenia: " << endl;
    for (const auto& el : rozszerzenia) {
        cout << el.first << " : " << el.second << endl;
    }
}
