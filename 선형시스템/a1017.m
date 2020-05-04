%% 팔면체 데이터

d=[0 5 5 0 -5 5 0 -5 -5 0 5 -5 0;...
    0 -5 5 0 5 5 0 5 -5 0 -5 -5 0;...
    20 0 0 20 0 0 -20 0 0 -20 0 0 20;...
    1 1 1 1 1 1 1 1 1 1 1 1 1];
% p의 각각은 벡터번호를 의미
p=[1 2 3;4 5 6;5 6 7;8 9 10;9 10 11;11 12 13;1 8 9;2 3 7];
c=['b';'r';'g';'w';'k';'c';'m';'y'];

%% x1 방향 이동하면서 yaw

orbit=[0,0,20];
for x1=0:0.15:20
    clf;
    psi=4*pi*x1/20; %x1이 20만큼 이동하는 동안 4pi만큼 회전
    Rz_u=[cos(psi) -sin(psi) 0 x1;sin(psi) cos(psi) 0 0;0 0 1 0;0 0 0 1];
    y=Rz_u*d;
    line([y(1,:) y(1,1)], [y(2,:) y(2,1)],[y(3,:) y(3,1)]);
    line([40 0 0],[0 0 0],[0 0 0],'color','r');
    line([0 0 0],[0 40 0],[0 0 0],'color','g');
    line([0 0 0],[0 0 0],[0 0 40],'color','k');
    
    orbit=[orbit;y(1,1) y(2,1) y(3,1)]; %실행시마다 orbit데이터가 추가됨(크기가 커짐)
    line(orbit(:,1), orbit(:,2),orbit(:,3));
    
    for i=1:1:8
       patch([y(1,p(i,1)) y(1,p(i,2)) y(1,p(i,3))], [y(2,p(i,1)) y(2,p(i,2)) y(2,p(i,3))],...
          [y(3,p(i,1)) y(3,p(i,2)) y(3,p(i,3))],c(i));
    end
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-60 60 -60 60 -60 60]);grid;
   pause(0.000001);
end

%% x3이동하면서 yaw
x3=0;
for deg=0:2:720
    clf;
    x1=20*cos(deg*pi/180);
    x2=20*sin(deg*pi/180);
    x3=x3-20/length(0:2:720);
    psi=deg*pi/180; %자전 2바퀴
    Rz_round=[cos(psi) -sin(psi) 0 x1;sin(psi) cos(psi) 0 x2;0 0 1 x3;0 0 0 1];
    y=Rz_round*d;
    line([y(1,:) y(1,1)], [y(2,:) y(2,1)],[y(3,:) y(3,1)]);
    line([60 0 0],[0 0 0],[0 0 0],'color','r');
    line([0 0 0],[0 60 0],[0 0 0],'color','g');
    line([0 0 0],[0 0 0],[0 0 60],'color','k');
    
    orbit=[orbit;y(1,1) y(2,1) y(3,1)];
    line(orbit(:,1), orbit(:,2),orbit(:,3));
    
    for i=1:1:8
       patch([y(1,p(i,1)) y(1,p(i,2)) y(1,p(i,3))], [y(2,p(i,1)) y(2,p(i,2)) y(2,p(i,3))],...
          [y(3,p(i,1)) y(3,p(i,2)) y(3,p(i,3))],c(i));
    end
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   axis([-60 60 -60 60 -60 60]);grid;
   pause(0.000001);
end