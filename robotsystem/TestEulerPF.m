%%
clear all;
dt=0.05;
t=0:dt:20;

Nsamples=length(t);

Xsaved=zeros(Nsamples,3);
X1saved=zeros(Nsamples,3);
X2saved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    % 측정값 측정
    r=GetRadar(dt);
    % 파티클 필터 추정값 계산
    [pos,vel,alt]=RadarPF(r,dt);
    % UKF 추정값 계산
    [pos1,vel1,alt1]=RadarUKF(r,dt);
    % EKF 추정값 계산
    [pos2,vel2,alt2]=RadarEKF(r,dt);
    % 앞서 계산된 추정값 저장
    Xsaved(k,:)=[pos vel alt];
    X1saved(k,:)=[pos1 vel1 alt1];
    X2saved(k,:)=[pos2 vel2 alt2];
    % 측정값 저장
    Zsaved(k)=r;
end

t=0:dt:(Nsamples-1)*dt;
% 시간 변화에 따른 속도 변화 그래프 plot
figure(1);
plot(t,Xsaved(:,2),'b');hold on;
plot(t,X1saved(:,2),'r');
plot(t,X2saved(:,2),'k');
legend('particle filter','UKF','EKF','location','northwest');
%legend('particle filter','UKF');
xlabel('Time [sec]');ylabel('Velocity [m/s]');
title('R change');

% 시간 변화에 따른 고도값 변화 그래프 plot
figure(2);
plot(t,Xsaved(:,3),'b');hold on;
plot(t,X1saved(:,3),'r');
plot(t,X2saved(:,3),'k');
%legend('particle filter','UKF');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Altitude [m]');
title('R change');

% 시간 변화에 따른 위치값 변화 그래프 plot
figure(3);
plot(t,Xsaved(:,1),'b');hold on;
plot(t,X1saved(:,1),'r');
plot(t,X2saved(:,1),'k');
%legend('particle filter','UKF');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Position [m]');
title('R change');

%%
clear all;
dt=0.05;
t=0:dt:20;

Nsamples=length(t);

Xsaved=zeros(Nsamples,3);
X1saved=zeros(Nsamples,3);
X2saved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);
for k=1:Nsamples
    % 측정값 측정
    r=GetRadar(dt);
    % 파티클 필터 추정값 계산
    [pos,vel,alt]=RadarPF(r,dt);
    % UKF 추정값 계산
    [pos1,vel1,alt1]=RadarUKF(r,dt);
    % EKF 추정값 계산
    [pos2,vel2,alt2]=RadarEKF(r,dt);
    % 앞서 계산된 추정값 저장
    Xsaved(k,:)=[pos vel alt];
    X1saved(k,:)=[pos1 vel1 alt1];
    X2saved(k,:)=[pos2 vel2 alt2];
    % 측정값 저장
    Zsaved(k)=r;
end

t=0:dt:(Nsamples-1)*dt;
%시간 변화에 따른 속도 변화 그래프 plot
figure(7);
plot(t,Xsaved(:,2));hold on;
plot(t,X1saved(:,2),'r');
plot(t,X2saved(:,2),'k');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Velocity [m/s]');
title('[0 150 1500]');
% %시간 변화에 따른 고도값 변화 그래프 plot
figure(8);
plot(t,Xsaved(:,3));hold on;
plot(t,X1saved(:,3),'r');
plot(t,X2saved(:,3),'k');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Altitude [m]');
title('[0 150 1500]');
% title('particle=1000');
% 
% %시간 변화에 따른 위치값 변화 그래프 plot
figure(9);
plot(t,Xsaved(:,1));hold on;
plot(t,X1saved(:,1),'r');
plot(t,X2saved(:,1),'k');
% %legend('particle filter','UKF');
% legend('10','100','10000');
legend('particle filter','UKF','EKF','location','northwest');
xlabel('Time [sec]');ylabel('Position [m]');
title('[0 150 1500]');