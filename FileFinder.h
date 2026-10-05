#ifndef FILEFINDER_H
#define FILEFINDER_H
#pragma once


#include <string>

void wyswietlPliki(const std::string& sciezka);
void szukajPoNazwie(const std::string& sciezka);
void rozszerzenieWyswietlanie(const std::string& sciezka);
void wyswietlajPlikiWiekszeNiz(const std::string& sciezka);
void statystykiFolderu(const std::string& sciezka);
void maleLiterki(const std::string& tekst);
std::string formatujLiczbe(double liczba, std::string& jednostka);
std::string formatujRozmiar(uintmax_t bajty);

#endif
