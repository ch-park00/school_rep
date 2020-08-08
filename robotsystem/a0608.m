%%
clear all;close all;

Nsamples=41500;
EulerSaved=zeros(Nsamples,3);

dt=0.01;

for k=1:Nsamples
    [ax,ay,az]=GetAccel();
    [p,q,r]=Getgyro();
    [phi,theta,psi]=ComFilterWithPI(p,q,r,ax,ay,az,dt);
    EulerSaved(k,:)=[phi,theta,psi];
end

Phisaved=EulerSaved(:,1)*180/pi;
Thetasaved=EulerSaved(:,2)*180/pi;
Psisaved=EulerSaved(:,3)*180/pi;

t=0:dt:(Nsamples-1)*dt;
figure(1);
plot(t,Phisaved);
xlabel('Time [sec]');ylabel('Roll [deg]');
figure(2);
plot(t,Thetasaved);
xlabel('Time [sec]');ylabel('Pithc [deg]');
figure(3);
plot(t,Psisaved);
xlabel('Time [sec]');ylabel('Yaw [deg]');