# Systemprogrammierung unter Linux

openSuse in der VM, keine spezielle Software

## 1. Basic
### 1.1 Aufbau
  * Kernel
    * Programm, Software laeuft die ganze Zeit
    * Faehig, dass die Programme (aktiv) wechseln/starten kann
      * Schedular, Interrupts, Prozessumgebung und Geraetetreiber, Speicherverwaltung
      * In einem Bus asynchrone Events (zum Beispiel Maus)
  * initial ramdisk
    * moeglichst klein, damit es in RAM passt
    * Dateien die sagen, wo der Kernel liegt, damit dieser starten kann
      * init process
        * weitere Software der Eingabegeraete
        * weitere Treiber fuer Hardware
  * root-Filesystem
    * fuer weitere Programme. z.B. Intellij IDEA


Der GNU-C-Compiler kann fuer beinahe jede CPU Maschinencode erzeugen. 

Verzeichnis: /boot  Software vom Bootloader
vmLinuz: Kernel (default: Standardisiert damit alles erkannt wird)
initrd: initial ramdisk
dmesg -k -f kernel -l info oder journalctl -k: Meldungen des kernels anzeigen

### 1.2 Das Dateisystem
  * bestimmt Struktur, Aufbau fuer Verzeichnisbaum
  * bei Unix eine Baumstruktur ohne Laufwerksbuchstaben

Verzeichnisname | Funktion
--------------- | --------
/ | Rootverzeichnis. Hier beginnt die Baumstruktur
/etc | Konfigurationsdateien
/opt | Optionale Zusatzsoftware von Drittanbietern
/media | Wechseldatentraeger
/mnt | Einhaengepunkt fuer weitere Dateisysteme, wird heute nicht mehr benutzt. Nur noch da fuer alte Systeme
/dev | Geraete die Kernel findet und kennt. Legt die dann an
/bin | Binaries: Ausfuehrbare Programme
/sbin | Systemkritische Programme
/var | Variables
/lib | Bibliotheksdateien
/proc | Processdateisystem (virtuell), alle aktuellen Prozesse als Ordnerstruktur, fuer Schedular
/usr | Unix System Resources. Abhaengig von Distributor, Zusatzsachen.. z.B. Java, xServer, ..
/home | Benutzerverzeichnisse
/root | Benutzerverzeichnisse vom Administrator
/run | Fluechtige Dateien, notwendig vom System. Sollten besser nicht von selbst geloescht werden
/tmp | temporaere Dateien, notwendig vom System. Koennen geloescht werden wenn man will. Ansonsten identisch zu /run
/sys | Kernelmodule

df -h : Anschauen vom Filesystem
Standarddateisystem ist ext4, btrfs -> Kernel braucht Treiber um das System zu benutzen
FAT32, exFAT benutzen um zwischen BS's zu interagieren

### 1.3 Shellverwendung
  * Konsole (Terminal tty)
  * Ein Geraet, mit dem man mit dem Kernel kommuniziert
  * Login-Prozess
  * Grafische Oberflaeche meist auf Konsole 7
  * Wechsel: Strg+Alt+Nummer oder sudo chvt [nummer]

## Shells
Shellname | Genauer Name
--------- | ------------
(b) sh | Bourne Shell
bash | Bourne Again Shell
csh | C-Shell
ksh | Korn-Shell
ash | Almquist Shell
dash | Debian Almquist Shell

Die Shell kann in /etc/passwd geaendert werden. Oder ueber den Terminalbefehl chsh 

Wichtige Befehle:
  * cd, pwd, vi, less, more, rmdir, mkdir, rm, mv, bg (Standardausgabe bleibt im Terminal), fg, ps, job, passwd (passwort ist in /etc/shadow als Hash gespeichert), chown
  * Bei Hilfe: man und help

### 1.3.1 Unix Standards
  * Portable Operating System Interface (POSIX)
    * Anforderungen an Standards
  * X/open-Gruppe (open-Group) mit x/Open-portablity-Guide (XPG)
  * Compiler-Standards: ANSI bzw. ISO
    * Viele Header-Dateien und Bibliotheken sind genormt, darin enthaltene Funktionen und Dateitypen koennen auf viele Systeme genutzt werden. Zwei Implementierungen sind: SystemV und BSD.
    Linux als "Open Source Linux" ist durchgaegngi beeinflusst durch oben genannten Standards und deren Implementierungen

## 3. Die Programmiersprache C
In 70ern von Dennis Ritchie entwickelt.

Jahr | Beschreibung
---- | ------------
1978 | Kernigham & Ritchie C
1988 | ANSI C (C89)
1990 | ISO-C (C-90)
1999 | (C-99)
2011 | (C11)

### 3.1 Der GNU C-Compiler (gcc)
  
Name | Alias
---- | -----
c-compiler | cc (alias fuer gcc)
c++-compiler | c++ (alias fuer g++)
Praeprozessor | cpp
Assembler | as
Linker | ld

#### gcc erkennt verschiedene Dateitypen: 

Dateiendung | Beschreibung
----------- | ------------
.c | C-Quellcode
.h | C-Headerdatei
.C | C++-Quellcodedatei
.cc | C++-Quellcodedatei
.cxx | C++-Quellcodedatei
.m | Objective-C-Quellprogramm
.s, .S | Assemblerdatei
.i | Praeprozessierte c-Quelltextdatei
.ii | Praeprozessierte c++-Quelltextdatei
.o | Objektdatei
.a | Bibliotheksdatei

#### Einige Schalter fuer gcc

Schalter | Beschreibung
-------- | ------------
-o name | Outputdateiname
-g gdb | fuegt Debuginformationen hinzu
-c | nur kompilieren
-E | Angegebene Quellcodes werden nur Praeprozessiert
-s | Es werden nur Assembler erzeugt
-Wall | zeigt alle Warnungen an, die vom Compiler unterstuetzt werden
-v | zeigt alle Schritte ausfuehrlich an
-l name | bindet Bibliotheke lib name.so ein
-D name | fuegt Name als Macro fuer Praeprozessor an
-m machtype | Prozessorarchitektur machtype

### 3.2 Welche Header gibts (Wiederholung)
#### Standardbibliotheke 
Sind unter Windows, Linux verfuegbar

  * time.h
  * stdio.h
  * stdlib.h
  * limits.h
  * math.h
  * float.h 
  * string.h 
  * ctype.h (Funktionen die Character convertieren zwischen Zahlen und Strings)
  * assert.h (prueft einen Ausdruck, muss einen bestimmten Wert haben, damit kann man auch debuggen)
  * stdint.h (definiert zum beispiel int8, int16, ..)
  * stddef.h

  Linuxspezifisch, braucht man fuer die Systemprogrammierung unter Linux

  * unistd.h (Unix standard Bibliotheke)
  * sys/types.h 
  * fcntl.h

### Wiederholung C-Syntax (siehe Programme)

  Fuer Arrays in C typisch: Null-terminiert.
  Headerdateien: /usr/include
  Headerdateien: /usr/include/sys

  Zum standardisieren: Make

### 2.2 Verwendung von Makefiles
  * Aehnlich wie ein Shellprogramm, man braucht die Kommandozeile zum kompilieren einer C-Datei. 
  * Da solche Projekte groesser werden koennen, sollen sich nur die frisch geaenderten Dateien neu kompiliert. Welche Dateien muessen neu uebersetzt werden
  * Name: Makefile oder makefile, wird automatisch von make als Steuerdatei ausgewaehlt, hat man keine zur Hand, greift make auf eingebaute Regeln zurueck.
  
