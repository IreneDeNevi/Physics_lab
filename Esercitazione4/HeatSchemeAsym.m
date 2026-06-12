function HeatSchemeAsym
    close all
    clear
    clc
    % Parametri fisici
    eta = 0.2; 
    L = 0.5; 
    kappa = 10;
    N = 101; 
    x = linspace(0.0,L,N);
    dx = x(2)-x(1); 
    dt = (eta*dx^2)/kappa;
    % Impulso di calore iniziale
    T0 = 20; 
    DeltaT = 80;
    T = ones(N,1)*T0;
    T(1:2) = T(1:2) + DeltaT;
    % Evoluzione
    t = 0; 
    tend = 1e-3; 
    % Temperatura in un punto
    P = 25;
    t2 = [];
    T2 = []; 
    while t<tend
       subplot(2,1,1);
       plot(x,T);
       T(N) = T0;
       T_left = T(2);
       % Metodo esplicito
       T(1) = T(1) + eta * (T(2) + T_left - 2*T(1));
       T(2:N-1) = T(2:N-1) + eta * (T(3:N) + T(1:N-2) - 2*T(2:N-1));
       % Temperatura in un punto P della sbarra al variare del tempo
       subplot(2,1,2);
       plot(t2,T2);
       t2(end+1) = t;
       T2(end+1) = T(P);
       % Disegno
       drawnow limitrate; 
       t = t+dt;
    end
    hold off;
end
