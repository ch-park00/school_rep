%%
function [pos vel alt]=RadarEKF(z,dt)

persistent A Q R
persistent x P
persistent firstrun

if isempty(firstrun)
    A=eye(3)+dt*[0 1 0;0 0 0;0 0 0];
    Q=[0 0 0;0 0.001 0;0 0 0.001];
    R=10;
    % 속도 초기값을 바꿔가며 테스트해보고 결과 분석=> 초기값이 중요하다는 것을 
    % 보여줘야함..
    x=[0 90 1100]';
    P=10*eye(3);
    firstrun=1;
end
H=zeros(1,3);
x1=x(1);
x3=x(3);
H(1)=x1/sqrt(x1^2+x3^2);
H(3)=x3/sqrt(x1^2+x3^2);

xp=A*x;
Pp=A*P*A'+Q;

K=Pp*H'*inv(H*Pp*H'+R);

x=xp+K*(z-sqrt(xp(1)^2+xp(3)^2));
P=Pp-K*H*Pp;

pos=x(1);vel=x(2);alt=x(3);