#### Make Befehle
Parameter | Beschreibung
--------- | ------------
-p | print, zeigt Makroumgebungen an
-s | silcent, zeigt Kommando nicht explizit an
-n | no execute, zeige nur das Kommando an, fuehre es nicht aus
-q | question, Abfrage ueber aktuellen Zustand der Ziele. Ist der Return wert positiv, muss nichts geaendert werden, wenn negativ, muss was gemacht werden. (exit status)

make main (gibt eine Datei namens main.c), sucht in der Regel fuer %.c wie er diese handhaben soll
ergibt dann (mit Standardregeln):
  $(CC) $(CFLAGS) $OUT-PUT-OPTION) 
  und daraus wird
  cc -o main main.c

Makefile schreibt man in der Regel gross, damit diese Datei im REPO auch immer oben steht, aehnlich README.md
if [ "$?" -wq 0  ]; then echo "OK"; else echo "NO"; fi
Prueft ab, ob alle uebersetzt?
Da sizeof(pointer) 8 Byte gross ist => Wir befinden uns auf einem 64 Bit System.

#### Der GNU-Debugger (gdb)
In Java aehnlich, gibt JDB

Befehl | Beschreibung
------ | ------------
help | Hilfe zu den Kommandos und Parametern 
help breakpoints | anhalten + fortsetzen, an irgendeine Variable eine Bedingung setzen
help data | Moeglichkeit, Speicher den das Programm belegt rauszuschreiben/reinzuladen. Gut fuer Segmentationfault
help files | Damit kann man mit Dateien arbeiten, laedt Prog. Datei
running | Wesentliche Befehle um mit dem Debugger arbeiten zu koennen. Da drin muss steht, wie das Programm laufen muss (z.B. Eingaben), next & step sind so die typischen Befehle
Start | Startet einen Debuglauf, setzt dabei einen temp. Breakpoint
file <executable> |  laedt Prog. Datei
list | listet Quelltext auf, falls Debugsymmbole vorhanden sind
next/step | Damit kann man ein Programm Schrittweise ablaufen lassen. Vereinheitlicht
nexti/stepi | Damit kann man ein Programm Schrittweise ablaufen lassen. Instruktionsweise. Dauert bisschen laenger 
run | Ausfuehren bis zum Naechsten Breakpoint/Absturz/Ende 
continue | Wenn ein Breakpoint erreicht wurde, wieder in den "run"-Modus wechseln
print | Ausgeben von Ausdrueck. z.B. Wertebelegung von Variablen. 
display | Ausgeben von Ausdruck nach jedem Debugschritt. Bemerkung: Der letzte Befehl wird durch <return>-Taste wiederholt.
x/FMT (Format) | Gibt an, wie der Speicher zu formatieren ist. Man muss eine Adresse spezifizieren. Zum Beispiel 20 Bytes ausgeben, man muss sagen wie diese dann zu interpretieren sind. (int, double, ...). Beispiel: /20dw{Adress} (zum Beispiel array, dann schaut er sich das ganze Array mit 20 Integers an)

##### Allgemeine Bemerkung: 
  * Alle Environmentvariablen werden auch mit uebergeben. Kann man auslesen mit x/20s ... Dort stehen sachen drin wie: Was ist die Shell?
  * Man kann die Variablen auch veraendern mit "set values[0] = 100"
  * Unter Microsoft ist auch 0xccccc ein NULL-Pointer. (Linux 0x0)
  * Segmentationfault: unter coredumpctl findet man die Abstuerze. Mit sudo coredumpctl gdb kann direkt gdb gegeben werden. Speicherabbild coredump.
  * ulimit -a zeigt die Limits. Kann die groesse vom Speicherabbild aendern (ulimit -c unlimited)


### 3. Fehlerbehandlung

  Dadurch bleibt die Fehlerbehandlung Systemunabhaengig:

  * #include <stdio.h>
    * void perror(const char \*s)

  * #include <errno.h>
    * int errno;

  * #include <string.h>
    * char * strerror(int errnum);

  * #include <error.h>
    * void error(int status, int errnum, const char * format, ...); 
      * Bricht mein Programm ab
    * void error_at_line(int status, int errnum, const char * filename, unsigned int linenum, const char * format)
    * extern unsigned int error_message_count;
    * extern int error_one_per_line;
    * extern void (\* error_prog_name) (void);
    * Makros:
      * \_\_LINE__
      * \_\_FILE__

### 4. Kommandozeilenparameter

  * zum Beispiel: ls -alt, ausgeschrieben: ls --all --list ...
  * Haeufige Paramter: 

  Parameter | Bedeutung
  --------- | ---------
  -v | verbose, sei gespraechig
  -h, -? | help, gibt Aufschluss, wie die wichtigsten Parameter gesetzt werden koennen
  -r, -R | rekursive Verarbeitung. Zum Beispiel: Dateisystem

  Bibliotheke fuer solche Parameter:
  * \#include <unistd.h>
  * \#include <getopt.h>

#### Funktionen:
  * ```int getopt(int argc, char * const argv[], const char *optstr)``` 
    * optstr gibt an, welche Optionen erlaubt sind oder nicht
    * keine Gedanken uebers Parsen machen
  * ```extern char * optarg;``` 
    * in diesem pointer legt er schalter eines Argumentes ab
  * ```extern int optind``` 
    * aktuelle Index von array an der Stelle wo er gerade parsed, wird standardmaessig auf 1 gesetzt, 0 ist schliesslich der Name des Programmes
  * ```extern int opterr``` 
    * 0 = Fehlersuche abschalten, 1 = an (Standard)
  * ```extern int optopt``` 
    * Wenn ein Schalter vorhanden ist mit einem Argument welches nicht erlaubt ist, getopt fuellt diese. Wird ein character zurueckgegeben

  Zeichen, die auf ein Minus ('-') folgen, werden als Option gewertet. Durch wiederholtes Aufrufen von getopt() wird eine Option nach der anderen zurueckgeliefert.
  Sind keine weiteren Optionen auffindbar, liefert getopt() den Wert -1. Zu Suchende Optionen: optstring.
  Folgt auf eine Option ein Doppelpunkt (':'), so erhaelt diese Option ein zusaetzliches Argument. Bei einem Doppelpunkt MUSS ein Wert danach folgen.
  wenn ich 'x:' definiere, kann das Programm mit '-x 127' aufgerufen werden. 127 wird in optarg gespeichert.
  Doch Vorsicht: wenn -x -y, dann wird das ('-') so in optarg geschrieben. 
  Sollte das Argument Optional sein, folgt ein weiterer Doppelpunkt ('::'). Beispiel: '\x\::' -> -x; -x 123. GEFAHR: bei einem -x -y wird das -y wieder als argument fuer -x gespeichert..

##### Es gibt zwei Fehlerarten, die auftreten koennen:
  * Unbekannter Parameter
  * Es fehlt das Argument einer gesetzten Option

  Dabei liefert ```getopt()``` ein '?' und speichert die unbekannte Option in optopt. Besitzt optstr zu Beginn einen Doppelpunkt ':', Bsp: ":x:", so liefert ```getopt()``` einen Doppelpunkt ':' zurueck, falls
  kein gefordertes Argument geliefert wurde. Dabei wird opterr = 0, schalten es also aus. 

```
  int getopt_long(int argc, char * const argv[], const char * optstr, const struct option, * longopts, int * longindex);
```
```
  struct option {
    const char *name; // Bezeichnung der longoption
    int has_arg; // 0, 1, 2 or no_argument (0), required_argument(1), optional_argument(2)
    int * flag; //bestimmt die Art der Rueckgabe, einfachsten Fall: 0, dann identisch zu getopt
    int val; //Rueckgabewert, wenn gefunden wurde. 
  };
```

