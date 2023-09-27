%% Practica03GangosoJorge

% Jorge Gangoso Kl�ck
% Tiempo: Incluye aqu� el tiempo dedicado a realizar el guion
%% Paso 1
close all; clear all; clc;
alf=['x' 'y' 'z'];
seqob=['y' 'z' 'x' 'z' 'z'];

%% Paso 2
indseqob=[2 3 1 3 3];

%% Paso 3
indseqob=zeros(1,numel(seqob),'uint16');
%% Paso 4
% A REALIZAR POR LOS ESTUDIANTES. INCLUIR C�DIGO AQU�

% Incluye en el paso 4 del fichero Practica03ApellidoNombre.m el c�digo 
% para convertir la secuencia seqob en �ndices del rango [1:numel(alf)]. 
% Dichos �ndices los almacenar�s en indseqob. Comprueba que  indseqob 
% contiene [2 3 1 3 3].
alf_num = [1:numel(alf)]

for i = 1:numel(alf)
   idx = seqob(:) == alf(i);
   indseqob(idx) = alf_num(i);
end


%% Paso 5
counts=[29 48 100];
code=arithenco(indseqob,counts)

%% Paso 6

indseqdec=arithdeco(code,counts,numel(indseqob));
seqdecf=alf(indseqdec);
fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(seqob,seqdecf))

%% Paso 7

close all; clear all;
seqob=[1 1];
counts=[1 1];
code=arithenco(seqob,counts)
fprintf('Longitud de la secuencia codificada %d\n',...
    numel(code))

%% Paso 8

% A REALIZAR POR LOS ESTUDIANTES. ENTREGA DE DISCUSION EN 
% Practica03ApellidoNombre.pdf 

% Compara en el paso 8 del fichero Practica03ApellidoNombre.pdf esta 
% longitud con la que la teor�a nos dice que es una cota superior al 
% n�mero de bits necesarios.



%% Paso 9 

close all; clear all;
seqob=[1 1];
counts=[50 50];
code=arithenco(seqob,counts)
fprintf('Longitud de la secuencia codificada %d\n',...
    numel(code))

%% Paso 10

% A REALIZAR POR LOS ESTUDIANTES. ENTREGA DE DISCUSION EN 
% Practica03ApellidoNombre.pdf 


% �Por qu� crees que ahora la longitud de la secuencia es 11 cuando las 
% frecuencias [1 1] y [50 50] producen las mismas probabilidades?

%Incluye la discusi�n en el paso 8 del fichero Practica03ApellidoNombre.pdf 

%% Paso 11

clear all;close all; clc;
maximo= 0.0;
minimo=0.0;
rng(0);
while maximo==minimo
seq=randsrc(1,100000,[1 2; 0.01 0.99]);
maximo=max(seq(:));
minimo=min(seq(:));
end
histo=histc(seq,[1 2]);
bar([1 2],histo);

%% Paso 12

code=arithenco(seq,histo);
fprintf('Longitud de la secuencia codificada %d\n',numel(code));
indseqdec=arithdeco(code,histo,numel(seq));
fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(seq,indseqdec))

%% Paso 13

% A REALIZAR POR LOS ESTUDIANTES. Entregar c�digo Matlab y discusi�n

% Realiza un estudio de c�mo evoluciona el n�mero de bits por s�mbolo 
% cuando generamos 10^i, i=1,2,3,4,5,6 s�mbolos siguiendo el proceso del 
% paso 11 con probabilidades pr(1)=0.1 y pr(2)=0.9.  Para cada uno de los 
% 6 casos,  realiza 5 simulaciones distintas y calcula el n�mero medio de 
% bits por s�mbolo como una media de las 5 simulaciones. Dibuja los 30 
% valores obtenidos as� como las medias de los 5 valores para las 10,100,
% 1000,10000, 100000 y 1000000 simulaciones. Dibuja tambi�n una l�nea con el valor
% de la entrop�a de la fuente. �Obtienes alg�n resultado que en principio
% parezca incorrecto entre la entrop�a de la fuente y los bits por s�mbolo?.
% �Cu�l ser�a la explicaci�n?

% Incluye el c�digo en el paso 13 del fichero Practica03ApellidoNombre.m 
% y la discusi�n en el paso 13 de  Practica03ApellidoNombre.pdf.
medias = [];
valores_medios = [];
entropias = [];
H = -( 0.1*log2(0.1)+0.9*log2(0.9) );
for i = [1 2 3 4 5 6]
    sumatoria = 0;
    for j = [1 2 3 4 5]
        maximo= 0.0;
        minimo=0.0;
        rng(j);
        while maximo==minimo
        seq=randsrc(1,10.^i,[1 2; 0.1 0.9]);
        maximo=max(seq(:));
        minimo=min(seq(:));
        end
        count = histc(seq, [1 2]);
        code = arithenco(seq, count);

        sumatoria = sumatoria + (numel(code)/10.^i);
        valores_medios(i,j) = (numel(code)/10.^i);
    end
    fprintf('Bits medios de la iteracion %i: %d\n',i,sumatoria/5);
    medias(i) = sumatoria/5;
    entropias(i) = H;
