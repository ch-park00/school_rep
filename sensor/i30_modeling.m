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

figure;trisurf(TR);xlabel('x(m)');ylabel('y(m)');zlabel('z(m)');
axis equal

%%
figure(3);plot3(lidar1(1,:),lidar1(2,:),lidar1(3,:),'r.');
hold on;plot3(lidar2(1,:),lidar2(2,:),lidar2(3,:),'b.');trisurf(TR);
grid on;xlabel('x(m)');ylabel('y(m)');zlabel('z(m)');
axis([-10 10 -10 10 -10 10]);