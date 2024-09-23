---

marp: true
paginate: false
theme: academic
footer: 'Matěj Michálek ![w:65](logo-nobg.png)' 

---

# Unixové shelly

## Matěj Michálek
### Fakulta jaderná a fyzikálně inženýrská

#### 18OS - operační systémy



<style scoped>
    h1 {
      display: block;
      margin-top: 25vh;
      
    }
    h2 {
      font-size: xxx-large;
    }
    h3 {
      font-size: x-large;
    }
    h4{
      font-size: large;
    }
  </style>

---

## Shell

<style scoped>
  ul {
  font-size: 1em;
  }
  </style>


- Rozhraní mezi uživatelem a operačním systémem
- Zpracovává příkazy zadané uživatelem
- Poskytuje různé funkce
- Typický interakce s uživatel pomocí terminálového emilátoru
- Pro server typicky na přímo
- rozebere, vyhodnotí, vyhledá a spustí daný program (pokud byl nalezen)


---

## Typy Shellů

- Bourne Shell (sh)
- C Shell (csh)
- Tenex C Shell (tcsh)
- KornShell (ksh)
- Bourne Again Shell (bash)
- Z Shell (zsh)

---

## Bourne Shell (sh)


- Nejzákladnější shell v Unixových systémech
- Cesta `/bin/sh`
- Uživatel `$` a superuživatel `#`
```
# ls -al
# su root
$ ls -al
```

--- 

## Bourne Shell (sh)

Nevýhody: 

- Omezená syntaxe
- Omezená podpora pro dynamické datové typy
- Neobsahuje historii příkazů
- Neobsahuje automatické doplňování 

---

## C Shell (csh)

- Napodobuje jazyk C
- Cesta `/bin/csh`
- Uživatel `%`, superuživatel `#`

```
% ls -al
% su root
# ls -al
```
--- 
## C Shell (csh)

Výhody: 
- Historie příkazů 
- Uživatelsky definované proměnné
- Realtivní domovský adresář (~)
- Vestavěné operace pro manipulaci se soubory a adresáři
- Podmínky a cykly

---

## C Shell (csh)

Nevýhody

- Omezená syntaxe
- Nízká rozšiřitelnost
- Problémy s kompatibilitou
- Není plně rekurzivní

---

## Tenex C Shell (tcsh)

- Cesta `/bin/tcsh`
- Uživatel `hostname:directory>` superuživatel `hostname:directory#`
- Rané verze MacOS a FreeBSD

```
user1:Documents> ls -al
user1:Documents> su root
User1:Documents# ls - -al
```
---

## Tenex C Shell (tcsh)

Výhody:

- Rozšíření historie příkazů
- Automatické doplňování 
- Podpora pro aliasy
- Rozšířená syntaxe
- Kompatibilita s původním C Shellem
- Vestavěný `where` příkaz

---

## KornShell (ksh)

- Cesta `/bin/ksh` nebo `/bin/ksh93`
- Uživatel `$` superuživatel `#` (stejný jako v Bourne Shellu)

```
# ls -al
# su root
$ ls -al
```
---

## KornShell (ksh)

Výhody:
- Rozšiřitelnost vestavěných příkazů
- Kompatibilní s Bourne shellem
- Inteligentní automatické doplňování
- Zabudovaní matematické funkce a desetinná aritmetika


---

## KornShell (ksh)
Příklad matematických funkcí a desetinné aritmetiky:

```
# Příklad sečtení desitinných čísel
result=$(echo "1.5 + 2.7" | bc) # bc je "basic calculator"
echo $result

# Příklad odmocnina čísla
result=$(echo "sqrt(25)" | bc)
echo $result
```

---

## Bourne Again Shell (bash)

- Cesta `/bin/bash`
- Uživatel `$` a superuživatel `#`

```
user1@user1:~$ ls -al
user1@user1:~$ su root
user1@user1:~# ls -al
```

--- 

## Bourne Again Shell (bash)

Výhody:
- Rozšířená syntaxe
- Automatické doplňování
- Historie příkazů
- Podpora pro rozšíření
- Kompatibilita s původním Bourne Shellem

---

## Bourne Again Shell (bash)

Příklad jednoduché skriptu: 

```
#!/bin/bash

echo "Enter the first number:"
read num1

echo "Enter the second number:"
read num2

sum=$((num1 + num2))

echo "The sum of $num1 and $num2 is: $sum"
```
---

## Z Shell (zsh)

- Cesta `/bin/zsh`
- Uživatel `user@hostname location %` superuživatel `hostname#`
- Výchozí shell pro MacOS a Kali Linux

```
user1@user1 ~ % ls -al
user1@user1 ~ % sudo -s
root@user1 ~ # ls -al
```

Shell je vysoce konfigurovatelný a upravitelný skrz framework Oh My Zsh

---

## Z Shell (zsh)

Výhody

- Kompatibilita s BASH
- Rozšiřitelný pomocí pluginů
- Rozšířené automatické doplňování 
- Rozšířené historické funkce

--- 

## References:

<style scoped>
  h2 {
    text-align: left;
    font-size: xx-large;
  }
  text{
    font-size: small;
  }
  </style>

  https://phoenixnap.com/kb/linux-shells
  https://en.wikipedia.org/wiki/Unix_shell
  https://www.digitalocean.com/community/tutorials/different-types-of-shells-in-linux
  https://www.freecodecamp.org/news/linux-shells-explained/