Optionen in langform ist '--' vorrangestellt. Optionen in Langform duerfen abgekuerzt vorkommen, solange sie eindeutig sind.
Argumente folgen nach Gleichheits- oder Leerzeichen. Ist bei einer Option das Flag gesetzt, so wird val an die Addresse in flag geschrieben und 0 zurueckgegeben. 
Anderenfalls liefert ```getopt_long``` den Wert val zurueck.  

### 5. Elementare E/A-Funktionen

* ungepufferte E/A Routinen
  * \#include <unistd.h>
  * \#include <fcntl.h>

#### 5.1 Filedeskriptoren
  * Zugriffsnummer, unter der der Kernel die Zugriffe auf die Datei verwaltet.
  * Diese Zugriffsnummern nennt man Dateideskriptoren
  * Bei jedem Start eines Prozesses werden schon drei Deskriptoren bereitgestellt:
    * stdin   -> 0
    * stdout  -> 1
    * stderr  -> 2
      * Kennt man auch von 2> in der Bash
      * In Linux 

  POSIX-Konstanten:
  * STDIN_FILENO
  * STDOUT_FILENO
  * STDERR_FILENO
    * Man sollte lieber diese Konstanten benutzen als irgendwelche Nummern. Diese sind in der Header-Datei <unistd.h> definiert.

  * Mit Hilfe von ```lsof -c bash``` zeigt er uns alle geoeffneten Filedeskriptoren der Bash an

#### 5.2 Lesen und Schreiben von Dateien
##### Oeffnen einer Datei

  * \#include <sys/stat.h>
  * \#include <sys/types.h>
  * \#include <fcntl.h>

  ```
  int open (const char * pathname, // nicht Unix-Windows-Kompatibel
               int flags,
               ... // mode_t mode)
  ```
  * gibts auch ueberladen 
  * Flags:
    * O_RDONLY  (=0)
    * O_WRONLY  (=1)
    * O_RDWR    (=2)
    * O_CREAT -> mode Parameter
    * O_APPEND
    * O_EXCL -> Oeffnet datei nur, wenn diese noch nicht existiert. Verhindert Oeffnen falls Datei existiert. z.B. PID-File. Kann dann pruefen, ob ein Prozess bereits laeuft. 
    * O_TRUNC -> Abschneiden
    * O_NONBLOCK -> asynchr. Schreiben bei Geraetedateien und FIFOS
    * O_SYNC -> Warten bis Schreibvorgang vollstaendig abgeschlossen (nur SystemV)
    * O_NOCTTY -> Falls der Pfad ein Terminal ist, wird dieses nicht das Kontrollterminal des Prozesses

    Wird O_CREAT gesetzt, benoetigt man das dritte Argument. (mode)

    User-Group-Other
    rwx -rwx  -rwx
    111 -111  -111
  0 7   - 7   - 7


  In #include <sys/stat.h> befinden sich folgende Flags:

  flag | description
  ---- | -----------
  S_ISUID | set user-ID bit (set inode set user id). Braucht man idR fuer Verzeichnisse oder Ausfuehrbare Dateien
  S_ISGID | set group-ID bit (set inode set group id). Braucht man idR fuer Verzeichnisse oder Ausfuehrbare Dateien
  S_ISVTX | saved text bit bzw. sticky bit
  S_IRUSR | read for user
  S_IWUSR | write for user
  S_IXUSR | executable for user
  S_IRWXU | Der User bekommt volle Rechte (=rwx)
  S_IRGRP | read for group
  S_IWGRP | write for group
  S_IXGRP | executable for group
  S_IRWXG | Die Gruppe bekommt volle Rechte (=rwx)
  S_IROTH | read for other
  S_IWOTH | write for other
  S_IXOTH | executable for other
  S_IRWXO | Others bekommt volle Rechte (=rwx)

  Alternativ zu open(..) kann creat(..) verwendet werden. Diese ist aequivalent zu open(..) mit den Flags:
  O_CREAT | O_WRONLY | O_TRUNC 

  Bemerkung: Einige Flags koennen zur Laufzeit (=waehrend die Datei geoeffnet ist) geaendert werden mit:
    fcntrl(...) // ausser oeffnen und schliessen alles kann. (=Zugriffsrechte)

  ```
  FILE * fopen (char * name, char * openflags)
  ```

  openflag | description
  -------- | -----------
  r | read
  w | write
  a | append
  \+ | read and write 
  b | binary file (macht nur fuer Windows Sinn, Unix unterscheidet sich da nicht)

#### Schliessen einer Datei:
  * \#include <unistd.h>
  
  ```
  int close (int fd); // 1. Um sauber zu arbeiten, 2. Option geben, dass nicht aufgeraeumt wird. Dann bleibt er noch offen. 
  ```

  Liefert 0 bei Erfolg, -1 bei Fehlerfall. Eine Obergrenze, wie viele Dateien maximal geoeffnet sein koennen, ist vorhanden (=rlimit, heisst Resourcelimit).
  
#### Lesen einer Datei:
  * \#include <unistd.h>

  ```
  ssize_t read (int fd, void * buffer, size_t bytes); // bytes darf die Puffergroesse nicht ueberschreiten. Der Rueckgabewert wird <= bytes sein. Nicht zu klein, nicht zu gross waehlen. 128, .., 512 Bytes
  ```

  Rueckgabewert: Im Erfolgsfall, tatsaechliche Anzahl gelesener Bytes. 
  Das Dateiende ist erreicht, wenn 0 zurueckgeliefert wird. -1 bei Fehlerfall

#### Schreiben einer Datei:
  * \#include <unistd.h>

  ```
  ssize_t write (int fd, void * buffer, size_t bytes); // bytes darf die Puffergroesse nicht ueberschreiten. Der Rueckgabewert wird <= bytes sein. Nicht zu klein, nicht zu gross waehlen. 128, .., 512 Bytes
  ```

  Schreibt zuerst alles in ein Buffer, wenn der Kernel mal Zeit hat, schreibt er es in die Datei. Wenn aus der Datei dann gelesen werden muss, liest er es aus dem Cache. Holt es nicht erst wieder aus dem File.

  Rueckgabewert: Tatsaechliche Anzahl geschriebener Bytes. 
  Bei Fehlerfall -1

#### Schreib-/Lesezeiger positionieren
  Nach oeffnen Lesezeichen meist am Anfang (Offset 0)

  Oeffnen zum Anhaengen (O_APPEND), so wird Lese-/Schreibzeichen vor jeder Schreibanforderung ans Ende gesetzt! Jedes Lesen und Schreiben bewegt Schreib-/Lesezeichen um tatsaechliche Anzahl Bytes vorwaerts.
  
  * \#include <unistd.h>
  * \#include <sys/types.h>

  ```
    int lseek (int fd, off_t offset, int woher)
  ```

  Rueckgabe: Ist neue Position des Zeigers oder -1
  Der Parameter 'offset' legt Byteanzahl fest, um die der Zeiger verschoben werden soll.
  Der Parameter 'woher' legt fest, von welcher Position aus verschoben wird.

  Value | Description
  ----- | -----------
  SEEK_SET | von Dateianfang Richtung Ende
  SEEK_CUR | von aktueller Position an (Richtung durch Vorzeichen bestimmt)
  SEEK_END | von Dateiende an (Richtung durch Vorzeichen)

  Momentane Position:
  ```
  int aktuelle_position = lseek(fd, 0, 'SEEK_CUR'); //Zeiger bleibt wo er ist, zeigt aber aktuelle Position
  ```

  In der Datei kann ein Loch entstehen, falls Zeiger an Position hinter das Dateiende gesetzt wird und geschrieben wird.
  Liest man das "Loch", erhaelt man fuer jedes Byte 0

