%% Â÷·® 3D wireframe
clear;clc
FV = stlread('Hyundai+i30.stl');

x=(FV.Points(:,1)/2.3475e+04)*4.340;
y=(FV.Points(:,2)/1.0471e+04)*1.795;
z=(FV.Points(:,3)/8.3238e+03)*1.455;

data=[x';y';z';ones(1,length(x))];
R_mv=[1 0 0 3.536;0 1 0 0.8922;0 0 1 0;0 0 0 1];
R_yaw=[cos(pi) -sin(pi) 0 0;sin(pi) cos(pi) 0 0;0 0 1 0;0 0 0 1];

data2=(R_mv*R_yaw*data);
data3=[data2(1,:);data2(2,:);data2(3,:)];
data4=data3';
TR = triangulation(FV.ConnectivityList,data4);
%%
load lidar_data2.mat
angle_ver=2;
angle_hor=0.2;

figure(1);plot3(lidar_1(:,1),lidar_1(:,2),lidar_1(:,3),'r.');
hold on;plot3(lidar_2(:,1),lidar_2(:,2),lidar_2(:,3),'b.');trisurf(TR);
grid on;xlabel('x(m)');ylabel('y(m)');zlabel('z(m)');axis([-10 10 -10 10 -10 10]);

lidar1 =[lidar_1(:,1) lidar_1(:,2) lidar_1(:,3) ones(1,length(lidar_1(:,1)))']';
lidar2 =[lidar_2(:,1) lidar_2(:,2) lidar_2(:,3) ones(1,length(lidar_2(:,1)))']';

lidar1_x=0.94;lidar1_y=0.49;lidar1_z=1.76;
lidar2_x=0.9649214;lidar2_y=-0.52463 ;lidar2_z=1.8305882;

lidar1_roll=0;lidar1_pitch=0;lidar1_yaw=-0.017453;
lidar2_roll= 0.0049101 ;lidar2_pitch= 0.113957 ;lidar2_yaw=0.0447597 ;
R_yaw_1=[cos(lidar1_yaw) -sin(lidar1_yaw) 0 0;sin(lidar1_yaw) cos(lidar1_yaw) 0 0;0 0 1 0;0 0 0 1];
L_1=[1 0 0 lidar1_x;0 1 0 lidar1_y;0 0 1 lidar1_z;0 0 0 1];
lidar1=R_yaw_1*L_1*lidar1;

R_roll_2=[1 0 0 0;0 cos(lidar2_roll) -sin(lidar2_roll) 0;0 sin(lidar2_roll) cos(lidar2_roll) 0;0 0 0 1];
R_pitch_2=[cos(lidar2_pitch) 0 sin(lidar2_pitch) 0;0 1 0 0;-sin(lidar2_pitch) 0 cos(lidar2_pitch) 0;0 0 0 1];
R_yaw_2=[cos(lidar2_yaw) -sin(lidar2_yaw) 0 0;sin(lidar2_yaw) cos(lidar2_yaw) 0 0;0 0 1 0;0 0 0 1];
L_2=[1 0 0 lidar2_x;0 1 0 lidar2_y;0 0 1 lidar2_z;0 0 0 1];
lidar2=R_roll_2*R_pitch_2*R_yaw_2*L_2*lidar2;

figure(2);plot3(lidar1(1,:),lidar1(2,:),lidar1(3,:),'r.');
hold on;plot3(lidar2(1,:),lidar2(2,:),lidar2(3,:),'b.');trisurf(TR);
grid on;xlabel('x(m)');ylabel('y(m)');zlabel('z(m)');
axis([-10 10 -10 10 -10 10]);