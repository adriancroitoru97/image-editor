# Image editor in C

*Imaginile P2 si P5 sunt stocate pixel cu pixel intr-o matrice alocata dinamic,
iar cele P3 si P6 sunt stocate in 3 matrice, corespunzand pixelilor R, G si B.
*Este definita o structura care contine toate aceste matrice, tipul imaginii,
dimensiunile si maximul dintr-un pixel.
*Este preluata fiecare linie introdusa si split-uita pe bucati, OPERATIA si
ARGUMENTELE OPERATIEI. In functie de operatie, se realizeaza diferitele seturi de
instructiuni.

### LOAD
	*Se deschide fisierul dat ca argument (in mod binar sau ascii), se parcurge si
	se stocheaza informatiile despre imaginea curenta in structura "poza".
	*Matricele sunt alocate dinamic.

### SAVE
	*Se deschide fisierul dat ca argument, iar acesta este populat cu 
	informatiile stocate la LOAD in structura "poza".

### SELECT
	*Se folosesc 4 variabile, care stocheaza cele 2 colturi ale selectiei. 
	*La fiecare din functiile ce urmeaza, se tine cont de acestea in 
	efectuarea modificarilor.
	*Pentru SELECT ALL, se revine la dimensiunile 
	imaginii ---> ((0, 0) ; (latime, lungime)).

### CROP
	*Se foloseste o structura auxiliara, "poza2". In aceasta se stocheaza 
	imaginea crop-uita, dupa care imaginea initiala este eliminata. 
	*Se copiaza in "poza" imaginea crop-uita din "poza2", iar structura auxiliara
	"poza2" este eliminata. Practic, imaginea pe care se lucreaza de acum inainte
	este crop-ul proaspat realizat. Sunt actualizate toate informatiile imaginii.

### ROTATE
	*Se foloseste un algoritm de rotire a unei matrice patratice. 
	*Astfel, matricea este rotita cu 90 de grade la dreapta prin 
	transpunerea acesteia, urmata de inversarea tuturor coloanelor. 
	*Toate celelalte rotiri de diferite unghiuri se realizeaza prin rotirea 
	repetata cu cate 90 de grade la dreapta.
	*Pentru rotirea unei imagini intregi, aceasta se completeaza cu negru
	pana devine un patrat, iar apoi se aplica algoritmul descris anterior. 
	*In final, se da crop la suprafata neagra, ramanand imaginea dorita.

### GRAYSCALE, SEPIA
	*Se parcuge selectia si se aplica formulele specifice pentru fiecare operatie,
	fiind folosita o functie de round pentru a rotunji rezultatele la 
	cel mai apropiat intreg. Schimbarile se realizeaza direct pe structura "poza".

### EXIT
	*Se opreste citirea de operatii de la tastatura, se elibereaza memoria
	si se inchide programul.
	
## License
[Adrian-Valeriu Croitoru](https://github.com/adriancroitoru97)
