%%
clear all;

dt=0.05;
t=0:dt:20;
Nsamples=length(t);

Xsaved=zeros(Nsamples,3);
Zsaved=zeros(Nsamples,1);

for k=1:Nsamples
    r=GetRadar(dt);
    [pos vel alt]=RadarUKF(r,dt);
    
    Xsaved(k,:)=[pos vel alt];
    Zsaved(k)=r;
end
PosSaved=Xsaved(:,1);
VelSaved=Xsaved(:,2);
AltSaved=Xsaved(:,3);
t=0:dt:(Nsamples-1)*dt;

figure;
plot(t,Xsaved(:,2));
xlabel('Time [sec]');
ylabel('Velocity [m/s]');

figure;
plot(t,Xsaved(:,3));
xlabel('Time [sec]');
ylabel('Altitude [m]');

figure;
plot(t,Xsaved(:,1));
xlabel('Time [sec]');
ylabel('Position [m/s]');

%%
clear all;
Nsamples=41500;
EulerSaved=zeros(Nsamples,3);
Eulersaved1=zeros(Nsamples,3);
dt=0.01;

for k=1:Nsamples
    [p q r]=Getgyro();
    [ax ay az]=GetAccel();
    A=eye(4)+dt*1/2*[0 -p -q -r;p 0 r -q;q -r 0 p;r q -p 0;];
    [phi_a theta_a]=EulerAccel(ax,ay);
    [phi theta psi]=EulerUKF([phi_a theta_a]',[p q r],dt);
    
    [phi1 theta1 psi1]=EulerEKF([phi_a theta_a]',[p q r],dt);
    
    EulerSaved(k,:)=[phi theta psi];
    EulerSaved1(k,:)=[phi1 theta1 psi1];
end
t=0:dt:(Nsamples-1)*dt;

figure;
plot(t,EulerSaved(:,1)*180/pi);hold on;
plot(t,EulerSaved1(:,1)*180/pi);
xlabel('Time [sec]');
ylabel('Roll angle [deg]');

figure;
plot(t,EulerSaved(:,2)*180/pi);hold on;
plot(t,EulerSaved1(:,2)*180/pi);
xlabel('Time [sec]');
ylabel('Pitch angle [deg]');

figure;
plot(t,EulerSaved(:,3)*180/pi);hold on;
plot(t,EulerSaved1(:,3)*180/pi);
xlabel('Time [sec]');
ylabel('Yaw angle [deg]');

%% Free falling body state estimate
clc;clear;close all;

rho=2;
g=32.2;
gam=20000;
Ts=0.5;
var_nu=1e4;
var_w=0;
R=var_nu;
a=1e5;
M=1e5;
x=[3e5 -2e4 0.001]';
n=length(x);
Q=zeros(n);
xh=x;
P=diag([1e6 4e6 10]);
z=0;

%% UKF
for k=2:60
    %%Time update
    Xi=sigmapoints2(xh(:,k-1),P(:,:,k-1));
    xp = zeros(3,1);
    Pp=Q;
    for m=1:2*n
        xx = Xi(:,m);
        for kk=1:501
            xx=fx1(xx,Ts/500,gam,g,rho);
        end
        fXi(:,m)=xx;
        xp = xp+fXi(:,m)/2/n;
    end
    
    for m=1:2*n
        error = fXi(:,m)-xp;
        Pp=Pp + error*error'/2/n;
    end
    Pp = (Pp + Pp')/2;
    
    %System Evolution
    xx = x(:,k-1);
    
    for kk=1:501
        xx = fx1(xx,Ts/500,gam,g,rho);
    end
    x(:,k) = xx;
    
    x_sigma_prior = sigmapoints2(xp,Pp);
    zp = 0;
    for m=1:2*n
        hXi(m) = take_measurement(x_sigma_prior(1,m),a,M,0);
        zp = zp+hXi(m)/2/n;
    end
    Pz = R;
    Pxz = zeros(n,1);
    
    for m=1:2*n
        Pz = Pz + (hXi(m) - zp)*(hXi(m) - zp)'/2/n;
        Pxz = Pxz + (fXi(:,m) - xp)*(hXi(m) - zp)'/2/n;
    end
    
    Pz = (Pz + Pz')/2;
    K = Pxz*inv(Pz);
    
    z(k) = take_measurement(x(1,k),a,M,R);
    
    xh(:,k) = xp+K*(z(k)-zp);
    P(:,:,k) = Pp-K*Pz*K';
    P(:,:,k)=(P(:,:,k) + P(:,:,k)')/2;
end

time = (1:k)*Ts;

figure(1);
subplot(3,1,1);plot(time,x(1,:),time,xh(1,:),'.');
grid on; ylabel ('position [ft]'); legend ('Position (true)','Position (estimated)');
subplot(3,1,2); plot(time,x(2,:),time,xh(2,:),'.');
grid on; ylabel ('speed [ft/sec]');legend('Speed (true)', 'Speed (estimated)');
subplot(3,1,3);plot(time,x(3,:),time,xh(3,:),'.');
grid on; ylabel('Balistic Parameter');
legend('Balistic Parameter (true)','Balistic Parameter (estimated)');
xlabel('Time [sec]');

figure(2);
subplot(3,1,1);
plot(time,x(1,:) - xh(1,:));
grid on; ylabel('Position Error [ft]');
subplot(3,1,2);
plot(time,x(2,:) - xh(2,:));
grid on; ylabel('Speed Error [ft/sec]');
subplot(3,1,3);
plot(time,x(3,:) - xh(3,:));
grid on; ylabel('Balistic Parameter Error');
xlabel('Time [sec]');