#### Duplizieren von Filedeskriptoren

  Es gibt Anwendungsfaelle in denen das Duplizieren von Filedeskriptoren erforderlich ist. 
  Dafuer gibt es zwei Methoden. Diese befinden sich in
  
  * \#include <unistd.h>

  ```
    int dup(int fd);
    int dup2(int fd, int fd2);
  ```

  * Rueckgabe: Neuer Filedeskriptor oder -1 im Fehlerfall.
  * Bei ```int dup(int fd)``` wird naechstfreier Deskriptor verwendet.
  * Die Funktion ```int dub2(int fd, int fd2)``` verwendet als neuen Filedeskriptor den Wert des zweiten Argumentes. 
  * Deskriptor fd2 kann bereits geoeffnet sein, ```dub2``` schliesst diesen dann vorher. (Damit nicht allzu viele Filedeskriptoren offen bleiben). Sind ```fd2 == fd```, dann wird nicht erst geschlossen
  * Anwendung: Umlenkung von Ein-/Ausgabe

#### Kontrolle der Eigenschaften einer Datei

Moechte man Einstellungen zur Datei nachtraeglich auslesen oder aendern, so kann man das mit ```fcntl(...)```

  * \#include <fcntl.h>
  * \#include <unistd.h>

    ```
      int fcntl (int fd, int kommando, ... /* int args */);
    ```
    
  * Der Rueckgabewert ist im Erfolgsfall abhaengig vom Kommando. Im Fehlerfall -1
  * Die Verfuegbaren Kommandos lauten:

Kommando | Beschreibung
-------- | ------------
F_DUPFD | Dupliziert Filedeskriptor, drittes Argument ist neuer Filedeskriptor oder 0, dann wird der naechste Freie verwendet. Wie bei den beiden ```dup()```-Funktionen
F_DUPFD_CLOEXEC | Dupliziert Filedeskriptor, drittes Argument ist neuer Filedeskriptor oder 0, dann wird der naechste Freie verwendet. Wie bei den beiden ```dup()```-Funktionen
F_SETFD | Setzen von fdflags (Aktuell nur: FD_CLOEXEC)
F_GETFD | Abfragen von fdflags (Aktuell nur: FD_CLOEXEC)
F_SETFL | Setzen der Statusflags (Read, Write, Append, Sync, Nonblock)
F_GETFL | Abfragen der Statusflags (Read, Write, Append, Sync, Nonblock)
F_SETOWN | Setzen von PID/GID, Empfaenger von SIGIO/SIGURG
F_GETOWN | Abfragen von PID/GID, Empfaenger von SIGIO/SIGURG
F_SETLK | Setzen von RecordLocks, ich kann einen Dateibereich sperren
F_GETLK | Abfragen von RecordLocks, kann eine Datei im Bereich sperren
F_GETLKW | Setzen/Abfragen von RecordLocks

#### Filezeiger

  Die c-Bibliotheke verwendet die FILE-Struktur. Diese koennen in Filedeskriptoren umgewandelt werden. Dazu braucht man

  * \#include <stdio.h>
  
  ```
    int fileno (FILE *fz)
    FILE * fdopen(int fd, const char * modus)
  ```

  * fdopen liefert im Fehlerfall ```NULL``` zurueck. 
  * Der Parameter ```modus``` legt Zugriffsart fest, diese muss identisch mit der des Filedeskriptores sein.
  * Beachte: Der Inhalt der Datei wird im Modus 'w' nicht wie bei fopen geloescht.
  * fdopen wird gern verwendet, wenn man Pipes oder Sockets benutzt, welche nicht mit fopen geoeffnet werden koennen.
  * Bei einem mkdir werden IMMER ```. und ..``` erstellt als verknuepfung, damit es im Baum ersichtlich ist.

#### Arbeit mit Dateien und Verzeichnissen

##### Attribute von Dateien

  * stat folder um Daten anzuzeigen

  Fuer gewoehnlich besitzt die Struktur ```stat``` folgende Komponenten (Nur benutzen unter Linux. Microsoft speichert nicht Modes und Gruppen):

  ```
    struct stat {
      dev_t st_dev;             // Nummer des Geraetes, welches die Datei enthaelt
      ino_t st_ino;             // Nummer der i-Node
      mode_t st_mode;           // Dateiart und Zugriffsrechte
      nlink_t st_nlink;         // Anzahl der Links
      uid_t st_uid;             // User-ID des Eigentuemers
      gid_t st_gid;             // Group-ID des Eigentuemers
      dev_t st_rdev;            // Geraetenummer bei Geraetedatei
      off_t st_size;            // Groesse der regulaeren Datei in Byte
      blksize_t st_blksize;     // Optimale Blockgroesse fuer File IO
      blkut_t st_blocks;        // Anzahl belegte 512-Byte-Bloecke (bei reg. Dateien)
      time_t st_atime;          // Access-Time
      time_t st_utime;          // Modification-Time
      time_t st_ctime;          // Aenderungszeit des i-Node
    }
  ```

##### Kleiner Rueckblick 

  ```lseek (fd, 0L, SEEK_SET)``` 
  * Setze den Zeiger auf den Dateianfang

  ```lseek (fd, 25L, SEEK_CUR)```
  * Setze den Zeiger 25 Bytes weiter

  ```lseek (fd, -1L, SEEK_END)```
  * Das Ende der Datei (Letztes Relevantes Byte)

  Positionierung in stdin moeglich? 
  * Prinzipiell ist dies nicht moeglich. ABER: Wenn eine Dateiumlenkung gemacht wird, ist dies auch moeglich. Somit sind beide Antworten richtig 

  * Die Struktur ```stat``` enthaelt Informationen ueber die i-Node bzw. Datei

#### 5.2 Auslesen der Dateiattribute

  * \#include <sys/types.h>
  * \#include <sys/stat.h>

  ```
  int stat (const char * path, struct stat * buf); // Folgt nicht dem Link, sondern benutzt lediglich die i-Node des Links
  int fstat (int fd, struct stat * puffer);
  int lstat (const char * path, struct stat * puffer); // Da ein Link auch eine eigene i-Node hat, wird hier immer weiter bis zur Datei geleitet
  ```

  * Rueckgabe: Fehlerfall gibt -1 zurueck. Ansonsten kommt 0 zurueck

#### 5.3 Dateiarten

  Art | Beschreibung
  --- | ------------
  Regulaere Datei | Text/Binaerdatei beliebigen Formats
  Verzeichnis | Datei mit Liste von Verzeichniseintraegen und i-Node-Nummern
  Geraetedatei (special file) | Logische Beschreibungsdatei (= keine Physische Datei), von physischen oder virtuellem Geraet, I/O-Operationen verwenden den entsprechenden Geraetetreiber. Kernel laedt den Geraetetreiber, dann ist das Geraet verfuegbar, ueber Device-Node. Gibt eine eigene Bibliotheke dafuer. Es wird bei den Geraetedateien zwischen Zeichen- und Blockorientierten Geraeten unterschieden. 
  FIFO (= named pipe) | Dateien, welche zur Interprozesskommunikation verwendet werden. Koennen nur einmal gelesen werden. Keine Spruenge erlaubt.
  Sockets | Dateien, die eine Kommunikation ueber das Netzwork oder auch Lokal moeglich machen.
  Symbolische Links | Datei, die auf eine andere Datei zeigt. Unterscheiden Hard- und Softlink ist wichtig.