end
figure;
plot([1 2 3 4 5 6], medias);
hold on;
x = [1 1 1 1 1 2 2 2 2 2 3 3 3 3 3 4 4 4 4 4 5 5 5 5 5 6 6 6 6 6];
scatter (x, valores_medios(:))
hold on;
plot([1 2 3 4 5 6], entropias);
legend("medias","valores medios","entropias");
hold off;
%% Paso 14 

% A REALIZAR POR LOS ESTUDIANTES. Entregar c�digo Matlab y discusi�n

%Como habr�s podido comprobar emp�ricamente, la codificaci�n aritm�tica es 
%m�s eficiente cuanto mayor sea la longitud de la secuencia a codificar, 
%es decir, el n�mero medio de bits necesarios para representar cada s�mbolo 
%se acerca m�s a la entrop�a cuantos m�s caracteres codificamos. 
%Comprobaremos de nuevo emp�ricamente este hecho usando los ficheros de 
%texto contenidos en el fichero textobinario.zip. 

% Los ficheros de texto en textobinario.zip contienen s�lo dos caracteres, 
% el car�cter '0' y el car�cter '1'. El nombre de cada fichero es textoX.txt 
% donde X representa el n�mero de caracteres en el fichero. Observa que 
% los caracteres �0� y �1� vas a tener que codificarlos como 1 y 2.

%Incluye en el paso 14 de Practica03ApellidoNombre.m el c�digo para 
%   1.	codificar y decodificar cada uno de estos ficheros, 
%   2.	comprobar que la secuencia original y decodificada coinciden,
%   3.	dibujar los histograma de los s�mbolos en cada fichero. 

% Incluye los histograma, la tabla que contiene el n�mero de bits por s�mbolo 
% para cada fichero y las conclusiones que puedas extraer en el paso 14 de
% Practica03ApellidoNombre.pdf.
clear all; close all; clc;
for indice = [1 2 3 4 5 6]
   %Seleccionar el fichero en cuestion
   numero = 10.^indice;
   fichero = "texto"+numero+".txt";
   %Abrir y leer el fichero
   f = fopen(fichero, 'r');
   [words count] = fread(f, inf, 'char');
   fclose(f);
   
   histograma= histc(words,[48 49]);
   
   new_words=zeros(1,numel(words),'uint8');
   alf = [48 49];
   alf_num = [1:numel(alf)];

    for i = 1:numel(alf)
       idx = words(:) == alf(i);
       new_words(idx) = alf_num(i);
    end

   histograma = histc(new_words, [1 2]);
   subplot(3,2, indice);
   bar([1 2], histograma);
   string = "fichero: "+fichero;
   title(string);
   code = arithenco(new_words, histograma);
   fprintf('Longitud de la secuencia codificada %d\n',numel(code));
   fprintf('Cantidad de bits por simbolo %d\n',numel(code)/count);
   indseqdec=arithdeco(code,histograma,numel(new_words));
   fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
   isequal(new_words,indseqdec));
end


%% Paso 15

% A REALIZAR POR LOS ESTUDIANTES. Entregar c�digo Matlab y discusi�n

% Utiliza codificaci�n aritm�tica para codificar cada uno de ficheros de 
%texto constitucion espa�ola.txt, Fundacion e Imperio - Isaac Asimov.txt 
% y Cinco semanas en globo - Julio Verne.txt 
% (dentro de Pr�cticas -  Datos - texto.zip). 

%Incluye en el paso 15 de Practica03ApellidoNombre.m el c�digo para 
%1.	codificar y decodificar cada uno de estos ficheros, 
%2.	comprobar que la secuencia original y decodificada coinciden,
%3.	dibujar los histogramas de los s�mbolos en cada fichero,
%4.	calcular el factor de compresi�n obtenida para cada uno de los ficheros,
%5.	calcular el n�mero de bits por s�mbolo para cada fichero.

%En el paso 15 de  Practica03ApellidoNombre.pdf incluye 
%1.	los histogramas, 
%2.	completa las tablas adjuntas, para la codificaci�n Huffman no incluyas 
%   el tama�o de la cabecera y
%3.	realiza una comparaci�n cr�tica de los resultados obtenidos usando 
%   codificaci�n Huffman y aritm�tica
clear all; close all; clc;
for fichero = ["constitucion espa�ola.txt" "FUNDACION E IMPERIO - Isaac Asimov.txt" "Cinco semanas en globo - Julio Verne.txt"]

    %Abrir y leer el fichero
    fprintf("Fichero: %s\n", fichero);
    f = fopen(fichero, 'r');
    [words count] = fread(f, inf, '*uint8');
    fclose(f);
    
    histograma = histc(words, [1:256]);
    idx = find(histograma > 0); %Elementos que aparecen m�s de una vez
    alfabeto = [1:numel(idx)];
    new_words = [];
    for i = 1:numel(idx)
        indices = find(words == idx(i)); 
        new_words(indices) = alfabeto(i);
    end
    
    histograma = histc(new_words, alfabeto);
    figure;
    
    bar(alfabeto, histograma);
    title(fichero);
    
    %Compresi�n aritm�tica
    code = arithenco(new_words, histograma);
    fprintf('Tama�o fichero original %d\n', count);
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/count);
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/count;
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la se�al
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/count);
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
     isequal(new_words,uint8(deco)))
 
