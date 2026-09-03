# C3I A26_Règle_PCB

Compétition de Conception de Circuits Imprimés – Université de Sherbrooke, Automne 2026

## Thème : Règle PCB

Bienvenue à la compétition de conception de PCB de l’Université de Sherbrooke, édition Automne 2026!
Cette compétition a pour but d'agir comme une introduction au monde de la conception de circuit imprimé (PCB). Le thème simple de cette compétition invite les participants à expérimenter, à découvrir et à essayer quelque chose de nouveau. Votre but sera de faire un PCB qui prendra la forme d'une règle tout en ayant un circuit fonctionnel.

---

## Déroulement

Voici l'ensemble des dates importantes de la session, réparties entre les événements et les dates de commandes :

### Calendrier des événements et ateliers

* **9 septembre 2026 (17h00)** : Présentation du projet C3I A26 + Atelier de soudure THT
* **16 septembre 2026 (17h00)** : Atelier de soudure THT + Atelier d'intro à l'électronique
* **23 septembre 2026 (17h00)** : Atelier introduction à KiCad
* **30 septembre 2026 (17h00)** : Atelier Kicad - PCB
* **7 octobre 2026 (17h00)** : Séminaire - Introduction MCU
* **14 octobre 2026 (17h00)** : Séminaires sur les normes de conception électroniques (Schémas + PCB)
* **21 octobre 2026 (17h00)** : Séminaire sur les protocoles de communications
* **28 octobre 2026 (17h00)** : Atelier - Un projet sans devboards
* **4 novembre 2026 (17h00)** : Atelier de soudure (THT + SMD)
* **11 novembre 2026 (17h00)** : Période de travail et d'échange (validation par les pairs)
* **18 novembre 2026 (17h00)** : Séminaire - Intro AmpliOp
* **25 novembre 2026 (17h00)** : Atelier - MicroPython
* **2 décembre 2026 (17h00)** : Séminaire - Assemblage automatique
* **9 décembre 2026 (17h00)** : Période de travail et d'échange (validation par les pairs)
* **16 décembre 2026 (17h00)** : Période de travail et d'échange (validation par les pairs)

### Dates de commande (Pièces et PCB)

* **9 septembre 2026** : Début de la compétition
* **2 octobre 2026** : C3I - Commande de pièces ou PCB
* **16 octobre 2026** : C3I - Commande de pièces ou PCB et fin des inscriptions
* **30 octobre 2026** : C3I - Commande de pièces ou PCB
* **13 novembre 2026** : C3I - Commande de pièces ou PCB (Dernière commande LCSC)
* **27 novembre 2026** : C3I - Commande de pièces ou PCB
* **11 décembre 2026** : C3I - Commande de pièces ou PCB (Dernière commande)
* **30 décembre 2026 (23h59)** : Date limite - Remise projet C3I A26
* **4 janvier 2027 (17h30)** : Événement de compétition C3I A26 (Évaluation, présentation et remise des prix)

---

### Comment forker le dépôt

1. Accédez au dépôt GitHub officiel à l'adresse suivante : `[https://github.com/CCI-udes/A26_Regle_PCB](https://github.com/CCI-udes/A_26_Regle_2-0)`
2. Cliquez sur le bouton "Fork" en haut à droite de la page du dépôt.
3. Sélectionnez votre propre compte GitHub comme destination du fork.
4. Clonez le dépôt forké sur votre machine locale.

---

## Règlement

* Équipes de 1 à 3 personnes. **Si c'est votre première fois à faire un PCB, on vous recommande de vous mettre en équipe de 2**.
* Frais de participation : 1 e-mail à envoyer à un potentiel commanditaire par membre de l'équipe. Voir le lien suivant pour de l'aide: [Repo commandite](https://github.com/CCI-udes/documents_sponsors).
* Dimensions maximales PCB : Longueur de **15,5 cm par 3 cm maximum**.
* Les PCB ayant plus de 2 couches sont acceptés, mais la différence de prix devra être ajoutée au BOM.
* BOM maximum (produit final) : **50 $**.
* Coût de développement maximal autorisé : **100 $**.
* Utilisation de **DevBoard permise** pour le développement (pénalité de -7 points si présente dans la version finale).
* Objectif : **s’amuser et apprendre** !

---

## Remise

Chaque équipe doit fournir via son fork GitHub avant le **30 décembre 2026** :

* Schéma électrique (nettoyé et en PDF).
* Fichiers Gerber du PCB.
* Le code logiciel si applicable.
* BOM (Bill of Materials) conforme (incluant distributeurs et prix réels).
* Documentation complète du projet.

---

## Évaluation

Les projets seront notés sur un total de **250 points**, répartis de la façon suivante :

* **Idée [15 pts]** (Appréciation juges [10 pts] + Appréciation participants [5 pts])


* **Fonctionnalité [35 pts]** (Démonstration fonctionnelle [20 pts] + Compréhension des parties non-fonctionnelles [15 pts])


* **Complexité [45 pts]** (Hardware [25 pts] + Software [20 pts])


* **Gestion des ressources [25 pts]** (Bill Of Materials [20 pts] + Nombre de commandes [5 pts])


* **Démonstration [55 pts]** (Présentation orale [25 pts], Documentation écrite [20 pts], Esthétique/boîtier [10 pts])


* **Conception électronique [75 pts]** (Choix composants [10 pts], Schéma [10 pts], Qualité PCB [20 pts], Conception préventive [10 pts], Assemblage/réparation [10 pts], Qualité des soudures [15 pts])



---

## Prix

* 🏆 **Prix de conception** – Évalué sur **250 pts** (Innovation, ingéniosité, minutie et originalité dans la conception).
* ⚡ **Prix du gningnégnieur** – Évalué sur **170 pts** (Démontre une compréhension des parties non-fonctionnelles, valorise la créativité et l'apprentissage).
* 💼 **Prix du vendeur** – Évalué sur **125 pts** (Savoir organiser ses ressources, minimiser les pertes, attention au détail, esthétique et finition "best-seller").

---

## Ressources utiles

* **Microcontrôleurs recommandés** : ESP32-C3, ESP32-S3, RP2040, PB-03, CH32V003.
* **Logiciels de conception** : KiCad, Altium Designer, EasyEDA.
* **Discord** : [Lien d’invitation](https://discord.gg/xeSqf3N3Hw).

---

## Contacts

* **Jacob Turcotte** – Jacob.Turcotte@usherbrooke.ca (FAC. GÉNIE Robotique)
* **Miriam Caisse** – Miriam.Caisse@usherbrooke.ca (FAC. GÉNIE Électrique)
* **Jordan Gagnon** – Jordan.Gagnon@usherbrooke.ca (FAC. GÉNIE Électrique)
* **Alyson Bourque** - Alyson.Bourque@USherbrooke.ca (FAC. GÉNIE Électrique)
* **Céleste-Lyi Martel** - Celeste-Lyi.Martel@USherbrooke.ca (FAC. GÉNIE Robotique)
