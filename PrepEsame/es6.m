%  Si risolva il problema di una corda vibrante di lunghezza L = 20 m che all’istante t = 0 ha la
% forma y = sin[π(x/L)]. Gli estremi restano vincolati a y = 0 durante il moto. La velocit`a di propagazione `e
% v = 1 m/s. Si disegni l’andamento del punto centrale (y per x = L/2) in funzione del tempo.
clc
close all;
clear all;
%-------------------------------------------------------------------------%
N = 100;
L = 20;
x= linspace(0,L,N);
dx = x(2)-x(1); %step
v = 1;
k=pi/L;
t=0;
tmax=100;
dt=0.1;
c= v*(dt/dx); %CFL condition
Y=sin(k*x);
Y0=sin(k*x);
Y(1)=0;
Y(N)=0;

%condizione derivata
Y(2:N-1) = Y(2:N-1) + c*c.*(Y(3:N)+Y(1:N-2)-2.*Y(2:N-1));
Y1=Y;

x1=[];
x2=[];
i=0;
while(t<tmax)
    i = i+1;
    Y(2:N-1) = 2.*Y1(2:N-1) - Y0(2:N-1) + c*c.*(Y1(3:N)+Y1(1:N-2)-2.*Y1(2:N-1));
    Y0=Y1;
    Y1=Y;
    Y(1)=0;
    Y(N)=0;
    hold on;
    figure(1);
    ylim([-1 1]);
    plot(x,Y);
    drawnow limitrate;
    x1(i) = t;
    x2(i) = Y(L/2); %punto centrale
    t=t+dt;
end

figure(2);
plot(x1,x2);
hold off;