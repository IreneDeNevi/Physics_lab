function HeatScheme
% Parametri fisici
eta = 0.2; L = 0.5; kappa = 10;
% Delta x, Delta t
N = 101; 
x = linspace(0.0,L,N);
dx = x(2)-x(1); 
dt = (eta*dx^2)/kappa;
% Impulso di calore iniziale
T0 = 20;
DeltaT = 80;
T = ones(N,1)*T0;
T((N-1)/2+1) = T0+DeltaT;
% Evoluzione
t = 0;
tend = 1000*dt;

while t<tend


plot(x,T);

T(N) = T0;
T(1) = T0;
% ... (Cranck-Nicholson o inv. matrice)
T(2:N-1) = CN(T,eta,N);
drawnow limitrate%cercare parametri per rendere meno lenta la visualizzazione
%pause(0.0001);
t = t+dt;
end
hold on
z = sqrt(2*kappa*t); %sigma    

G = @(x) (T0+(DeltaT*dx*(1/(sqrt(2*pi*z.^2)))*exp((-(x-0.25).^2)/(2*z.^2))));
plot(x,G(x));
hold off
end