##### Variable st_mode

  * liefert Dateityp
  * Abfrage mit Makros (= Testmakros):
      
  Name | Beschreibung
  ---- | ------------
  S_ISREG () | Regulaere Datei
  S_ISDIR () | Verzeichnis
  S_ISCHR() | Zeichenorientiertes Geraet
  S_ISBLK () | Blockdevice
  S_ISFIFO () | Prueft, ob Datei eine Fifo ist
  S_ISLNK () | Systemlink
  S_ISSOCK () | Socket

  * Wo liegen diese Variablen? 

  ```grep -r S_IFREG /usr/include bzw. /usr/sys/stat.h```
  * Wenn wir __USE_MISC definieren bzw. __USE_XOPEN definieren, bekommen wir zusaetzlich in sys/stat weitere Symbole geliefert. 
  * \#include S_ISGID 007000 -> Oktal, die drei nullen nach der 7 sind dann fuer die Zugriffsrechte

#### 5.4 Dateizugriffsrechte

  Neben dem Dateityp sind in ```st_mode``` ebenfalls die Zugriffsrechte, sowie die speziellen Bits set-UID-Bit, set-GID-Bit und sticky-Bit kodiert.
  Was ist S_IFMT ? Filtert nur S_ISUID, S_ISGID und S_ISVTX heraus, quasi wie ```(st_mode & S_IFMT) == S_IFREG //passend fuer switch-case```

##### Einfache Zugriffsrechte

  * rwx fuer User, Group, Other
  * In der Summe 9 Bit

##### Erweiterte Zugriffsrechte

  * Ausfuehrbare Datei (= z.B. passwd) erweitert um Systemverwaltungsrechte
  * z.B. Datei ```/etc/shadow``` gehoert Systemverwalter (= root), normale User duerfen in die Datei nicht hineinschreiben, sollen aber ihr Passwort aendern duerfen.
  Ein zusaetzliches Flag an ausfuehrbarer Datei, erlaubt es, dass Benutzer das Programm 'im Auftrag' ausfuehren darf (quasi als root).
  Ein anderes Programm was es auch macht ist ```sudo```. Das gilt sowohl fuer Eigentuemer (SUID), als auch Gruppe (SGID).
  Wodurch ein Prozess neben seines realen (UID/GID) vom Nutzer, noch effektive Rechte (SUID/SGID) des Nutzers/der Gruppe dem die ausfuehrbare Datei gehoert zugeordnet bekommt. Quasi maximal 4 Schluessel moeglich. 
  Sudo = Generalschluessel
  * Im st_mode kann man die Zugriffsrechte aendern.

##### Aendern der Zugriffsrechte

  Rechte bereits bestehender Dateien koennen mit ```chmod (...)``` oder ```fchmod (...)``` geaendert werden. 

  * \#include <sys/types.h>
  * \#include <sys/stat.h>

  ```
    int chmod (const char * path, mode_t mode);
    int fchmod (int fd, mode_t mode);
  ```

  * mode_t kann man zusammen bauen, sind in /usr/include/linux/stat.h definiert. Z.B. S_IWUSR

##### Dateikreierungsmaske

  Die Dateikreierungsmaske (umask) enthaelt alle Rechte, die bei Erzeugung einer Datei nicht vergeben werden duerfen, selbst wenn sie von ```open (...)``` oder ```creat (...)``` angefordert worden.
  umask gibts als Kommando oder als Systemaufruf.

  * \#include <sys/types.h>
  * \#include <sys/stat.h>

  ```mode_t umask (mode_t mask);```

  Rueckgabe: Vorherige umask.
  Praktische Anwendung: Bisherige ```umask``` durch 0 ersetzen (=Alle Rechte erlauben), alte ```umask``` speichern und spaeter wieder zuruecksetzen

#### 5.5 Aendern von Besitzer und Gruppe

  * \#include <sys/types.h>
  * \#include <unistd.h>

  ```
    int chown (const char * path, uid_t owner, gid_t group);
    int fchown (int fd, uid_t owner, gid_t group);
    int lchown (const char * path, uid_t owner, gid_t group);
  ```

  Rueckgabe: Im Erfolgsfall 0, -1 bei Fehlern
  Beachte: Auf aktuellen Systemen _POSIX_CHOWN_RESTRICTED ist definiert, daraus folgt chown ist nur fuer Superuser! 
  Mittels ```getuid()``` kann reale Benutzerkennung eines Prozesses abgefragt/erfragt werden.
  
#### 5.6 Dateisystemverlinkungen

##### Hardlinks vs Softlinks (symbolische Links)

  Im Gegensatz zu Hardlinks koennen Softlinks ueber Dateisystemgrenzen hinweg verknuepft werden

  * \#include <unistd.h>

###### harte Links:

  ```
    int link ( const char * name, const char * linkname );
    // Rueckgabe: Im Erfolgsfall 0, -1 bei Fehlern

    int unlink ( const char * name );
    // Rueckgabe: Im Erfolgsfall 0, -1 bei Fehlern

    // Bemerkung: Eine durch unlink geschlossene/entfernte Datei wird nicht sofort geloescht, wenn diese noch durch andere Prozesse geoeffnet ist! Haeufiges Problem beim updaten 
  ```

###### sym Links:

  ```
    int symlink ( const char * destination, const char * symlink );
    // Rueckgabe: Im Erfolgsfall 0, -1 bei Fehlern

    // Bemerkung: Ein symbolischer Link kann nicht erzeugt werden, wenn Ziel und Symlink den gleichen Namen tragen und im selben Verzeichnis sein sollen.
  ```

  Beim Umgang mit Symlinks ist es vorteilhaft zu wissen, welche Systemfunktionen Links folgen und welche es nicht tun.

###### Funktionen, die Links folgen (= dereferenzieren): 

  * access
  * chdir
  * chmod
  * chown
  * creat
  * exec
  * link
  * mkdir
  * mkfifo
  * mknod
  * open
  * opendir
  * pathconf
  * stat
  * truncate

###### Funktionen, die symbolische Links verarbeiten:
  
  * lchown
  * lstat
  * readlink
  * rename
  * remove
  * unlink

  Ausnahme: rmdir, liefert Fehler, falls zu loeschender Pfad ein Softlink ist

  Moechte man auslesen, welches Ziel ein Link hat, kann man ```readlink(...)``` verwenden.

  * \#include <unistd.h>

  ```
    int readlink (const char * symlink, char * puffer, int size);
  ```

  Rueckgabe: Anzahl gelesener Bytes oder -1 bei Fehler. z.B. Wenn Ziel nicht mehr existiert. Der Puffer wird nicht nullterminiert

#### 5.7 Dateigroesse

  in struct ```stat```:

Name | Beschreibung
---- | ------------
st_size | Dateigroesse in Byte (fuer reg. Datei/Verzeichnis und syslinks)
st_blksize| ideale I/O Blockgroesse. 
st_blocks | Anzahl 512 Byte-Bloecke

  Wenn ```st_size = 0``` bei reg. Datei, dann ist sie leer. 
  Verzeichnisse haben gewoehnlich ```st_size``` als Wert ein vielfaches von 16.
  Bei symbolischen Links entspricht Dateilaenge/groesse der Laenge des Verweises/Pfades auf den der Link verweist.
  Bei Pipes entspricht ```st_size``` der Anzahl lesbarer Datenbytes. Die Groesse einer Datei kann geaendert werden: 

  * \#include <sys/types.h>
  * \#include <unistd.h>

   ```
   int truncate (const char * path, off_t laenge);
   ftruncate(int fd, off_t laenge);
   ```

   Rueckgabe: 0 bei Erfolg, bei Fehler -1
   Normalerweise: Reduzieren der Dateigroesse, etwa um sie zu leeren.
   Alternativ: Datei virtuell zu vergroessern. Zum Beispiel: Plattenplatz fuer einen bevorstehenden Download reservieren.

   Dabei koennen Loecher entstehen, die beim Lesen den ASCII-Wert 0 haben. 