end





%% Paso 16

% A REALIZAR POR LOS ESTUDIANTES. Entregar c�digo Matlab y discusi�n

% Utiliza codificaci�n aritm�tica sobre los ficheros de im�genes  
% ptt1.pbm, ptt4.pbm, ptt8.pbm (dentro de material complementario 
% - Datos para pr�cticas - imgs_binarias.zip) y camera.pgm, bird.pgm y 
% bridge.pgm (dentro de Pr�cticas -  Datos - imgs_grises.zip).  

%Incluye en el paso 16 de Practica03ApellidoNombre.m el c�digo para 
%1.	codificar y decodificar cada uno de estos ficheros, 
%2.	comprobar que la secuencia original y decodificada coinciden,
%3.	dibujar los histogramas de los s�mbolos en cada fichero,
%4.	calcular el factor de compresi�n obtenida para cada uno de los ficheros,
%5.	calcular el n�mero de bits por s�mbolo para cada fichero.%

%En el paso 16 de  Practica03ApellidoNombre.pdf incluye 
%1.	los histogramas, 
%2.	completa las tablas adjuntas, para la codificaci�n Huffman no incluyas el tama�o de la cabecera y
%3.	realiza una comparaci�n cr�tica de los resultados obtenidos  usando codificaci�n Huffman y aritm�tica

clear all; close all; clc;
for fichero = ["ptt1.pbm" "ptt4.pbm" "ptt8.pbm"]

     %Abrir y leer el fichero
    fprintf("Fichero: %s\n", fichero);
    [words] = imread(fichero);
    %Convertir a vector fila
    [fil col] = size(words);
    words=reshape(words,1,fil*col);
    words = uint8(words);
    
    histograma = histc(words, [0 1]);
    
    idx = find(histograma > 0); %Elementos que aparecen m�s de una vez
    alfabeto = [1:numel(idx)];
    new_words = [];
    for i = 1:numel(idx)
        indices = find(words == idx(i)-1); 
        new_words(indices) = alfabeto(i);
    end
    
    histograma = histc(new_words, alfabeto);
    
    figure;
    bar(alfabeto, histograma);
    title(fichero);
    
    
    %Compresi�n aritm�tica
    code = arithenco(new_words, histograma);
    fprintf('Tama�o fichero original %d\n', length(words));
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/length(words));
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    prob_letras_usadas = [];
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/length(words);
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la se�al
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/length(words));
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,uint8(deco)))

 
end

for fichero = ["camera.pgm" "bird.pgm" "bridge.pgm"]
    
    %Abrir y leer el fichero
    fprintf("Fichero: %s\n", fichero);
    f = fopen(fichero, 'r');
    [words count] = fread(f, inf, '*uint8');
    fclose(f);
    
    histograma = histc(words, [0:255]);
    idx = find(histograma > 0); %Elementos que aparecen m�s de una vez
    alfabeto = [1:numel(idx)];
    new_words = [];
    for i = 1:numel(idx)
        indices = find(words == idx(i)-1); 
        new_words(indices) = alfabeto(i);
    end
    
    histograma = histc(new_words, alfabeto);
    
    figure;
    bar(alfabeto, histograma);
    title(fichero);
    
    
    %Compresi�n aritm�tica
    code = arithenco(new_words, histograma);
    fprintf('Tama�o fichero original %d\n', count);
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/count);
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    prob_letras_usadas = [];
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/count;
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la se�al
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/count);
    fprintf('�Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,deco));
end
%% Paso 17

% A REALIZAR POR LOS ESTUDIANTES. Discusi�n en pdf

% No hemos discutido en clase qu� cabecera debemos incluir en el fichero 
% codificado para que el decodificador sea capaz de reconstruir el fichero
% original. Suponiendo que, como mucho, las letras del alfabeto son 256,  
% �que cabecera incluir�as?. No olvides incluir las frecuencias o 
% probabilidades si lo consideras necesario. Podemos incluir la longitud 
% de la secuencia a decodificar, �habr�a alguna forma de no tener que 
% incluir el n�mero de s�mbolos a decodificar?.

% Incluye la discusi�n en el paso 17 de  Practica03ApellidoNombre.pdf.


