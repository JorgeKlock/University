%% Practica05GangosoJorge

% Jorge Gangoso Klock
% Tiempo: 20 horas

%% Paso 1


X=[0:255];
for i=0:8
  factor=2^i;
  Q_X=uint8(floor(factor*(floor(X/factor)+0.5)));          
  subplot(3,3,i+1)
  plot(X,Q_X); axis('tight');
  title(['factor de cuantificación ',num2str(factor)])
end




%% Paso 2

% A REALIZAR POR LOS ESTUDIANTES. Código de Matlab aquí

% A continuación aplicaremos estos cuantificadores a la imagen bridge.pgm. 
% Escribe en el paso 2 de Practica05ApellidoNombre.m código de Matlab que:
%1.	lea la imagen bridge.pgm en la matriz a, la convierta a double y la 
%   almacene en adouble
%2.	calcule y guarde en un vector de 9 componentes la entropía de las 
%   imágenes cuantificadas utilizando 
%           uint8(floor(factor*(floor(adouble(:)/factor)+0.5)));
%   con los 9 factores, factor=2^i,  i=0:8.
%3.	calcule y guarde, en un vector de 9 componentes, el error cuadrático 
%   medio de cuantificación entre la imagen original y la cuantificada 
%   para los 9 factores y 
%4.	dibuje en una gráfica con dos figuras las entropías obtenidas y la 
%   curva  (factor, error cuadrático medio de cuantificación).
clear all; close all;
A = imread("bridge.pgm");
adouble = double(A);
[fil col] = size(adouble);
entropias = [];
errores = [];
factores = [];
for i = 0:8
    factor = 2.^i;
    factores = [factores factor];
    a_cuantified = uint8(floor(factor*(floor(adouble(:)/factor)+0.5)));
    hist = histc(a_cuantified,[0:256]);
    
    entropias = [entropias entropiaJGK(hist)];
    
    a_cuantified = reshape(a_cuantified, fil, col);
    
    diferencia = adouble - double(a_cuantified);
    diferencia_cuadrada_total = sum(sum(diferencia.^2));
    diferencia_cuadrada_media = diferencia_cuadrada_total / sum(size(adouble));
    errores = [errores diferencia_cuadrada_media];
end

plot(factores, entropias);
xlabel('factor de cuantificación');
ylabel('Entropía');
figure;
plot(factores, errores);
xlabel('factor de cuantificación');
ylabel('Error cuadrático Medio');

%% Paso 3

% A REALIZAR POR LOS ESTUDIANTES. Discusión en pdf

% En el paso 3 de Practica05ApellidoNombre.pdf

%1.	incluye las entropías y los errores cuadráticos medios calculados en 
%   la tabla adjunta. Explica el contenido de la tabla
%2.	incluye las gráficas de la entropía y la curva 
%   (factor, error cuadrático medio de cuantificación).




%% Paso 4

clear all;close all;
A=imread('camera.pgm');
imhist(A)



%% Paso 5

dA=double(A);
frontera_particion =[127];
valores_cuantizados=[63 , 192];
[index,quants]=quantiz(dA(:),frontera_particion,valores_cuantizados); 
dqA=reshape(quants,size(dA));
qA=uint8(dqA);
subplot(1,2,1), imshow(A); title('Imagen Original')
subplot(1,2,2), imshow(qA); title('Cuantificación uniforme con dos niveles')
error=(dA-dqA).*(dA-dqA);
qerror=sum(error(:))/numel(error);
fprintf('Error cuadrático medio de cuantificación %e\n',qerror);



%% Paso 6

[particion, vcuantizada,qerror] = lloyds(dA(:),2);
[index,quants]=quantiz(dA(:),particion,vcuantizada); 
qA=uint8(reshape(quants,size(A)));
subplot(1,2,1), imshow(A); title('Imagen Original')
subplot(1,2,2), imshow(qA); title('Cuantificación Max-Lloyd con dos niveles')
formatspc='Partición= %4.2f; V. cuantizadas =%4.2f, %4.2f; Error =%4.2f.\n';
fprintf(formatspc,particion,vcuantizada(1),vcuantizada(2),qerror)


%% Paso 7

close all; clear all;
rng('default')
X=2*rand(1000,1)-1; %entiende este paso
hist(X); title('Histograma 1000 realizaciones U(-1,1)')

%% Paso 8

var=sum((X-mean(X)).*(X-mean(X)))/numel(X)

%% Paso 9

% A REALIZAR POR LOS ESTUDIANTES. código de Matlab.

