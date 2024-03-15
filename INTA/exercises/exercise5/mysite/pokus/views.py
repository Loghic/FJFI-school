from django.shortcuts import render
from django.http import HttpResponse
import datetime

# Zdroj: https://www.itnetwork.cz/javascript/zaklady/javascript-tutorial-zaciname-s-javascriptem-podminky-cykly-pole-svatky
svatky = {
    #january
    1: ["Nový rok, Den obnovy samostatného českého státu", "Karina", "Radmila", "Diana", "Dalimil", "Tři králové", "Vilma", "Čestmír", "Vladan", "Břetislav", "Bohdana", "Pravoslav", "Edita", "Radovan", "Alice", "Ctirad", "Drahoslav", "Vladislav", "Doubravka", "Ilona", "Běla", "Slavomír", "Zdeněk", "Milena", "Miloš", "Zora", "Ingrid", "Otýlie", "Zdislava", "Robin", "Marika"],
    #february
    2: ["Hynek", "Nela", "Blažej", "Jarmila", "Dobromila", "Vanda", "Veronika", "Milada", "Apolena", "Mojmír", "Božena", "Slavěna", "Věnceslav", "Valentýn", "Jiřina", "Ljuba", "Miloslava", "Gizela", "Patrik", "Oldřich", "Lenka", "Petr", "Svatopluk", "Matěj", "Liliana", "Dorota", "Alexandr", "Lumír", "Horymír",],
    #march
    3: ["Bedřich", "Anežka", "Kamil", "Stela", "Kazimír", "Miroslav", "Tomáš", "Gabriela", "Františka", "Viktorie", "Anděla", "Řehoř", "Růžena", "Rút, Matylda", "Ida", "Elena, Herbert", "Vlastimil", "Eduard", "Josef", "Světlana", "Radek", "Leona", "Ivona", "Gabriel", "Marián", "Emanuel", "Dita", "Soňa", "Taťána", "Arnošt", "Kvido"],
    #april
    4: ["Hugo", "Erika", "Richard", "Ivana", "Miroslava", "Vendula", "Heřman, Hermína", "Ema", "Dušan", "Darja", "Izabela", "Julius", "Aleš", "Vincenc", "Anastázie", "Irena", "Rudolf", "Valérie", "Rostislav", "Marcela", "Alexandra", "Evženie", "Vojtěch", "Jiří", "Marek", "Oto", "Jaroslav", "Vlastislav", "Robert", "Blahoslav"],
    #may
    5: ["Svátek práce", "Zikmund", "Alexej", "Květoslav", "Klaudie", "Radoslav", "Stanislav", "Den vítězství", "Ctibor", "Blažena", "Svatava", "Pankrác", "Servác", "Bonifác", "Žofie", "Přemysl", "Aneta", "Nataša", "Ivo", "Zbyšek", "Monika", "Emil", "Vladimír", "Jana", "Viola", "Filip", "Valdemar", "Vilém", "Maxmilián", "Ferdinand", "Kamila"],
    #june   
    6: ["Laura", "Jarmil", "Tamara", "Dalibor", "Dobroslav", "Norbert", "Iveta, Slavoj", "Medard", "Stanislava", "Gita", "Bruno", "Antonie", "Antonín", "Roland", "Vít", "Zbyněk", "Adolf", "Milan", "Leoš", "Květa", "Alois", "Pavla", "Zdeňka", "Jan", "Ivan", "Adriana", "Ladislav", "Lubomír", "Petr a Pavel", "Šárka"],
    #july
    7: ["Jaroslava", "Patricie", "Radomír", "Prokop", "Cyril, Metoděj", "Den upálení mistra Jana Husa", "Bohuslava", "Nora", "Drahoslava", "Libuše, Amálie", "Olga", "Bořek", "Markéta", "Karolína", "Jindřich", "Luboš", "Martina", "Drahomíra", "Čeněk", "Ilja", "Vítězslav", "Magdaléna", "Libor", "Kristýna", "Jakub", "Anna", "Věroslav", "Viktor", "Marta", "Bořivoj", "Ignác"],
    #august
    8: ["Oskar", "Gustav", "Miluše", "Dominik", "Kristián", "Oldřiška", "Lada", "Soběslav", "Roman", "Vavřinec", "Zuzana", "Klára", "Alena", "Alan", "Hana", "Jáchym", "Petra", "Helena", "Ludvík", "Bernard", "Johana", "Bohuslav", "Sandra", "Bartoloměj", "Radim", "Luděk", "Otakar", "Augustýn", "Evelína", "Vladěna", "Pavlína"],
    #september
    9: ["Linda, Samuel", "Adéla", "Bronislav", "Jindřiška", "Boris", "Boleslav", "Regína", "Mariana", "Daniela", "Irma", "Denisa", "Marie", "Lubor", "Radka", "Jolana", "Ludmila", "Naděžda", "Kryštof", "Zita", "Oleg", "Matouš", "Darina", "Berta", "Jaromír", "Zlata", "Andrea", "Jonáš", "Václav, Den české státnosti", "Michal", "Jeroným"],
    #october
    10: ["Igor", "Olivie, Oliver", "Bohumil", "František", "Eliška", "Hanuš", "Justýna", "Věra", "Štefan, Sára", "Marina", "Andrej", "Marcel", "Renáta", "Agáta", "Tereza", "Havel", "Hedvika", "Lukáš", "Michaela", "Vendelín", "Brigita", "Sabina", "Teodor", "Nina", "Beáta", "Erik", "Šarlota, Zoe", "Den vzniku samostatného československého státu", "Silvie", "Tadeáš", "Štěpánka"],
    #november
    11: ["Felix", "Památka zesnulých (dušičky)", "Hubert", "Karel", "Miriam", "Liběna", "Saskie", "Bohumír", "Bohdan", "Evžen", "Martin", "Benedikt", "Tibor", "Sáva", "Leopold", "Otmar", "Mahulena, Den boje za svobodu a demokracii", "Romana", "Alžběta", "Nikola", "Albert", "Cecílie", "Klement", "Emílie", "Kateřina", "Artur", "Xenie", "René", "Zina", "Ondřej"],
    #december
    12: ["Iva", "Blanka", "Svatoslav", "Barbora", "Jitka", "Mikuláš", "Benjamín", "Květoslava", "Vratislav", "Julie", "Dana", "Simona", "Lucie", "Lýdie", "Radana", "Albína", "Daniel", "Miloslav", "Ester", "Dagmar", "Natálie", "Šimon", "Vlasta", "Adam, Eva, Štědrý den", "1. svátek vánoční", "Štěpán, 2. svátek vánoční", "Žaneta", "Bohumila", "Judita", "David", "Silvestr"],
}

