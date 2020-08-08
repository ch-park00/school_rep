%%
function [phi theta psi]=EulerEKF(z,rates,dt)

persistent H Q R
persistent x P
persistent firstrun
if isempty(firstrun)
    H=[1 0 0;0 1 0];
    Q=[0.0001 0 0;0 0.0001 0;0 0 0.1];
    R=[6 0;0 6];
    x=[0 0 0]';
    P=10*eye(3);
    
    firstrun=1;
end

A=Ajacob_(x,rates,dt);
xp=fx(x,rates,dt);
Pp=A*P*A'+Q;
K=Pp*H'*inv(H*Pp*H'+R);

x=xp+K*(z-H*xp);
P=Pp-K*H*Pp;

phi=x(1);
theta=x(2);
psi=x(3);
