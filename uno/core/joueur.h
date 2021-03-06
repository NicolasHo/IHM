#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <vector>
#include <string>
#include "carte.h"
#include "manche.h"
#include "types.h"

/**
 * @brief Permet la gestion des différents cas concernant la nécessité de dire
 *        'uno' quand il ne nous reste plus qu'une carte en main.
 *
 * UNOSTATE_FAUX : 'uno' n'est pas prononcé (ou ne peut pas être prononcé).
 *
 * UNOSTATE_EN_ATTENTE : 'uno' a été prononcé quand le joueur avait le droit :
 *                       le joueur peut annoncer 'uno' quand c'est à son tour
 *                       de jouer, donc avant de poser son avant-dernière carte.
 *
 * UNOSTATE_VRAI : 'uno' a été prononcé a temps, et le joueurs n'as
 *                 plus qu'une carte.
 *
 * UNOSTATE_PENALITE : 'uno' n'as pas été prononcé la pénalité a été
 *                     prise en compte.
 */
enum UnoState { UNOSTATE_FAUX=0, UNOSTATE_EN_ATTENTE, UNOSTATE_VRAI,
                UNOSTATE_PENALITE };

/**
 * @brief La classe Joueur représente un participant d'une partie de Uno.
 */
class Joueur
{
public:
    /**
     * @brief Constructeur de la classe Joueur.
     * @param num le numeros du joueur dans la partie.
     * @param i un pointeur vers les informations de la partie (voir InfoPartie).
     */
    Joueur(u_int num, InfoPartie *i);

    /**
     * @brief Destructeur de la classe Joueur.
     */
    virtual ~Joueur();

    /**
     * @brief Réalise les actions necessaire pour finir la manche courante.
     *
     * Finit la manche courante en comptant les points de sa main et en
     * remettant dans la pioche ses cartes restantes.
     *
     * @return le nombre de nombre de points des cartes restantes.
     */
    int finir_manche();

    /**
     * @brief Prend en compte que le joueur annonce 'uno'.
     *
     * Le 'uno' n'est pris en compte que si c'est à son tour de jouer, et n'est
     * validé que plus tard si il ne lui reste plus qu'une Carte à la fin de son
     * tour.
     */
    void appuie_uno();

    /**
     * @brief Prend en compte qu'un joueur a annoncé un 'contre-uno' contre lui.
     *
     * Le 'contre-uno' ne fait piocher le joueur que s'il ne lui reste qu'une
     * Carte et qu'il n'as pas validé le uno.
     *
     * @return vrai si le joueur subit une penalité, faux sinon.
     */
    bool appuie_contre_uno();

    /**
     * @brief Fait piocher le joueur lorsque c'est son tour de jeu.
     *
     * Le joueur pioche (par défaut ou non) le nombre de Carte indiqué dans la
     * manche courante (comprenant les éventuels malus).
     * Cette fonction appelle piocher(int nb_cartes) pour faire piocher le joueur.
     *
     * @param possibilitee_poser indique si la règle du jeu lui autorise à
     *        poser sa carte s'il n'en pioche qu'une.
     * @return vrai si le joueur peut et a le droit de poser la carte piochée,
     *         faux sinon.
     */
    bool piocher(bool possibilitee_poser=false);

    /**
     * @brief Fait piocher au joueur le nombre de Cartes spécifiées.
     *
     * Cette fonction est appelée quand le joueur pioche quand c'est son tour
     * de jeu, mais également pour distribuer les Cartes en début de Manche,
     * ainsi que pour lui infliger les malus du 'contre-uno'.
     *
     * @param nb_cartes le nombre de Carte que le Joueur doit piocher.
     * @param possibilitee_poser indique si la règle du jeu lui autorise à
     *        poser sa carte s'il n'en pioche qu'une.
     * @return vrai si le joueur peut et a le droit de poser la carte piochée,
     *         faux sinon.
     */
    bool piocher(int nb_cartes, bool possibilitee_poser=false);

    /**
     * @brief Fait joueur ou non la carte piochée.
     *
     * Si il joue la carte, alors elle est posée sur le tas, sinon elle est
     * mise avec ses autres cartes.
     *
     * @param jouer_la_carte indique si le joueur pose la carte piochée.
     */
    void joue_carte_piochee(bool jouer_la_carte);

    /**
     * @brief Trie les Cartes de la main du Joueur.
     *
     * Voir la fonction comparaison_cartes dans la classs Carte pour plus
     * d'information sur le tri des Cartes.
     */
    void trier_main();

    /**
     * @brief Indique à la manche le choix de Couleur du Joueur.
     * @param c la nouvelle couleur choisie par le Joueur.
     */
    void choisir_couleur(Couleur c);

    /**
     * @brief Choisit arbitrairement une nouvelle couleur pour la manche.
     *
     * Si le joueur n'as plus de Carte ou qu'il ne reste que des Carte NOIR,
     * alors la couleur est choisie aléatoirement, sinon la couleur choisie est
     * celle de la première carte de son jeu.
     *
     * @return renvoie la couleur choisie.
     */
    virtual Couleur choisir_couleur_defaut();

    /**
     * @brief Cherche toutes les Carte du Joueur qu'il peux poser.
     * @return la liste des indices des Cartes jouables.
     */
    std::vector<int> recherche_cartes_jouables();

    /**
     * @brief Joue (si possible) la carte indiquée.
     *
     * La Carte que souhaite poser le joueur n'est jouée que si elle est jouable.
     *
     * @param indice_carte l'indice de la carte à jouer.
     * @return vrai si la Carte a été jouée, faux sinon.
     */
    bool jouer(int indice_carte);

    /**
     * @brief L'action du joueur se fait arbitrairement.
     *
     * Si une carte est jouable, il joue la première jouable, sinon il pioche.
     */
    virtual void action_par_defaut();

    /**
     * @brief Affiche les Cartes du Joueur sur la sortie standard.
     */
    void afficher_main();

public:
    /// Manche en cours pendant une partie.
    Manche* manche_courante;

    /// Les cartes qu'à en main le joueur.
    std::vector<Carte*> cmain;

    /// La carte piochée si il peut et à le droit de la poser.
    Carte *carte_piochee;

    /// Voir enum UnoState pour plus de précisions.
    UnoState uno;

    /// Nombre de points du joueur dans la partie.
    u_int points;

    /// Numero du joueur dans la partie.
    u_int num_joueur;

    /// Informations de la partie (voir struct InfoPartie).
    InfoPartie *infos;
};


#endif // JOUEUR_H