def index(request):
    now = datetime.datetime.now()
    document = f"<p>Datum a čas: {now}</p>"
    name = svatky[now.month][now.day - 1]
    document += f"<p>Svátek má {name}.</p>"
    return HttpResponse(document)
# Create your views here.

from django.shortcuts import render

def some_page(request):
    context = {
        "some_parameters": {"key": "value"},
    }
    return render(request, "pokus/some_page.html", context)

def info(request):
    r = HttpResponse()
    r.write(f"<p>Request scheme: {request.scheme}</p>")
    r.write(f"<p>Request method: {request.method}</p>")
    r.write(f"<p>Request encoding: {request.encoding}</p>")
    r.write(f"<p>Request body: {request.body}</p>")
    r.write(f"<p>Request path: {request.path}</p>")
    r.write(f"<p>Request headers: {len(request.headers)}</p>")
    r.write("<ul>")
    for key, value in request.headers.items():
        r.write(f"<li>{key}: {value}</li>")
    r.write("</ul>")
    if request.method == "GET":
        r.write(f"<p>GET parameters: {len(request.GET)}</p>")
        r.write("<ul>")
        for key, value in request.GET.items():
            r.write(f"<li>{key}: {value}</li>")
        r.write("</ul>")
    if request.method == "POST":
        r.write(f"<p>POST parameters: {len(request.POST)}</p>")
        r.write("<ul>")
        for key, value in request.POST.items():
            r.write(f"<li>{key}: {value}</li>")
        r.write("</ul>")

    #r.status_code = 404
    #r.headers["MyHeader"] = "test"

    return r