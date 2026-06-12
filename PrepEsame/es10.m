%Eulero-Cromer
clc
close all;
clear all;
%Creazione elementi necessari:
r=zeros(2,1);
v=zeros(2,1);
a=zeros(2,1);
rnew=zeros(2,1);
vnew=zeros(2,1);

 

%Condizioni iniziali:
grid=100;
dt=0.1;
t=0.;
tend=1000*dt;
x=5;
vy=4;
r(1,1)=x;
v(2,1)=vy;
M=100;
G=1;

 

while t<tend
    scatter(r(1,1),r(2,1));
    axis([-grid grid -grid grid]);
    hold on;
    scatter(0,0);
     
    rnew(1:2,1)=r(1:2,1)+v(1:2,1)*dt;
    F=-G*M/(rnew(1,1)^2+rnew(2,1)^2);
    a(1:2,1)=F*(r(1:2,1)/sqrt(r(1,1)^2+r(2,1)^2));
    vnew(1:2,1)=v(1:2,1)+ a(1:2,1)*dt;
    
    r=rnew;
    v=vnew;

 

    drawnow limitrate nocallbacks
    
    t=t+dt;
end
