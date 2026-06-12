function [Y]=CN(T,T0,N,eta)
    a = -1;
    c = -1;
    d = 2/eta + 2;
    M = diag(d*ones(1,N-2)) + diag(c*ones(1,N-3), 1) + diag(a*ones(1,N-3),-1);
    V = T;
    V(2:N-1) = V(3:N) + V(1:N-2);
    B = ones(N-2, 1)*0;
    B(1:N-2) = (2/eta - 2)*T(2:N-1) + V(2:N-1);
    B(1) = B(1) + T0;
    B(N-2) = B(N-2) + T0;
    Y = inv(M) * B;
end