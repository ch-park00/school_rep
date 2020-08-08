%%
dt=0.2;
t=0:dt:10;
Nsamples=length(t);
Xsaved=zeros(Nsamples,1);
X1saved=zeros(Nsamples,1);
X2saved=zeros(Nsamples,1);
Zsaved=zeros(Nsamples,1);
for k=1:Nsamples
    z=GetVolt();
    volt=avgFilter(z);
    volt1=LPF(z);
    volt2=SimpleKalman(z);
    Xsaved(k)=volt;
    X1saved(k)=volt1;
    X2saved(k)=volt2;
    Zsaved(k)=z;
end
% 평균필터
figure(1);
plot(t,Xsaved,'o-');hold on;
plot(t,Zsaved,'r:*');
xlabel('Time (sec)');
ylabel('Voltage (V)');
legend('Average Filter', 'Measurements');
% 1차 저주파 통과필터
figure(2);
plot(t,X1saved,'o-');hold on;
plot(t,Zsaved,'r:*');
xlabel('Time (sec)');
ylabel('Voltage (V)');
legend('LPF', 'Measurements');
% 칼만필터
figure(3);
plot(t,X2saved,'o-');hold on;
plot(t,Zsaved,'r:*');
xlabel('Time (sec)');
ylabel('Voltage (V)');
legend('Kalman Filter', 'Measurements');



%%
clear all;
dt=0.2;
t=0:dt:10;
Nsamples=length(t);
Xsaved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    z=GetVolt();
    [volt Cov Kg]=SimpleKalman2(z);
    
    Xsaved(k,:)=[volt Cov Kg];
    Zsaved(k)=z;
end

figure();
plot(t,Xsaved(:,1),'o-');hold on;
plot(t,Zsaved,'r:*');
xlabel('Time (sec)');
ylabel('Voltage (V)');
legend('Kalman Filter', 'Measurements');
title ('Kalman Filter Output');

figure();
plot(t,Xsaved(:,2),'o-');
xlabel('Time (sec)');
ylabel('P');
title ('Error Covariance');

figure();
plot(t,Xsaved(:,3),'o-');
xlabel('Time (sec)');
ylabel('K');
title ('Kalman gain');