%%
clc;clear all;close all;
% 샘플링 주기
Ts=1/100;
time=3000;
% 시뮬레이션 진행 시간
TFinal=Ts*time;

% 초기값 지정
muWx=0;
muWy=0;
wx=0;
wy=0;
sigWx=1e-7;
sigWy=1e-7;
sigR=1e-1;
sigB=1e-1;
cx=2;
cy=2;
Z=2;
V0=[-0.25;0.25];
P0=[1;1];
M0=0*rand(1,1)*eye(4);
X0=0*rand(4,1)+[P0;V0];
C0=[cx;cy];
%%
% 시뮬레이션 수행
out=sim('vechicle_circular_traversing.slx');
%%
% plot
figure(1)
plot(P(:,1),P(:,2),'-');
hold on;grid on;axis equal;
plot(pxhat,pyhat,'--k');
scatter(cx,cy,250,'fill');
xlim([0 4]);ylim([0 4]);

title('Trajectory Around C');
legend('True','Estimated');
xlabel('x [m]');ylabel('y [m]');

figure(2);plot(t,Rnhat(:,1),'.-');hold on;
plot(t,Rnhat(:,2),'--r');grid minor;
plot(t,Rhat,'--k','Linewidth',2);
legend('True','Observed','Estimated');
xlabel('Time [sec]');ylabel('Range [m]');

figure(3);plot(t,Bnhat(:,1)*180/pi,'.-');hold on;
plot(t,Bnhat(:,2)*180/pi,'--r');grid minor;
plot(t,Azhat*180/pi,'--k','Linewidth',2);
legend('True','Observed','Estimated');
xlabel('Time [sec]');ylabel('Azimuth Angle [deg]');

