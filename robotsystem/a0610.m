%%
clear all;clc
Nsamples=41500;
dt=0.01;

EulerSaved_comp=zeros(Nsamples,3);
EulerSaved_EKF=zeros(Nsamples,3);
EulerSaved_kalman=zeros(Nsamples,3);

comp_time=0;
EKF_time=0;
kalman_time=0;

for k=1:Nsamples
    [ax,ay,az]=GetAccel();
    [p,q,r]=Getgyro();
    
    comp_start=tic;
    [phi_comp, theta_comp, psi_comp]=ComFilterWithPI(p,q,r,ax,ay,az,dt);
    comp_end=toc(comp_start);
    
    EulerSaved_comp(k,:)=[phi_comp theta_comp psi_comp];
    
    EKF_start=tic;
    [phi_a,theta_a]=EulerAccel(ax,ay);
    [phi_EKF,theta_EKF,psi_EKF]=EulerEKF([phi_a theta_a]',[p q r],dt);
    EKF_end=toc(EKF_start);
    
    EulerSaved_EKF(k,:)=[phi_EKF,theta_EKF,psi_EKF];
    
    kalman_start=tic;
    psi_kalman=0;
    A=eye(4)+dt*1/2*[0 -p -q -r;p 0 r -q;q -r 0 p;r q -p 0];
    [phi_kalman,theta_kalman]=EulerAccel(ax,ay);
    z=EulerToQuaternion(phi_kalman,theta_kalman,0);
    [phi_kalman, theta_kalman,psi_kalman]=EulerKalman(A,z);
    kalman_end=toc(kalman_start);
    
    EulerSaved_kalman(k,:)=[phi_kalman,theta_kalman,psi_kalman];
    
    comp_time=comp_time+comp_end;
    EKF_time=EKF_time+EKF_end;
    kalman_time=kalman_time+kalman_end;
    
end

disp('--Elapsed Time[ms]-----');
disp('--41500 Samples-----');
disp('Complimentary:');
disp(comp_time*1e3);
disp('EKF:');
disp(EKF_time*1e3);
disp('kalman:');
disp(kalman_time*1e3);


PhiSaved_comp=EulerSaved_comp(:,1)*180/pi;
ThetaSaved_comp=EulerSaved_comp(:,2)*180/pi;
PsiSaved_comp=EulerSaved_comp(:,3)*180/pi;

PhiSaved_EKF=EulerSaved_EKF(:,1)*180/pi;
ThetaSaved_EKF=EulerSaved_EKF(:,2)*180/pi;
PsiSaved_EKF=EulerSaved_EKF(:,3)*180/pi;

PhiSaved_kalman=EulerSaved_kalman(:,1)*180/pi;
ThetaSaved_kalman=EulerSaved_kalman(:,2)*180/pi;
PsiSaved_kalman=EulerSaved_kalman(:,3)*180/pi;


t=0:dt:(Nsamples-1)*dt;

figure;
subplot(2,1,1);hold on;
xlabel('Time [sec]');ylabel('Roll (\phi)');
plot(t,PhiSaved_comp);
plot(t,PhiSaved_EKF);
plot(t,PhiSaved_kalman);legend('Complimentary','EKF','kalman');

subplot(2,1,2);hold on;
xlabel('Time [sec]');ylabel('pitch (\theta)');
plot(t,ThetaSaved_comp);
plot(t,ThetaSaved_EKF);
plot(t,ThetaSaved_kalman);legend('Complimentary','EKF','kalman');

%subplot(3,1,3);hold on;
%xlabel('Time [sec]');ylabel('yaw (\psi)');
%plot(t,PsiSaved_comp);
%plot(t,PsiSaved_EKF);
%plot(t,PsiSaved_kalman);legend('Complimentary','EKF','kalman');

% comp_max=max(PhiSaved_comp);
% comp_min=min(PhiSaved_comp);
% EKF_max=max(PhiSaved_EKF);
% EKF_min=min(PhiSaved_EKF);
% kalman_max=max(PhiSaved_comp);
% kalman_min=min(PhiSaved_comp);
% 
% comp_max1=max(ThetaSaved_comp);
% comp_min1=min(ThetaSaved_comp);
% EKF_max1=max(ThetaSaved_EKF);
% EKF_min1=min(ThetaSaved_EKF);
% kalman_max1=max(ThetaSaved_comp);
% kalman_min1=min(ThetaSaved_comp);
% 
% disp('phi comp max :');disp(comp_max);disp('phi comp min:');disp(comp_min);
% disp('phi EKF max :');disp(EKF_max);disp('phi EKF min:');disp(EKF_min);
% disp('phi kalman max :');disp(kalman_max);disp('phi kalman min:');disp(kalman_min);
% 
% disp('theta comp max :');disp(comp_max1);disp('theta comp min:');disp(comp_min1);
% disp('theta EKF max :');disp(EKF_max1);disp('theta EKF min:');disp(EKF_min1);
% disp('theta kalman max :');disp(kalman_max1);disp('theta kalman min:');disp(kalman_min1);