%% Practica04MolinaRafael
% Cambia el nombre del guión a Practica04tuapellidonombre

% Jorge Gangoso Klock
% Tiempo: 12 Horas

%% Paso 1. Entregar discusión en pdf

% Al observar las curvas anteriores surge una pregunta, ¿es posible que 
% las líneas roja y verde de la segunda figura y la roja de la primera ç
% no sean cóncavas?. ¿Si es posible, qué indican?. Escribe y justifica 
% tu respuesta en el paso 1 de Practica04ApellidoNombre.pdf.

%% Paso 2. Escribir código aquí

% En el paso 2 de Practica04ApellidoNombre.m escribe código Matlab para:
% •	leer la imagen sin comprimir bird.pgm, 
% •	salvar la imagen bird.pgm  usando JPEG variando el factor de calidad 
%   desde 5 a 100 en pasos de 5 (ver manual de imwrite). Llama a las imágenes
%   comprimidas birdx.jpeg con x=5,10,15,20,… 100. 
% •	mostrar en una ventana las 20 imágenes obtenidas.
clear all; close all; clc; 
for x = [5:5:100]
    imagen = imread("bird.pgm");
    nombre = "bird"+x+".jpeg";
    imwrite(imagen, nombre, 'Quality', x);
    imagen_comprimida = imread(nombre);
    subplot(4,5,x/5), imshow(imagen_comprimida);
end

%% Paso 3. Respuesta en pdf

% Incluye en el paso 3 de Practica04ApellidoNombre.pdf la ventana que 
% contiene las 20 imágenes. Examínalas con detenimiento y comenta 
% brevemente su calidad.

%% Paso 4. Incluye código en Matlab

%En el paso 4 de Practica04ApellidoNombre.m escribe código Matlab para:

%1)	calcular el espacio que ocupa en bits cada 8 bits del fichero original 
%   para cada fichero comprimido birdx.jpeg con x? {5,10,15,…,100}. 
%   Es decir, calcula la tasa.
%2) calcular la distorsión como error cuadrático medio entre las imágenes 
%   en bird.pgm y birdx.jpeg, x=5, 10, 15, 20,…,100.
%3) representar los puntos tasa/distorsión obtenidos.

%Te será de utilidad la función dir.
clear all; close all; clc;

MyFileInfo = dir("bird.pgm");
tam_original = MyFileInfo.bytes;
img_original = imread("bird.pgm");
tasas = [];
distorsiones = [];
for x = [5:5:100]
    nombre = "bird"+x+".jpeg";
    %Calcular la tasa
    MyFileInfo = dir(nombre);
    tam_actual = MyFileInfo.bytes;
    relacion = tam_original/tam_actual;
    tasa = 8/relacion;
    tasas = [tasas tasa];
    fprintf("Tamaño original (bytes): %i. Tamaño comprimido %s (bytes): %i. Tasa: %d bits\n", tam_original, nombre, tam_actual, tasa);
    %Calcular el error cuadrático medio
    img_comprimida = imread(nombre);
    diferencia = img_original - img_comprimida;
    diferencia_cuadrada_total = sum(sum(diferencia.^2));
    diferencia_cuadrada_media = diferencia_cuadrada_total / sum(size(img_original));
    distorsiones = [distorsiones diferencia_cuadrada_media];
    fprintf("Distorsión del archivo %s: %d\n",nombre, diferencia_cuadrada_media);
end
scatter(tasas, distorsiones);
hold on;
plot (tasas, distorsiones);
title("Relacion T/D para JPEG");
xlabel("Tasa");
ylabel("Distorsión (Error cuadrático medio)");
hold off;
%% Paso 5. Incluye respuesta en pdf

%   Completa en el paso 5 de Practica04ApellidoNombre.pdf la siguiente tabla e
%   incluye la curva tasa/distorsión que has obtenido en el
%   paso anterior.


%% Paso 6. Incluye código Matlab

% En el paso 6 de Practica04ApellidoNombre.m escribe código Matlab para:
%1) salvar la imagen bird.pgm  usando JPEG2000 variando el factor de 
%   compresión ‘CompressionRatio’ en x? {40, 38, 36, 34, …, 6, 4 ,2}. 
%   Llama a las imágenes comprimidas birdx.jp2 con x? {40, 38, 36, 34, …, 6, 4 ,2}.
%2) mostrar en una ventana las 20 imágenes obtenidas.

