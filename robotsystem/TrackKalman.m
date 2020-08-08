%%
function [xh yh]=TrackKalman(xm,ym)

persistent A H Q R
persistent x P
persistent firstRun

if isempty(firstRun)
    dt=1;
    A=[1 dt 0 0
       0 1 0 0
       0 0 1 dt
       0 0 0 1];
    H=[1 0 0 0
       0 0 1 0];
    Q=1.0*eye(4);
    R=[50 0;0 50];
    
    x=[0,0,0,0]';
    P=100*eye(4);
    firstRun=1;
end

% 추정값 예측
xp=A*x;
% 오차 공분산 예측
Pp=A*P*A'+Q;
% 칼만 이득 계산
K=Pp*H'*inv(H*Pp*H'+R);
z=[xm ym]';
% 추정값 계산
x=xp+K*(z-H*xp);
% 오차 공분산 계산
P=Pp-K*H*Pp;
% x 좌표
xh=x(1);
% y 좌표
yh=x(3);