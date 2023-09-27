function e = entropiaJGK(histograma)
%Entropía JGK calcula la entropía a partir de un histograma
%La entropía calculada se devuelve en e


prob = histograma/sum(histograma); %Dividimos cada fila (símbolo) del histograma por la cantidad total de elementos para tener la probabilidad de cada símbolo
e = sum(-prob(find(prob)).*log2(prob(find(prob)))); %E= -sum(P(x)*log(P(x))

