M = 100; %dimensione matrice, grande per arrivare dove V tende a zero
V = zeros(M,M); %def matrice griglia con potenziale nullo ovunque 
Q = zeros(M,M); %def matrice griglia con carica (densità di carica) nulla ovunque

%condensatore al centro
Cen = M/2;
W = M/20;

%LAPLACE 
Q(Cen-W:Cen+W,Cen-W) = 10;
Q(Cen-W:Cen+W,Cen+W) = -10;
x = linspace(0,1,M);
d = x(2) - x(1); %spaziatura griglia

figure(1)
%iteriamo il rilassamento

k = 1/(4* 8.85*10e-12 * pi);
t=0;
dt=0.1;
while t<10 %100 cicli
    
    t=t+dt; 
    
    Vold = V; %parto dal valore iniziale
  
    V(2:M-1,2:M-1) = 1/4.*(Vold(3:M,2:M-1)+Vold(1:M-2,2:M-1)+Vold(2:M-1,3:M)+Vold(2:M-1,1:M-2)) + k*Q(2:M-1,2:M-1)*d^2;
    %ovvero V(i,j) = 1/4.*(Vold(i+1,j)+Vold(i-1,j)+Vold(i,j+1)+Vold(i,j-1) + 1/4.q(i,j)*d^2);

    %non sono sicuro perciò non lo metto
    %V(Cen-W:Cen+W,Cen-W) = k*Q(Cen-W:Cen+W,Cen-W);
    %V(Cen-W:Cen+W,Cen+W) = k*Q(Cen-W:Cen+W,Cen+W); %fisso il pot del condensatore, nell'iter lo cambiavo

    surfc(V)
    drawnow %non è necessario, ma voglio vedere per curiosità come evolve la soluzione
    
end

%alla fine anche il campo E
figure(2)
[Ex,Ey] = gradient(V);
y = linspace (0,1,M);
quiver (x,y,-Ex,-Ey)