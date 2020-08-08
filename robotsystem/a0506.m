%%
clear all;
Nsamples=41500;
Eulersaved=zeros(Nsamples,3);


KFsaved=zeros(Nsamples,3);
dt=0.01;

for k=1:Nsamples
   [p q r]=Getgyro();
   A=eye(4)+dt*1/2*[0 -p -q -r;p 0 r -q;q -r 0 p;r q -p 0;];
   [ax ay az]=GetAccel();
   
   [phi_a theta_a]=EulerAccel(ax,ay);
   
   [phi theta psi]=EulerEKF([phi_a theta_a]',[p q r],dt);
    z=EulerToQuaternion(phi,theta,0);

   [phi1 theta1 psi1]=EulerKalman(A,z);
   Eulersaved(k,:)=[phi theta psi];
   KFsaved(k,:)=[phi1 theta1 psi1];
end

phisaved=Eulersaved(:,1)*180/pi;
thetasaved=Eulersaved(:,2)*180/pi;
psisaved=Eulersaved(:,3)*180/pi;

t=0:dt:(Nsamples-1)*dt;

figure(1);plot(t,phisaved);xlabel('Time [sec]');ylabel('Roll angle [deg]');

figure(2);plot(t,thetasaved);xlabel('Time [sec]');ylabel('Pitch angle [deg]');

figure(3);hold on;plot(t,psisaved);plot(t,KFsaved(:,3)*180/pi);xlabel('Time [sec]');ylabel('Yaw angle [deg]');