% Volvamos al histograma. Éste nos indica que nuestras observaciones son 
% candidatas a ser cuantificadas utilizando un cuantificador uniforme. 
% Escribe en el paso 9 de Practica05ApellidoNombre.m  código Matlab para:
%1.	Construir un cuantificador uniforme con 2n valores cuantificados con 
%   n=1,2,3,4,5,6,7,8.
%2.	Calcular en función de n, el error cuadrático medio de cuantificación 
%   sobre los datos en X y también su error cuadrático medio de cuantificación teórico. 
%3.	Dibujar, en función de n, las dos curvas de errores obtenidas. Dos subfiguras
%   distintas en una misma figura.
%
%La función linspace de Matlab, con valor inicial -1 y final 1,  
%puede ser útil para este ejercicio.

%n_valores = 2,4,8,16,32,64
errores = [];
errores_teoricos = [];
for n=[1:8]
    
    valores_cuantificados = 2.^n;
    
    %Tomamos valores_cuantificados - 1 fronteras de entre esos puntos
    %equidistantes
    %COMO CALCULAR LAS FRONTERAS DE FORMA MANUAL
%             n_fronteras = valores_cuantificados - 1;
%             fronteras_particion = [];
%             for i = [1:n_fronteras]
%                 fronteras_particion = [fronteras_particion i*(2/valores_cuantificados)];
%             end
%             fronteras = [0 fronteras_particion 2];
%             fronteras = fronteras - 1;
%             fronteras_particion = fronteras_particion - 1;
    %Los valores devueltos de cuantificacion serán los puntos medios entre
    %fronteras
    
    fronteras = linspace(-1,1,valores_cuantificados+1);
    fronteras_particion = fronteras(2:end-1);
    
    
    valores_cuantizados = [];
    for j = [1:numel(fronteras)-1]
        valores_cuantizados = [valores_cuantizados (fronteras(j)+fronteras(j+1))/2];
    end
    
    [index, quants] = quantiz(X(:), fronteras_particion, valores_cuantizados);
    x_q = reshape(quants, size(X(:)));
    
    err = ((X-x_q).*(X-x_q));
    err = sum(err)/numel(X);
    errores = [errores err];
    tamanio_intervalo = 2/valores_cuantificados;
    err_teorico = (tamanio_intervalo.^2)/12;
    errores_teoricos = [errores_teoricos err_teorico];
    fprintf("Error cuadrático empírico de la iteracion %i: %d\n", n, err);
    fprintf("Error Teórico de la iteración %i: %d\n", n, err_teorico);
end

subplot(1,2,1);
plot([1:8], errores);
legend('Error Empírico');
subplot(1,2,2);
plot([1:8], errores_teoricos, 'red');
legend('Error Teórico');
% subplot(1,3,1);
% plot([1:8], errores);
% legend('Error Empírico');
% subplot(1,3,2);
% plot([1:8], errores_teoricos, 'red');
% legend('Error Teórico');
% subplot(1,3,3);
% plot([1:8], errores);
% hold on;
% plot([1:8], errores_teoricos);
% legend('Error Empirico', 'Error Teórico');
% hold off;

%% Paso 10

% A REALIZAR POR LOS ESTUDIANTES. incluye discusión en pdf

% En el paso 10 de Practica05ApellidoNombre.pdf:
%1.	Completa la tabla adjunta que contiene el error cuadrático medio 
%   calculado y el teórico. Utiliza 5 decimales.
%2.	Incluye las dos curvas obtenidas correspondientes al error cuadrático 
%   medio calculado y al teórico.
%3.	Discute y explica además qué ocurre cuando aumentamos n en el paso anterior. 
%4.	Por último, indica cómo deberíamos codificar los índices de 
%   cuantificación: Huffman, aritmética o longitud fija.


%% Paso 11

close all; clear all; rng('default');
X=laprnd(1000,1,0,sqrt(1/30));
X=X(X>=-1 & X<=1);
hist(X); title('Histograma 2000 realizaciones Laplace(0,1/30)')



%% Paso 12

% A REALIZAR POR LOS ESTUDIANTES. código de Matlab.

% Como puedes observar el histograma no es muy uniforme. Esto nos indica 
% que nuestras observaciones no son candidatas a ser cuantificadas utilizando
% un cuantificador uniforme. No obstante, escribe en el paso 12 de 
% Practica05ApellidoNombre.m código Matlab para:
%1.	construir un cuantificador uniforme con 2n , n=1,2,3,4,5,6,7,8, niveles
%   de cuantificación en el intervalo (-1,1) y aplicarselo a estos datos en X, 
%2.	calcular, en función de n, el error cuadrático medio de cuantificación 
%   sobre los datos en X,
%3.	dibujar, en función de n, la curva de errores obtenida. 