#### 5.8 Zeiten einer Datei

   Zeiten in i-Node (= MAC-Times, Media Access Control):

Name | Beschreibung
---- | ------------
st_mtime | letzte Aenderung
st_atime | letzter Zugriff
st_ctime | letzte Aenderung i-Node

mtime und atime lassen sich nachtraeglich aendern. Dazu koennen die Funktionen ```utime``` bzw. ```utimes``` benutzt werden.

  * \#include <sys/types.h>
  * \#include <utime.h>

  ```
  int utime (const char * path, const struct utimbuf * tm);
  ```

  Rueckgabe: 0 bei Erfolg, -1 bei Fehler
  Parameter: 

  ```
  struct utimbuf {
    time_t actime; // access
    time_t modtime; // modification
  };
  ```

  Bemerkung: Eine Moeglichkeit, die Zeit der letzten i-Node-Aenderung zu aendern, besteht nicht.
  Jedes mal, wenn ```utime()``` aufgerufen wird, wird auch automatisch ```st_ctime``` des i-Node auf Systemzeit gesetzt.
  So dass man diese tatsaechlich Manipulieren kann.

  Die Werte ```actime``` und ```modtime``` sind Unix-Zeitstempel, also Sekunden seit dem 1.1.1970 um 00:00 Uhr.

  Fuer den Erfolg von ```utime(...)``` benoetigt man entsprechende Rechte. Genauer: Prozess (effektive UID) muss entweder Eigentuemer (also Owner) oder Superuser der Datei sein.
  Wird ```utime(...)``` mit Nullzeiger aufgerufen, werden beide Zeitstempel auf Systemzeit gesetzt. 
  Hierfuer reichen bereits Schreibrechte einer Datei (= wie ein ```touch```)! 

  BSD-Unix und Linux unterstuetzen weitere Funktion: 
  
  * \#include <sys/types.h>
  * \#include <utime.h>

  ```
  int utimes (const char * path, const struct timeval * tm); // tm[2] muss uebergeben werden, wegen timeval
  ```

  Rueckgabe: 0 bei Erfolg, -1 bei Fehler.

  Parameter:
  ```
  struct timeval {
    long tv_sec;
    long tv_usec;
  }
  ```

  ```utimes (...)``` erlaubt Mikrosekundengenauigkeit.

  Beispiel: Kopieren einer Datei ohne Aenderung der Zeiten

#### 5.9 Verzeichnisse

  Fuer die Arbeit mit Verzeichnissen stehen aehnliche Funktionen bereit, wie bei Dateien.

##### Anlegen eines neuen Ordners

  * \#include <sys/types.h>
  * \#include <sys/stat.h>

  ```
  int mkdir (const char * path, mode_t accessMode);
  ```

  Wurde der Ordner angelegt, liefert ```mkdir (...)``` 0, sonst -1.
  Zugriffsrechte sowieso UID/GID werden identisch zu Dateien festgelegt.

  Bemerkung: Bei Ordnern sollte man darauf achten, dass neben Lese- und Schreibrecht auch das Ausfuehrrecht gesetzt sein sollte.
  Um auf Dateien im Ordner zugreifen zu koennen.

##### Loeschen eines ordners

  Die entsprechende Funktion ```rmdir (...)``` loescht ein leeres Verzeichnis!

  * \#include <sys/types.h>
  * \#include <sys/stat.h>

  ```
  int rmdir (const char * path);
  ```

  War der ordner leer und konnte geloescht werden, wird 0 zurueckgeliefert. Sonst -1

##### Wechseln des Verzeichnisses

  Jedem Prozess ist ein sogenanntes Arbeitsverzeichnis zugeordnet (=Working Directory). 
  Shellbefehl ```pwd```

  * \#include <unistd.h>

  ```
  int chdir (const char * path);
  int fchdir (int fd);
  ```

  Rueckgabe: im Normalfall 0, bei Fehler -1

  Das Kommando ```cd``` ist kein C-Programm, sondern ein sogenanntes Shell-Buildin-Programm! (= Bei einem C-Programm wuerde man wieder in das 'alte' Verzeichnis landen. Das kann nur die Shell selber)

##### Aktuelles Arbeitsverzeichnis 

  * \#include <unistd.h>

  ```
  char * getcwd (char * buffer, size_t size);
  ```

  Rueckgabe: Im Erfolg Adresse des Puffers. Im Fehlerfall einen ```NULL```-Zeiger. Im Puffer wird der Pfadname des Verzeichnisses abgelegt, sein Ende wird mit ```\0``` terminiert.
  Beachte: 
  * Ist der uebergebene Puffer zu klein, wird 0 zurueckgeliefert.  
  * Ist das erste Argument ```NULL```, dann wird ```getcwd (...)``` dynamisch Speicher in uebergebener Groesse anfordern.
    Werden beide Parameter ```NULL (bzw 0)``` gesetzt, so liefert ```getcwd (...)``` einem Puffer zurueck, der genauso gross ist, wie benoetigt.

##### Lesen von Verzeichnissen

###### Verzeichniseintrag

  * Ist Systemabhaengige Datenstruktur
  * POSIX schreibt aber Systemunabhaengigen Teil vor

  ```
  struct dirent {
    ino_t d_ino;             // Seriennummer
    char d_name[NAME_MAX+1]; // Dateiname + Nullterminator (= '\0')
  }
  ```

  Damit Systemunabhaengig Verzeichnisse gelesen werden koennen, definiert POSIX folgende Funktionen:

  * \#include <sys/types.h>
  * \#include <dirent.h>

  ```
  DIR * opendir (const char * path);
  struct dirent * readdir (DIR * folder);
  void rewindDir (DIR * folder);
  int closedir (DIR * folder);
  ```

  Rueckgabe: 
    ```opendir``` und ```readdir``` liefern im Fehlerfall ```NULL```-Zeiger.
    ```closedir``` liefert ```0``` bei Erfolg, ```-1``` sonst.

  Die rekursive Verarbeitung von Verzeichnisbaeumen wird zusaetzlich durch zwei weitere Funktionen:

  ```
  ftw ( File Traverse walk )
  nftw ( new File Traverse walk )
  ```
  
  unterstuetzt. Diese beiden unterstuetzen eine Callback-Benutzerfunktion, welche fuer jeden Verzeichniseintrag aufgerufen wird.
  Unterschied zwischen den beiden ist, ```ftw``` folgt symbolischen Links, bei ```nftw``` kann man das abstellen.

#### 5.10 Geraetedateien

  Major Device Number und Minor Device Number in ```struct stat``` verfuegbar.
  Beispiel in ```st_dev``` findet man zu jeder Datei die Geraetenummer des Dateisystems.
  In der Komponente ```st_rdev``` findet man im Falle einer Geraetedatei genau die Nummern des zugeordneten Geraetes. 
  Die Major Device Number = Geraetetyp/Geraeteklasse, waehrend die Minor Divice Number zur Unterscheidung verschiedener Geraete gleichen Typs benutzt wird.

