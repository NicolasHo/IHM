#include "jeu.h"

Jeu::Jeu(QObject *parent) : QObject(parent)
{
    m_compteur = 0;
}

int Jeu::compteur()
{
    return m_compteur;
}

void Jeu::setCompteur(int i)
{
    m_compteur = i;
    emit compteurChanged();
}

void Jeu::drawCard()
{

}
void Jeu::pressUNO()
{

}
void Jeu::playCard()
{

}