errores = [];
for n=[1:8]
    
    valores_cuantificados = 2.^n;
    fronteras = linspace(-1,1,valores_cuantificados+1);
    fronteras_particion = fronteras(2:end-1);
    
    
    valores_cuantizados = [];
    for j = [1:numel(fronteras)-1]
        valores_cuantizados = [valores_cuantizados (fronteras(j)+fronteras(j+1))/2];
    end
    
    [index, quants] = quantiz(X(:), fronteras_particion, valores_cuantizados);
    x_q = reshape(quants, size(X(:)));
    
    err = ((X-x_q).*(X-x_q));
    err = sum(err)/numel(X);
    errores = [errores err];
    tamanio_intervalo = 2/valores_cuantificados;
    fprintf("Error cuadrático empírico de la iteracion %i: %d\n", n, err);
end

plot([1:8], errores);
legend('Error Empírico');

%% Paso 13

% A REALIZAR POR LOS ESTUDIANTES. Entrega discusión en pdf.

% En el paso 13 de Practica05ApellidoNombre.pdf 
%1.	Completa la tabla de errores cuadráticos medios. Utiliza cinco decimales 
%2.	Incluye la curva de errores cuadráticos medios obtenidos
%3.	Por último indica cómo deberíamos codificar los índices de 
%   cuantificación: Huffman, aritmética o longitud fija.


%% Paso 14

%Discute y compara las tablas que has incluido en los pasos 10 y 13.

%% Paso 15

% A REALIZAR POR LOS ESTUDIANTES. Entrega código Matlab.

% Escribe en el paso 15 de Practica05ApellidoNombre.m código de Matlab para:
%1.	Construir a partir de los datos observados en X un cuantificador de 
%   Max-Lloyd con: 2n niveles de cuantificación usando la función Lloyd de 
%   Matlab   para n=1,2,3,4,5,6,7,8,
%2.	Calcular los errores de cuantificación
%3.	Dibujar la curva de errores en función de n.
%4.	Incluir en una figura con 8 subfiguras los límites de las particiones 
%   y los valores de cuantificación asignados a cada partición
clc;
errores = [];

for n=[1:8]
    y = [];
    y2 = [];
    valores_cuantificados = 2.^n;
    fronteras = linspace(-1,1,valores_cuantificados+1);
    fronteras_particion = fronteras(2:end-1);
    
    [particion, vcuantizada, qerror] = lloyds(X(:),valores_cuantificados);
    [index,quants]=quantiz(X(:),particion,vcuantizada); 

    x_q = reshape(quants, size(X(:)));

    subplot(4,2,n);
    y(1:numel(particion)) = n;
    y2(1:numel(vcuantizada)) = n;
    scatter(particion, y, '+');
    hold on;
    scatter(vcuantizada, y2, 'filled');
    legend("particiones","vcuantizada");
    hold off;
    
    err = ((X-x_q).*(X-x_q));
    err = sum(err)/numel(X);
    errores = [errores err];
    tamanio_intervalo = 2/valores_cuantificados;
    fprintf("Error cuadrático empírico de la iteracion %i: %d\n", n, err);
end

figure;
plot([1:8], errores);
legend('Error Empírico');



 
%% Paso 16
 
% A REALIZAR POR LOS ESTUDIANTES. Entrega discusión en pdf.

%  En el paso 16 de Practica05ApellidoNombre.pdf
%1.	Completa la tabla de errores cuadráticos medios. Utiliza 5 decimales.
%2.	Incluye la curva de errores cuadráticos medios obtenidos.
%3.	Incluye la figura con 8 subfiguras que dibuja los límites de las 
%   particiones con los valores de cuantificación asignados a cada partición.
%4.	¿Qué conclusiones extraes de la figura?
%5.	Por último, indica cómo deberíamos codificar los índices de 
%   cuantificación: Huffman, aritmética o longitud fija.




%% Paso 17

% A REALIZAR POR LOS ESTUDIANTES. Entrega discusión en pdf.

%  Discute y compara las tablas que has incluido en los pasos 10 , 13 y 16.

%% Paso 18

% A REALIZAR POR LOS ESTUDIANTES. Entrega discusión en pdf.

%Por último, ¿Por qué crees que hemos utilizado la distribución de Laplace?