##### spezielle Geraetedateien

  ```/dev/null``` 

  * schreiben endlos moeglich, ist ein Muellschlucker. Daten werden nicht verarbeitet.
  * Lesen liefert sofort EOF (= End of filestream). Wird gerne zum leeren von Dateien verwendet

  ```/dev/zero```

  * schreiben endlos moeglich, Daten werden nicht verarbeitet. Kann auch als Muellschlucker verwendet werden.
  * Lesen liefert endlose Folge von Nullen. Wird gerne verwendet, um Dateien mehrfach mit nullen zu ueberschreiben (Loeschen) oder Dateisysteme zu formatieren.

  ```/dev/full```
  
  * Schreiben auf dieses Geraet ist nicht moeglich, auf dem Geraet ist kein Speicherplatz mehr verfuegbar.
  * Benutzen, um ein Programm auf Fehlertoleranz zu testen
  * Lesen liefert eine endlose Folge von Nullen 

  ```/dev/random```
  
  * Erzeugt zufaellige Folge von bits.
  * Der Zufall beruht auf reinen Zufallsquellen.
  * Aendern die Zufallsquellen ihren Zustand nicht, liefert das Geraet auch keine weiteren bits.

  ```/dev/urandom```
  
  * Erzeugt zufaellige Folge von bits.
  * Folge beruht auf Pseudozufallszahlen.

#### 5.11 Der Puffercache

  Betriebssysteme Unterhalten Puffer fuer externe Speichermedien, um zu schreibende Daten zwischenzuspeichern (= Delayed Write).
  Ziel: Anzahl Zugriffe auf Geraet minimieren, Verarbeitungsgeschwindigkeit maximieren, da jeder Zugriff Zeit kostet (= IO Wait).
  Nachteil: Bei Systemabsturz sind gepufferte Daten verloren.
  Eine Anwendung kann physikalisches Schreiben veranlassen. Dazu gibt es folgende Funktionen: ```sync (...)``` und ```fsync (...)```

  * \#include <unistd.h>

  ```
  void sync (void);
  void fsync (int fd);
  ```

  Rueckgabe: ```fsync``` liefert 0 bei Erfolg, sonst -1

  ```sync``` veranlasst physikalisches Schreiben aller Puffer. Die Funktion kehrt sofort zurueck, ohne auf das Ende aller Schreibvorgaenge zu warten.
  Sie wird von einem Hintergrundprozess automatisch alle 30 Sekunden aufgerufen. ```fsync``` bezieht sich nur auf eine Datei und veranlasst somit also nur das Schreiben des zugehoerigen Puffers.
  Ausserdem wartet ```fsync``` bis die Operation beendet ist.

#### 6. System- und Benutzerinformationen 

#### 7. Prozesse unter Linux

  * Ein Prozess ist ein laufendes Programm
  * Ein und dasselbe Programm kann mehrfach laufen
  * Ein Computer kann aber nur ein Programm ausfuehren (= Kernel)

  Der Kernel muss demzufolge in der Lage sein, beliebig weitere Programme zu starten und zu beenden (auch wenn das Programm nicht beenden laesst!)
  Multitasking bedeutet, dass die Ressource die CPU-Zeit verwaltet werden muss. Die Zuteilung unterliegt Regeln. Das macht die Komponente Schedular. Der Benutzer merkt so gut wie nicht,
  dass laufender Prozess staendig wechselt.

  Damit das fehlerfrei von statten geht benoetigt Kernel zusaetzliche Informationen. 
  z.B.: 

  * auszufuehrender Programmcode
  * Prozessumgebung (Environment)
  * Speicher
  * Zugriff auf Ressourcen
  * Dateisystem
  * Externe Geraete
  * Treiber

##### 7.1 Starten eines Prozesses

  Eine Startup-Routine im Kernel sorgt dafuer, dass beim Starten eines Programmes die ```main``` gebunden und aufgerufen wird, sowie mit entsprechenden Parametern versehen und Umgebungsdaten verfuegbar gemacht wird.

  ```
  int main (int argc, char * argv[]);
  ```

  enthaelt an Stelle argv[argc] einen Nullzeiger (=POSIX C-Standard)

##### 7.2 Beenden eines Prozesses

  Linux unterscheidet zwei Arten, wie ein Prozess beendet werden kann:

  * erreicht Ende von ```main (...)``` und liefert einen Wert zurueck. Alternativ kann ```exit (...)``` verwendet werden.
  * ausserdem Abbruch z.B. durch ein externes Signal oder Aufruf von ```abort ()```

###### Exit-Status eines Prozesses 

  Beenden mit Aufraeumen

  Beendet sich ein Programm regulaer, liefert es einen Wert zurueck. Aufruf ```$?``` in der Konsole. Gibt z.B. Aufschluss ueber Erledigung von Aufgaben.
  Rueckgabe: Bei Erfolg typischerweise 0, sonst ein von 0 verschiedener Wert

  * \#include <stdlib.h>
  
  ```
  void exit(int status);
  ```

  Beenden ohne Aufraeumen

  Beendet sich ein Programm normal, werden zuvor noch alle Puffer geleert, alle Dateien geschlossen und die mit ```tmpfile (...)``` angelegten geloescht.
  Nach dem Aufraeumen ruft ```exit (...)``` seinerseits ```_exit (...)``` auf, um zum Kern zurueckzukehren.

  * \#include <stdlib.h>

  ```
  void _exit (int status);
  ```

  Diese Funktion (von POSIX vorgeschrieben) bewirkt sofortige Rueckkehr zum Kernel ohne aufraeumen.

  Zusaetzliches Cleanup 

  Das Aufraeumen laesst sich, um benutzerdefinierte Routinen erweitern. Zum Registrieren einer eigenen Cleanup-Funktionen kann ```atexit (...)``` genutzt werden.

  * \#include <unistd.h>

  ```
  int atexit( void (* funktion ) (void) );
  ```
  
  Im Fehlerfall liefert ```atexit (...)``` einen Wert verschieden von 0, zum Beispiel wenn versucht wird, mehr als 32 Handler zu registrieren

  Funktionen koennen mehrfach registriert werden, was zu mehrmaligen Aufruf fuehrt. Die Aufgrufe finden in umgekehrter Reihenfolge der Registrierung statt.

  alternativ zu ```int main (int argc, char * argv[])```:

  * ```int main (void)```
  * ```void main (int argc, char * argv[])```
  * ```void main (void)```

    Bemerkung: Dennoch existieren nach Konvention dort auch Rueckgabewert und Parameter

##### 7.3. Umgebungsvariablen

  * Anzeigen mit ```echo $``` in der bash
  * Interaktion/Anpassung mit/an System- bzw. Benutzerumgebung
  * Zugriff auf Umgebungsvariablen durch durch Deklaration von ```extern char * environ[];```

  Die Variablenbelegung ist in Form:
    name = Wert als Stringarray, Nullterminiert verfuegbar

  * z.B.
    * ```echo $LANG```, die Sprache die benutzt wird
    * ```echo $MACHTYPE```, die Architektur
    * ```echo $HOST```, der HOSTNAME

###### Abfragen von Umgebungsvariablen

  * \#include <stdlib.h>

  ```
  char * getenv(const char * name);
  // gibt Zeiger auf Wert von einer Umgebungsvariable oder NULL falls Name nicht vorhanden
  ``` 

