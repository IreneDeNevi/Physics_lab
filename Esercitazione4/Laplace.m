M = 100; %dimensione matrice, grande per arrivare dove V tende a zero
V = zeros(M,M); %def matrice griglia con potenziale nullo

%condensatore al centro
Cen = M/2;
W = M/20;

%Laplace
V(Cen-W:Cen+W,Cen-W) = 100;
V(Cen-W:Cen+W,Cen+W) = -100;

figure(1)

t=0;
dt=0.1;
while t<10 
    
    t=t+dt; 
    
    V0 = V; %parto dal valore iniziale
  
    V(2:M-1,2:M-1) = 1/4.*(V0(3:M,2:M-1)+V0(1:M-2,2:M-1)+V0(2:M-1,3:M)+V0(2:M-1,1:M-2));
    % V(i,j) = 1/4.*(V0(i+1,j)+V0(i-1,j)+V0(i,j+1)+V0(i,j-1));

    V(Cen-W:Cen+W,Cen-W) = 100;
    V(Cen-W:Cen+W,Cen+W) = -100; %fisso il potenziale del condensatore

    surfc(V)
    colorbar
    drawnow limitrate

end

%campo E = -grad(V)
figure(2)
[Ex,Ey] = gradient(V);
x = linspace(0,1,M);
y = linspace (0,1,M);
p = quiver(x,y,-Ex,-Ey,'r'); %tengo conto del segno di E nel plot 
p.ShowArrowHead = 'on';
