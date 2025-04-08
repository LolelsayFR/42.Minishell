![minishell](https://github.com/user-attachments/assets/d4a311b8-98b2-498d-bc85-105916ebb865)

# Minishell

## Description 🇫🇷

Minishell est une implémentation simple d'un shell Unix, conçu pour reproduire le comportement de base de Bash. Ce projet a été réalisé dans le cadre d'un exercice éducatif pour apprendre à manipuler les processus, les signaux et les entrées/sorties en C.

---

## Fonctionnalités

- Exécution de commandes simples (avec ou sans arguments)
- Redirections et heredocs (`>`, `>>`, `<`, `<<`)
- Pipes (`|`) pour connecter plusieurs commandes
- Gestion des variables d'environnement
- Gestion des signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+Z`)
- Implémentation de commandes intégrées comme `cd`, `echo`, `env`, `exit`, etc.

---

## Prérequis

Pour compiler et exécuter Minishell, vous aurez besoin de :

- Un compilateur C (comme `gcc` ou `clang`)
- **La bibliothèque [readline](https://tiswww.case.edu/php/chet/readline/rltop.html)** (souvent disponible via le gestionnaire de paquets de votre système, par exemple `libreadline-dev` sur Debian/Ubuntu)
- Une machine Unix/Linux ou un environnement compatible (comme WSL sur Windows)

---

## Installation

1. Clonez le dépôt :

   ```bash
   git clone https://github.com/LolelsayFR/minishell.git
   cd minishell
   ```

2. Compilez le projet :

   ```bash
   make
   ```

3. Lancez le shell :

   ```bash
   ./minishell
   ```

---

## Utilisation

Lancez `./minishell` pour entrer dans le shell. Voici quelques exemples de commandes :

- Commande simple :
  ```bash
  ls -l
  ```

- Redirection de sortie :
  ```bash
  echo "Hello, world!" > fichier.txt
  ```

- Utilisation de pipes :
  ```bash
  cat fichier.txt | grep Hello
  ```

- Commandes intégrées :
  ```bash
  cd ..
  echo "Bienvenue dans Minishell"
  exit
  ```

---

## Commandes Intégrées

- `echo` : Affiche du texte.
- `cd` : Change de répertoire.
- `pwd` : Affiche le répertoire courant.
- `export` : Définit des variables d'environnement.
- `unset` : Supprime des variables d'environnement.
- `env` : Affiche les variables d'environnement.
- `exit` : Quitte le shell.

---

## Auteurs

Ce projet a été réalisé par :

- **LolelsayFR | Emaillet**
- **UnGarsRandom | Artgirar**

## Description 🇬🇧

Minishell is a simple implementation of a Unix shell, designed to replicate the basic behavior of Bash. This project was created as an educational exercise to learn how to handle processes, signals, and input/output in C.

---

## Features 

- Execution of simple commands (with or without arguments)
- Redirections and heredocs (`>`, `>>`, `<`, `<<`)
- Pipes (`|`) to connect multiple commands
- Environment variables management
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+Z`)
- Built-in commands such as `cd`, `echo`, `env`, `exit`, etc.

---

## Prerequisites

To compile and run Minishell, you will need:

- A C compiler (such as `gcc` or `clang`)
- **The [readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)** (commonly available via your system's package manager, e.g., `libreadline-dev` on Debian/Ubuntu)
- A Unix/Linux machine or a compatible environment (such as WSL on Windows)

---

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/LolelsayFR/minishell.git
   cd minishell
   ```

2. Compile the project:

   ```bash
   make
   ```

3. Run the shell:

   ```bash
   ./minishell
   ```

---

## Usage

Run `./minishell` to enter the shell. Here are a few command examples:

- Simple command:
  ```bash
  ls -l
  ```

- Output redirection:
  ```bash
  echo "Hello, world!" > file.txt
  ```

- Using pipes:
  ```bash
  cat file.txt | grep Hello
  ```

- Built-in commands:
  ```bash
  cd ..
  echo "Welcome to Minishell"
  exit
  ```

---

## Built-in Commands

- `echo`: Prints text.
- `cd`: Changes the current directory.
- `pwd`: Displays the current directory.
- `export`: Sets environment variables.
- `unset`: Removes environment variables.
- `env`: Displays environment variables.
- `exit`: Exits the shell.

---

## Authors

This project was created by:

- **LolelsayFR | Emaillet**
- **UnGarsRandom | Artgirar**