###### Veraenderung von Umgebungsvariablen

  * \#include <stdlib.h>

  ```
  int putenv (const char * entry);                                      // Name = Wert
  int setenv (const char * name, const char * value, int overwrite);    // Falls Eintrag vorhanden ist, kann der Wert ueberschrieben werden
  void unsetenv (const char * name);
  int clearenv (void);
  ```

  Rueckgabe: 0 bei Erfolg, im Fehlerfall von 0 verschieden

  Parameter: 

  Methode | Parameter
  ------- | ---------
  putenv | name = Wert. Sollte Name bereits existieren, wird bisheriger Eintrag entfernt
  setenv | Aendert Name nur, wenn overwrite verschieden von 0 
  unsetenv | Loeschen eines Eintrages
  clearenv | Loeschen des gesamten Environment. ```clearenv``` verweitert arbeit, falls Environment veraendert wurde, ohne ```putenv```, ```setenv```, ```unsetenv``` zu verwenden.

  Alternativ:

  Loeschen des Environments mittels:
  ```environ = NULL;```

##### Dynamisches Anfordern von Speicher

  Die Standard-C stellt zur Verfuegung:

  * \#include <stdlib.h>

```
void malloc (size_t size);                        // Size Wert in Bytes
void * calloc (size_t amount, size_t size);       // Anzahl Elemente, mit passenden Wert. Gut fuer Arrays
void * reallocate (void * ptr, size_t size);      // Vergroessern/Verkleinern des Speichers der bereits auf dem Heap liegt
```

```
                      ------------
Hoechste Addresse    |            | Kommando Zeilenargumente + Environment
                      ------------
                     |    STACK   | Lokale (automatic) Variable und Sprungaddresse 
                      ------------
                     |     ||     |
                     |     \/     |
                     |    Free    |
                     |   memory   |
                     |     /\     |
                     |     ||     |
                      ------------
                     |    HEAP    | Dynamisch angeforderter Speicher
                      ------------
                     |    bss     | Mit 0 initialisierte globale Variable (z.B. Ausserhalb der Main-Methode, dann hat Wert 0. Lokal ists ein Zufallswert, der Bereits drin steht!)
                      ------------
                     |    data    | initialisierte globale Variable
                      ------------
Niedrigste Addresse  |    text    | Programmcode (Shared, meist read-only. Ein Programm kann man jedoch auch manipulieren. z.B. Debugger)
                      ------------
```

mit ```size ./programm``` kann der ganze Speicher eingesehen werden

Konnte geforderter Speicherplatz reserviert werden, so liefern alle Funktionen die Anfangsaddresse, falls nicht erhaelt man Nullzeiger.
Im Unterschied zu ```malloc ()``` initialisiert ```calloc ()``` den Speicherbereich mit 0en.
Moechte man einen Speicherbereich verkleinern/vergroessern, kann ```realloc ()``` benutzt werden.

##### Freigabe dynamisch angeforderten Speichers

  * \#include <stdlib.h>

  ```
  void free (void * ptr);
  ```

  Wird eine Addresse ausgegeben, die nicht vorher mit ```malloc```, ```realloc``` oder ```calloc``` reserviert wurde, so ist das Verhalten undefiniert. Speicherverwaltung kann initialiisert werden! Evt. Absturz des Prozesses

  Laut C-Standard sind folgende Aufrufe identisch:
  ```
  realloc (NULL, groesse)
  ```

  und

  ```
  malloc(groesse)
  ```

  Diese liefern beide einen neuen Speicher

  ```realloc(addresse, 0)```
  und
  ```free(addresse)```
  geben allokierten Speicher frei. Ein Aufruf von ```free(NULL)``` ist wirkungslos

##### Anfordern von Speicherplatz im Stack

  * \#include <stdlib.h>

  ```
  void alloca (size_t size)
  ```

  Liefert Addresse des Speicherbereichs oder ```NULL``` bei Fehler. Speicher wird im Bereich des Stacks reserviert. Dabei wird Stackbereich der momentanen Funktion erweitert.
  Wenn die Funktion abgearbeitet ist, wird der Speicher automatisch wieder frei gegeben. 
  Gefaehrlich ist, wenn der Speicherplatz im Stack nicht ausreicht und ```alloca()``` einen Stack-Overflow hervorrruft. Weiterer Ablauf undefiniert.

#### 7.5 Ressourcenbeschraenkungen

  Die Ressourcenvergabe an Prozesse (Speichergroesse, CPU-Zeit, Anzahl geoeffneter Dateien, Stackgroesse, ...) ist durch den Kernel beschraenkt. Diese Schranken (=limits) sind konfigurierbar.
  In einem gewissen Bereich kann ein Prozess diese Schranken selbst waehlen.
  Erfragen und Setzen von Limits:
  ```getlimits()```
  ```setlimits()```
  Beide benutzen die Datenstruktur ```rlimit```

  * \#include <sys/tyime.h>
  * \#include <sys/resource.h>

  ```
    int getrlimit(int resource, struct rlimit * ptr);
    int setrlimit(int resource, const struct r limit * ptr);;
  ```

  Rueckgabe: 0 bei Erfolg, != 0 bei Fehler

  Die Struktur ```rlimit``` enthaelt zwei Komponenten

  ```
  struct rlimit 
  {
    rlimit rlim_cur;    // Aktuelles Limit
    rlimit rlim_max;    // max. Limit
  }
  ```

  Die Konstante ```RLIM_INFINITY``` drueckt aus, dass fuer eine Ressource keine Beschraenkung gilt. 
  Ein Prozess darf sein Limit frei waehlen, solange es gleich dem max. Wert ist. 
  Nur Superuser darf den Maxwert erhoehen!

  Praktische Relevanz: z.B. Testen von Software
  Einige Limits und ihre Bedeutungen:

  Name | Beschreibung
  ---- | ------------
  RLIMIT_CORE | Beschraenkt Groesse von Core-Files
  RLIMIT_CPU | CPU-Zeit je Prozess
  RLIMIT_DATA | Datensegmentgroesse
  RLIMIT_FSIZE | Dateigroessenbeschraenkung
  RLIMIT_NOFILE | Anzahl geoeffneter Dateien
  RLIMIT_NICE | nice-Wert Beschraenkung
  RLIMIT_NPROC | Beschraenkung Prozessanzahl
  RLIMIT_STACK | Stackgroessenbeschraenkung
  RLIMIT_AS | Addressraum

#### 7.6. Ressourcenverbrauch

  Abfrage mit:
  * \#include <sys/time.h>
  * \#include <sys/resource.h>
  * \#include <unistd.h>

  ```
  int getrusage (int whom, struct rusage * usage)
  ```

  Rueckgabe: 0 bei Erfolg, -1 sonst

  Der erste Parameter entscheidet darueber, von wem man den Ressourcenverbrauch erfragen moechte. Das kann sein:

  Name | Beschreibung
  ---- | ------------
  RUSAGE_SELF | Prozess selbst (inkl. Threads)
  RUSAGE_CHILDREN | Alle Kindprozesse
  RUSAGE_THREAD | von aufrufendem Thread

  zweiter Parameter:

  ```
  struct rusage {
    struct timeval ru_utime; /* user CPU time used */
    struct timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
  };
  ```

#### 7.7. Identifikation von Prozessen

  Intern: PID (= Prozess-ID)

  Kern stellt fest, dass es keine zwei Prozesse mit selber PID geben kann.
  Bis auf wenige Ausnahmen haben alle Prozesse Elternprozess, der Start veranlaesst.
  Kernel vermerkt zu jedem Prozess die Parent-Process-ID (=PPID).
  Beide Angaben ergeben Baumstruktur (Prozesshierarchie)

