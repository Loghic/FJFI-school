
# Flexbox a Grid v CSS


### Co je Flexbox?
    
**Flexbox** je metoda jednorozměrného rozvržení pro uspořádání položek do řádků nebo sloupců, která umožňuje vytvářet responsivní layouty. Položky se ohýbají (roztahují), aby vyplnily další prostor, nebo se zmenšily, aby se vešly do menších prostor. 

---

### Základní vlastnosti Flexboxu

 Pro vytvoření flex kontejneru můžete použít vlastnost `display` v CSS a nastavit její hodnotu na `flex` nebo `inline-flex`.
 
HTML:

    <div class="container">
     <div class="one">...</div>
	 <div class="two">...</div>
    </div>

CSS:

    .container{
	    display: flex | inline-flex;
    }

   ---
   
   Flexbox má několik vlastností, které vám umožní ovládat rozložení položek. Zde jsou některé z nejdůležitějších:

`flex-direction`: Určuje směr, ve kterém jsou položky rozmístěny.

    flex-direction: row | column| row-reverse |
				    column-reverse;

`flex-basis`: Určuje počáteční velikost položky.

    flex-basis: 100px;
    
 `order`: Určuje pořadí, ve kterém se položky zobrazí.


---

`flex-wrap`: Určuje, zda mají být položky zalomeny na více řádků nebo ne.

    flex-wrap: nowrap | wrap | wrap-reverse;

`justify-content`: Určuje zarovnání položek podél hlavní osy.

    justify-content: flex-start | flex-end | center |
				     space-between | space-around |
				     space-evenly;

`align-items`: Určuje zarovnání položek podél větve osy.

    align-items: flex-start | flex-end | center |
				 baseline | stretch;

`align-content`: Určuje zarovnání řádků, pokud je v kontejneru nadbytečné místo.

    align-content: flex-start | flex-end | center |
				   space-between | space-around |
				   space-evenly | stretch;

`align-self`: Umožňuje přepsat zarovnání specifikované vlastností  `align-items`  pro konkrétní položku.


---


`flex-grow`: Určuje množství místa, které by měla položka zabrat v kontejneru.
`flex-shrink`: Určuje množství místa, které by měla položka zmenšit, pokud není dostatek místa v kontejneru.

    flex-basis: 0;
    flex-grow: 1;
    flex-shrink: 1;

`flex`: Zkrácená vlastnost pro  `flex-grow`,  `flex-shrink`  a  `flex-basis`.

    flex: 1 1 0;

Zkracený zápis:

    flex: 1;


### Co je Grid?
    
**Grid** v CSS je systém rozvržení, který nabízí větší flexibilitu a kontrolu než tradiční techniky rozvržení, jako jsou plovoucí, inline-block nebo tabulky. Funguje tak, že rozvržení rozdělí do určitého počtu sloupců a řádků, což umožní umístit položky do těchto buněk a snadno ovládat jejich velikost, polohu a zarovnání.

---

### Základní vlastnosti Gridu

 Pro vytvoření mřížky můžeme použít vlastnost CSS `display` a nastavit její hodnotu na `grid`. Tím se prvek přemění na mřížkový kontejner.
 
HTML:

    <div class="container">
     <div class="one">...</div>
	 <div class="two">...</div>
    </div>

CSS:

    .container {
        display: grid;
    }


---
   
Grid má několik vlastností, které vám umožní ovládat rozložení položek. Zde jsou některé z nejdůležitějších:

`grid-template-columns`: Určuje počet položek ve sloupci.

`grid-template-rows`: Určuje počet položek v řádce.

`gap`: Určuje velikost mezery mezi jednotlivými políčky. Funguje to obdobně jako `padding`.

Lze zapsat zkráceně takto

CSS: 


 grid-template: grid-template-rows / grid-template-columns

CSS:

    .container {
        display: grid;
        grid-template-columns: repeat(3, 1fr);
        grid-template-rows: repeat(2, 1fr);    
    }



V tomto příkladu je funkce `repeat()` použita k vytvoření tří nebo dvou stejně velkých sloupců nebo řádků. Jednotka `1fr` znamená „1 zlomek dostupného prostoru“, což znamená, že každý sloupec nebo řádek zabere stejný podíl dostupného prostoru.


---

`grid-area`: Tato vlastnost umožňuje prvku rozložit více řádků a sloupců v gridu. Má čtyři hodnoty: číslo řádku nebo název pro řádek a sloupec, na kterém začíná oblast mřížky položky mřížky, a číslo řádku nebo název pro řádek a sloupec, na kterém končí oblast mřížky položky mřížky.

    grid-area: 2 / 3 / 4 / 5;

`grid-row`: Tato vlastnost je zkratkou pro grid-row-start a grid-row-end. Definuje velikost a umístění položky gridu v řádku gridu nastavením počáteční a koncové čáry gridu.

    grid-row: 2 / 3;
				    

`grid-column`: Tato vlastnost je zkratkou pro grid-column-start a grid-column-end. Definuje velikost a umístění položky gridu ve sloupci mřížky nastavením počáteční a koncové čáry gridu.

    grid-column: 2 / 3;
				
Lze napsat do `grid-row` a `grid-column` kličové slovo `span`, které nám říká přes kolik políček se má buňka roztáhout.

    grid-row: span 2;
    grid-column: span 4;


