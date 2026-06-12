%Corda Vibrante 2D
clc
close all;
clear all;
%---------------------------------------------------
%Parametri fisici
n = 1000;
L = 10;
x = linspace(0,L,n);

dx = x(2)-x(1);
c = 0.3+0.7*x/L; %corda con densità variabile
%c = 1;

dt = 0.01;
rho = c.^2./(dx^2/dt^2);
fprintf('rho = %f\n',rho);

%psi = sin(x/L*2*pi);
psi = normpdf(x,L/2,L/40);
psiold = psi;
psi(2:n-1) = psi(2:n-1) + (rho(2:n-1).^2/2).*(psi(3:n)+psi(1:n-2)-2*psi(2:n-1));

for i = 1:5000
    psitemp = psi;
    psi(2:n-1) = 2*psi(2:n-1)-psiold(2:n-1)+(rho(2:n-1).^2).*(psi(3:n)+psi(1:n-2)-2*psi(2:n-1));
    psiold = psitemp;
    plot(x,psi);
    ylim([-1.5,1.5]);
%Evoluzione
drawnow limitrate nocallbacks;
end