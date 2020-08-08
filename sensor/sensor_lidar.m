%% lidar data 그려보기 : 개구각 190도로 최대 80m까지 스캔 가능.
% 차량 앞방향 : x, 차량 왼쪽 :y, 위쪽 : z

%%
clear;clc
load lidar_data.mat
angle_start=-95;

angle_res1=0.1667;
angle_res23=0.5;

angle1=angle_start : angle_res1 : angle_start+angle_res1*1140;
angle23=angle_start : angle_res23 : angle_start+angle_res23*380;

x1=cosd(angle1).*(lidar_data_1/1000);
y1=sind(angle1).*(lidar_data_1/1000);
z1=zeros(1,length(x1));

x2=cosd(angle23).*(lidar_data_2/1000);
y2=sind(angle23).*(lidar_data_2/1000);
z2=zeros(1,length(x2));

x3=cosd(angle23).*(lidar_data_3/1000);
y3=sind(angle23).*(lidar_data_3/1000);
z3=zeros(1,length(x3));

%%
figure; plot(x1,y1,'r.');axis([0 20 -10 10]);xlabel('x(m)');ylabel('y(m)');
figure; plot(x2,y2,'b.');axis([0 20 -10 10]);xlabel('x(m)');ylabel('y(m)');
figure; plot(x3,y3,'k.');axis([0 20 -10 10]);xlabel('x(m)');ylabel('y(m)');
figure; hold on; axis([0 20 -10 10]);
plot(x1,y1,'r.'); plot(x3,y3,'k.');plot(x2,y2,'b.');xlabel('x(m)');ylabel('y(m)');

%%
lidar1 =[x1;y1;z1;ones(1,length(x1))];
lidar2 =[x2;y2;z2;ones(1,length(x2))];
lidar3 =[x3;y3;z3;ones(1,length(x3))];

lidar1_roll=0;lidar1_pitch=2;lidar1_yaw=0;
lidar2_roll=0;lidar2_pitch=3;lidar2_yaw=0;
lidar3_roll=0;lidar3_pitch=1;lidar3_yaw=0;

lidar1_x=0.85;lidar1_y=0.4;lidar1_z=1.54;
lidar2_x=0.85;lidar2_y=-0.4;lidar2_z=1.54;
lidar3_x=2.68;lidar3_y=0;lidar3_z=0.45;

R_pitch_1=[cosd(lidar1_pitch) 0 sind(lidar1_pitch) 0;0 1 0 0;-sind(lidar1_pitch) 0 cosd(lidar1_pitch) 0;0 0 0 1];
L_1=[1 0 0 lidar1_x;0 1 0 lidar1_y;0 0 1 lidar1_z;0 0 0 1];
lidar1=R_pitch_1*L_1*lidar1;

R_pitch_2=[cosd(lidar2_pitch) 0 sind(lidar2_pitch) 0;0 1 0 0;-sind(lidar2_pitch) 0 cosd(lidar2_pitch) 0;0 0 0 1];
L_2=[1 0 0 lidar2_x;0 1 0 lidar2_y;0 0 1 lidar2_z;0 0 0 1];
lidar2=R_pitch_2*L_2*lidar2;

R_pitch_3=[cosd(lidar3_pitch) 0 sind(lidar3_pitch) 0;0 1 0 0;-sind(lidar3_pitch) 0 cosd(lidar3_pitch) 0;0 0 0 1];
L_3=[1 0 0 lidar3_x;0 1 0 lidar3_y;0 0 1 lidar3_z;0 0 0 1];
lidar3=R_pitch_3*L_3*lidar3;

figure;hold on;axis([0 20 -10 10 0 5]);daspect([1 1 1]);grid on;
plot3(lidar1(1,:),lidar1(2,:),lidar1(3,:),'r.');
plot3(lidar2(1,:),lidar2(2,:),lidar2(3,:),'b.');
plot3(lidar3(1,:),lidar3(2,:),lidar3(3,:),'k.');xlabel('x(m)');ylabel('y(m)');zlabel('z(m)');