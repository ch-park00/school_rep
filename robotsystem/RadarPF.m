%%
function [pos,vel,alt]=RadarPF(z,dt)
persistent x
persistent firstrun
persistent pt wt
persistent Npt
if isempty(firstrun)
    % 초기값
    x=[0 90 1100]';
    % 파티클 개수
    Npt=1000;
    % 정규분포를 따르는 잡음을 추가
    pt(1,:)=x(1)+0.1*x(1)*randn(1,Npt);
    pt(2,:)=x(2)+0.1*x(2)*randn(1,Npt);
    pt(3,:)=x(3)+0.1*x(3)*randn(1,Npt);
    wt=ones(1,Npt)*1/Npt;
    firstrun=1;
end
% 모든 파티클들을 시스템 모델에 적용
for k=1:Npt
    pt(:,k)=fx(pt(:,k),dt)+randn(3,1);
end
% 파티클의 가중치 계산.이 가중치는 측정값 z와 비슷할수록 가중치가 커지게 된다.
for k=1:Npt
    wt(k)=wt(k)*normpdf(z,hx(pt(:,k)),10);
end
% 추정값 계산
wt=wt/sum(wt);
x=pt*wt';
pos=x(1);
vel=x(2);
alt=x(3);
% resampling 과정(SIR 알고리즘)
% 기존 모든 가중치의 합을 구함.
wtc=cumsum(wt);
% 0~1 사이 새로운 1000개의 파티클을 무작위로 생성
rpt=rand(Npt,1);
% 각 구간에 맞는 파티클 개수 결정
[~,ind1]=sort([rpt;wtc']);
ind=find(ind1<=Npt)-[0:Npt-1]';
pt=pt(:,ind);
% 가중치 초기화
wt=ones(1,Npt)*1/Npt;
end
function xp=fx(x,dt)
A=eye(3)+dt*[0 1 0;0 0 0;0 0 0];
xp=A*x;
end
function zp=hx(xhat)

x1=xhat(1);
x3=xhat(3);
zp=sqrt(x1^2+x3^2);
end