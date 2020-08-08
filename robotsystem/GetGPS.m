%%
function [ax,ay,aVel,aYawRate,aStrAng]=GetGPS()

persistent fx fy vehVel yawRate strAng
persistent k firstrun

if isempty(firstrun)
    load('GPS_EKF_data.mat');
    fx=utmX;
    fy=utmY;
    vehVel=Vehicle_Vel;
    yawRate=Yaw_Rate;
    strAng=Steering_Ang;
    k=1;
    firstrun=1;
end

ax=fx(k);
ay=fy(k);
aVel=vehVel(k);
aYawRate=yawRate(k);
aStrAng=strAng(k);

k=k+1;