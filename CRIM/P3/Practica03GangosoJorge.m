%% Practica03GangosoJorge

% Jorge Gangoso Klöck
% Tiempo: Incluye aquí el tiempo dedicado a realizar el guion
%% Paso 1
close all; clear all; clc;
alf=['x' 'y' 'z'];
seqob=['y' 'z' 'x' 'z' 'z'];

%% Paso 2
indseqob=[2 3 1 3 3];

%% Paso 3
indseqob=zeros(1,numel(seqob),'uint16');
%% Paso 4
% A REALIZAR POR LOS ESTUDIANTES. INCLUIR CÓDIGO AQUÍ

% Incluye en el paso 4 del fichero Practica03ApellidoNombre.m el código 
% para convertir la secuencia seqob en índices del rango [1:numel(alf)]. 
% Dichos índices los almacenarás en indseqob. Comprueba que  indseqob 
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
fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
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
% longitud con la que la teoría nos dice que es una cota superior al 
% número de bits necesarios.



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


% ¿Por qué crees que ahora la longitud de la secuencia es 11 cuando las 
% frecuencias [1 1] y [50 50] producen las mismas probabilidades?

%Incluye la discusión en el paso 8 del fichero Practica03ApellidoNombre.pdf 

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
fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(seq,indseqdec))

%% Paso 13

% A REALIZAR POR LOS ESTUDIANTES. Entregar código Matlab y discusión

% Realiza un estudio de cómo evoluciona el número de bits por símbolo 
% cuando generamos 10^i, i=1,2,3,4,5,6 símbolos siguiendo el proceso del 
% paso 11 con probabilidades pr(1)=0.1 y pr(2)=0.9.  Para cada uno de los 
% 6 casos,  realiza 5 simulaciones distintas y calcula el número medio de 
% bits por símbolo como una media de las 5 simulaciones. Dibuja los 30 
% valores obtenidos así como las medias de los 5 valores para las 10,100,
% 1000,10000, 100000 y 1000000 simulaciones. Dibuja también una línea con el valor
% de la entropía de la fuente. ¿Obtienes algún resultado que en principio
% parezca incorrecto entre la entropía de la fuente y los bits por símbolo?.
% ¿Cuál sería la explicación?

% Incluye el código en el paso 13 del fichero Practica03ApellidoNombre.m 
% y la discusión en el paso 13 de  Practica03ApellidoNombre.pdf.
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

% A REALIZAR POR LOS ESTUDIANTES. Entregar código Matlab y discusión

%Como habrás podido comprobar empíricamente, la codificación aritmética es 
%más eficiente cuanto mayor sea la longitud de la secuencia a codificar, 
%es decir, el número medio de bits necesarios para representar cada símbolo 
%se acerca más a la entropía cuantos más caracteres codificamos. 
%Comprobaremos de nuevo empíricamente este hecho usando los ficheros de 
%texto contenidos en el fichero textobinario.zip. 

% Los ficheros de texto en textobinario.zip contienen sólo dos caracteres, 
% el carácter '0' y el carácter '1'. El nombre de cada fichero es textoX.txt 
% donde X representa el número de caracteres en el fichero. Observa que 
% los caracteres ‘0’ y ‘1’ vas a tener que codificarlos como 1 y 2.

%Incluye en el paso 14 de Practica03ApellidoNombre.m el código para 
%   1.	codificar y decodificar cada uno de estos ficheros, 
%   2.	comprobar que la secuencia original y decodificada coinciden,
%   3.	dibujar los histograma de los símbolos en cada fichero. 

% Incluye los histograma, la tabla que contiene el número de bits por símbolo 
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
   fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
   isequal(new_words,indseqdec));
end


%% Paso 15

% A REALIZAR POR LOS ESTUDIANTES. Entregar código Matlab y discusión

% Utiliza codificación aritmética para codificar cada uno de ficheros de 
%texto constitucion española.txt, Fundacion e Imperio - Isaac Asimov.txt 
% y Cinco semanas en globo - Julio Verne.txt 
% (dentro de Prácticas -  Datos - texto.zip). 

%Incluye en el paso 15 de Practica03ApellidoNombre.m el código para 
%1.	codificar y decodificar cada uno de estos ficheros, 
%2.	comprobar que la secuencia original y decodificada coinciden,
%3.	dibujar los histogramas de los símbolos en cada fichero,
%4.	calcular el factor de compresión obtenida para cada uno de los ficheros,
%5.	calcular el número de bits por símbolo para cada fichero.

