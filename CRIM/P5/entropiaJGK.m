function e = entropiaJGK(histograma)
%Entrop�a JGK calcula la entrop�a a partir de un histograma
%La entrop�a calculada se devuelve en e


prob = histograma/sum(histograma); %Dividimos cada fila (s�mbolo) del histograma por la cantidad total de elementos para tener la probabilidad de cada s�mbolo
e = sum(-prob(find(prob)).*log2(prob(find(prob)))); %E= -sum(P(x)*log(P(x))

