function Esercizio2
    L = 0.5; 
    k = 1; 
    eta = 0.2;
    N = 101;
    x = linspace(0.0, L, N);
    dx = x(2)-x(1);
    dt = (eta*dx*dx)/k;
    T0 = 100.0;
    t = 0;
    T1 = T0/10;
    n = 5000;
    t1 = n*dt;
    tend = 5*n*dt;
    
    T = ones(N,1)*T1; T((N-1)/2 + 1) = T0;
    plot(x,T);
    
    tempo = zeros(2*n,1);
    y = zeros(2*n,1);
    tempo(1) = t;
    y(1) = T(75);
    i = 2;
       
    figure(1)
    while t<t1
        t = t+dt;
        T(1) = T1;
        T(N) = T1;
        
        Y = CN(T, T1, N, eta);
        T(2:N-1) = Y(1:N-2);
        tempo(i) = t;
        y(i) = T(75);
        i = i+1;
        pause(0.01)
        plot(x,T);

    end
    
    while t<tend
        t = t+dt;
        T(1) = T1;
        TRight = T(N-1);
        T(N) = T(N) + eta*(T(N-1) + TRight - 2*T(N));
        T(2:N-1) = T(2:N-1) + eta*(T(3:N) + T(1:N-2) - 2*T(2:N-1));
        tempo(i) = t;
        y(i) = T(75);
        i = i+1;
        pause(0.01)
        plot(x,T);
        
    end
    
    figure(2)
    plot(tempo,y);
    
end