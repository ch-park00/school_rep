%%
function [pos vel]=DvKalman(z)

persistent A H Q R
persistent x P
persistent firstRun

if isempty(firstRun)
    % 초기값 설정
    firstRun=1;
    dt=0.1;
    A=[1 dt;0 1];
    H=[1 0];
    Q=[1 0;0 3];
    R=10;
    
    x=[0;20];
    P=5*eye(2);
end
% 추정값 예측
xp=A*x;
% 오차 공분산 예측
Pp=A*P*A'+Q;
% 칼만 이득 계산
K=Pp*H'*inv(H*Pp*H'+R);
% 추정값 계산
x=xp+K*(z-H*xp);
% 오차공분산 계산
P=Pp-K*H*Pp;
% 위치
pos=x(1);
% 속도
vel=x(2);