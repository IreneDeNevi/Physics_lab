function y = CN(T,eta,N)
a = -1;
c = -1;
d = (2./eta)+2;
eta = 0.2;
b = ones(N-2,1);  %vettore delle temperature note (sino all'istante N) N-2 perchè sto termostatando la zona centrale
for i=2:N-1        
    b(i-1) = T(i-1)+(2/eta-2)*T(i)+T(i+1);   
end
b(1) = b(1)+T(1);      
b(N-2) = b(N-2)+T(N);

M = diag(a.*ones(1,N-3),1)+diag(d.*ones(1,N-2))+diag(c.*ones(1,N-3),-1);   
M = inv(M);

y = M*b