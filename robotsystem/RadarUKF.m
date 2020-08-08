%%
function [pos,vel,alt]=RadarUKF(z,dt)
persistent Q R
persistent x P
persistent n m
persistent firstrun
if isempty(firstrun)
    Q=[0.01 0 0;0 0.01 0;0 0 0.01];
    R=10;
    x=[0 90 1100]';
    P=10*eye(3);
    % 보고자 하는 값 = 3개
    n=3;
    m=1;
    firstrun=1;
end
% 시그마 포인트와 가중치 계산
[Xi W]=sigmaPoints(x,P,0);
fXi=zeros(n,2*n+1);
% 추정값과 오차 공분산 계산
for k=1:2*n+1
    fXi(:,k)=fx(Xi(:,k),dt);
end
[xp Pp]=UT(fXi,W,Q);
% 측정값과 오차 공분산 계산
hXi=zeros(m,2*n+1);
for k=1:2*n+1
    hXi(:,k)=hx(fXi(:,k));
end
[zp Pz]=UT(hXi,W,R);
% 칼만 이득 계산
Pxz=zeros(n,m);
for k=1:2*n+1
    Pxz=Pxz+W(k)*(fXi(:,k)-xp)*(hXi(:,k)-zp)';
end
K=Pxz*inv(Pz);
% 추정값 계산
x=xp+K*(z-zp);
% 오차 공분산 계산
P=Pp-K*Pz*K';
pos=x(1);
vel=x(2);
alt=x(3);

function xp=fx(x,dt)
A=eye(3)+dt*[0 1 0;0 0 0;0 0 0];
xp=A*x;

function yp=hx(x)
yp=sqrt(x(1)^2+x(3)^2);