%En el paso 15 de  Practica03ApellidoNombre.pdf incluye 
%1.	los histogramas, 
%2.	completa las tablas adjuntas, para la codificación Huffman no incluyas 
%   el tamaño de la cabecera y
%3.	realiza una comparación crítica de los resultados obtenidos usando 
%   codificación Huffman y aritmética
clear all; close all; clc;
for fichero = ["constitucion española.txt" "FUNDACION E IMPERIO - Isaac Asimov.txt" "Cinco semanas en globo - Julio Verne.txt"]

    %Abrir y leer el fichero
    fprintf("Fichero: %s\n", fichero);
    f = fopen(fichero, 'r');
    [words count] = fread(f, inf, '*uint8');
    fclose(f);
    
    histograma = histc(words, [1:256]);
    idx = find(histograma > 0); %Elementos que aparecen más de una vez
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
    
    %Compresión aritmética
    code = arithenco(new_words, histograma);
    fprintf('Tamaño fichero original %d\n', count);
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/count);
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/count;
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la señal
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/count);
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
     isequal(new_words,uint8(deco)))
 
end





%% Paso 16

% A REALIZAR POR LOS ESTUDIANTES. Entregar código Matlab y discusión

% Utiliza codificación aritmética sobre los ficheros de imágenes  
% ptt1.pbm, ptt4.pbm, ptt8.pbm (dentro de material complementario 
% - Datos para prácticas - imgs_binarias.zip) y camera.pgm, bird.pgm y 
% bridge.pgm (dentro de Prácticas -  Datos - imgs_grises.zip).  

%Incluye en el paso 16 de Practica03ApellidoNombre.m el código para 
%1.	codificar y decodificar cada uno de estos ficheros, 
%2.	comprobar que la secuencia original y decodificada coinciden,
%3.	dibujar los histogramas de los símbolos en cada fichero,
%4.	calcular el factor de compresión obtenida para cada uno de los ficheros,
%5.	calcular el número de bits por símbolo para cada fichero.%

%En el paso 16 de  Practica03ApellidoNombre.pdf incluye 
%1.	los histogramas, 
%2.	completa las tablas adjuntas, para la codificación Huffman no incluyas el tamaño de la cabecera y
%3.	realiza una comparación crítica de los resultados obtenidos  usando codificación Huffman y aritmética

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
    
    idx = find(histograma > 0); %Elementos que aparecen más de una vez
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
    
    
    %Compresión aritmética
    code = arithenco(new_words, histograma);
    fprintf('Tamaño fichero original %d\n', length(words));
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/length(words));
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    prob_letras_usadas = [];
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/length(words);
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la señal
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/length(words));
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,uint8(deco)))

 
end

for fichero = ["camera.pgm" "bird.pgm" "bridge.pgm"]
    
    %Abrir y leer el fichero
    fprintf("Fichero: %s\n", fichero);
    f = fopen(fichero, 'r');
    [words count] = fread(f, inf, '*uint8');
    fclose(f);
    
    histograma = histc(words, [0:255]);
    idx = find(histograma > 0); %Elementos que aparecen más de una vez
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
    
    
    %Compresión aritmética
    code = arithenco(new_words, histograma);
    fprintf('Tamaño fichero original %d\n', count);
    fprintf('Longitud de la secuencia codificada %d\n',numel(code));
    fprintf('Cantidad de bits por simbolo %d\n',numel(code)/count);
    indseqdec=arithdeco(code,histograma,numel(new_words));
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,indseqdec))

    %Compresion Huffman
    fprintf("HUFFMAN\n");
    prob_letras_usadas = [];
    for i = 1:numel(alfabeto)
        prob_letras_usadas(i) = histograma(i)/count;
    end
    
    [dict,avglen] = huffmandict(alfabeto,prob_letras_usadas) ; %construimos el diccionario
    seq_codificada = huffmanenco(new_words,dict); %codificamos la señal
    deco=huffmandeco(seq_codificada,dict);
    fprintf('Longitud de la secuencia codificada %d\n',numel(seq_codificada));
    fprintf('Cantidad de bits por simbolo %d\n',numel(seq_codificada)/count);
    fprintf('¿Coinciden original y comprimido 1(S) 0 (N)?, %d\n',...
    isequal(new_words,deco));
end
%% Paso 17

% A REALIZAR POR LOS ESTUDIANTES. Discusión en pdf

% No hemos discutido en clase qué cabecera debemos incluir en el fichero 
% codificado para que el decodificador sea capaz de reconstruir el fichero
% original. Suponiendo que, como mucho, las letras del alfabeto son 256,  
% ¿que cabecera incluirías?. No olvides incluir las frecuencias o 
% probabilidades si lo consideras necesario. Podemos incluir la longitud 
% de la secuencia a decodificar, ¿habría alguna forma de no tener que 
% incluir el número de símbolos a decodificar?.

% Incluye la discusión en el paso 17 de  Practica03ApellidoNombre.pdf.