clear all; close all; clc; 
for x = [40:-2:2]
    imagen = imread("bird.pgm");
    nombre = "bird"+x+".jp2";
    imwrite(imagen, nombre, 'CompressionRatio', x);
    imagen_comprimida = imread(nombre);
    subplot(4,5,x/2), imshow(imagen_comprimida);
end

 
%% Paso 7. Incluye respuesta en fichero pdf

% Incluye en el paso 7 de Practica04ApellidoNombre.pdf la ventana que 
% contiene las 20 imágenes. Examínalas con detenimiento y comenta 
% brevemente su calidad.

%% Paso 8. Incluye código Matlab

% En el paso 8 de Practica04ApellidoNombre.m escribe código Matlab para:

%1) calcular el espacio que ocupa en bits cada 8 bits del fichero original 
%   para cada fichero comprimido birdx.jp2 con x? {40, 38, 36, 34, …, 6, 4 ,2}. 
%   Es decir, calcula la tasa.
%2) calcular la distorsión como error cuadrático medio entre las imágenes en 
%   bird.pgm y birdx.jp2, x? {40, 38, 36, 34, …, 6, 4 ,2}.
%3) representar los puntos tasa/distorsión obtenidos.

% Te será de utilidad la función dir.
clear all; close all; clc;

MyFileInfo = dir("bird.pgm");
tam_original = MyFileInfo.bytes;
img_original = imread("bird.pgm");
tasas = [];
distorsiones = [];
for x = [40:-2:2]
    nombre = "bird"+x+".jp2";
    %Calcular la tasa
    MyFileInfo = dir(nombre);
    tam_actual = MyFileInfo.bytes;
    relacion = tam_original/tam_actual;
    tasa = 8/relacion;
    tasas = [tasas tasa];
    fprintf("Tamaño original (bytes): %i. Tamaño comprimido %s (bytes): %i. Tasa: %d bits\n", tam_original, nombre, tam_actual, tasa);
    %Calcular el error cuadrático medio
    img_comprimida = imread(nombre);
    diferencia = img_original - img_comprimida;
    diferencia_cuadrada_total = sum(sum(diferencia.^2));
    diferencia_cuadrada_media = diferencia_cuadrada_total / sum(size(img_original));
    distorsiones = [distorsiones diferencia_cuadrada_media];
    fprintf("Distorsión del archivo %s: %d\n",nombre, diferencia_cuadrada_media);
end
scatter(tasas, distorsiones);
hold on;
plot (tasas, distorsiones);
title("Relacion T/D para JPEG2000");
xlabel("Tasa");
ylabel("Distorsión (Error cuadrático medio)");
hold off;

%% Paso 9. Incluye respuesta en pdf

%   Completa en el paso 9 de Practica04ApellidoNombre.pdf la siguiente tabla 
%   e incluye la curva tasa/distorsión que has obtenido en el paso
%   anterior.

%% Paso 10. Incluye respuesta en pdf

%   En el paso 10 de Practica04ApellidoNombre.pdf, representa en un mismo 
%   gráfico las dos curvas obtenidas en los pasos 5 y 9 y analízalas. Completa 
%   la tabla adjunta

%% Paso 11. Incluye tus respuestas en pdf

% En el paso 11 de Practica04ApellidoNombre.pdf:
%•	muestra las figuras bird10.jpeg y bird34.jp2,
%•	incluye sus tasas y distorsiones,
%•	comenta y compara la calidad de ambas imágenes.
clear all; close all; clc;

imshow("bird34.jp2");
title("bird34.jp2");
figure;
imshow("bird10.jpeg");
title("bird10.jpeg");
%% Paso 12

% En el paso 12 de Practica04ApellidoNombre.pdf:
%•	muestra las figuras bird90.jpeg y bird6.jp2,
%•	incluye sus tasas y distorsiones,
%•	comenta y compara la calidad de ambas imágenes.
clear all; close all; clc;

imshow("bird6.jp2");
title("bird6.jp2");
figure;
imshow("bird90.jpeg");
title("bird90.jpeg");






