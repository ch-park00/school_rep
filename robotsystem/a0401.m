%% 
clear all;clc;close all;
dt=0.1;
t=0:dt:10;
Nsamples=length(t);
Xsaved=zeros(Nsamples,2);
Zsaved=zeros(Nsamples,2);

for k=1:Nsamples
    [z vel]=GetPos();
    [pos vel1]=DvKalman(z);
    Xsaved(k,:)=[pos vel1];
    Zsaved(k,:)=[z vel];
end
% 위치 그래프
figure;hold on;
plot(t,Zsaved(:,1),'r.');
plot(t,Xsaved(:,1));xlabel('Time (sec)');
ylabel('position (P)');
legend('measurement', 'kalman filter');
% 속도 그래프
figure;plot(t,Xsaved(:,2));hold on;
plot(t,Zsaved(:,2));xlabel('Time (sec)');
ylabel('Velocity (m/s)');
legend('kalman Filter', 'true speed');

%%
clear all;clc;close all;
dt=0.1;
t=0:dt:10;
Nsamples=length(t);
Xsaved=zeros(Nsamples,2);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    vel=Getvel();
    [pos vel1]=IntKalman(vel);
    Xsaved(k,:)=[pos vel1];
    Zsaved(k)=vel;
end
% 위치 그래프
figure;hold on;
plot(t,Xsaved(:,1));xlabel('Time (sec)');
ylabel('position (P)');
% 속도 그래프
figure;plot(t,Xsaved(:,2));hold on;
plot(t,Zsaved(:),'r.');xlabel('Time (sec)');
ylabel('Velocity (m/s)');
legend('kalman Filter', 'measurement');

%%
clear all;
Nsamples=500;

Xsaved=zeros(Nsamples,2);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    z=GetSonar();
    [pos vel]=DvKalman(z);
    Xsaved(k,:)=[pos vel];
    Zsaved(k)=z;
end

dt=0.02;
t=0:dt:(Nsamples-1)*dt;
% 거리 그래프
figure;hold on;
plot(t,Xsaved(:,1));plot(t,Zsaved(:),'r.');
xlabel('Time (sec)');
ylabel('Distance (m)');
legend('Kalman filter','measurement');
% 속도 그래프
figure;plot(t,Xsaved(:,2),'Linewidth',2);hold on;
plot(t,Zsaved);xlabel('Time (sec)');
ylabel('Velocity (m/s)');
legend('Velocity', 'distance');
