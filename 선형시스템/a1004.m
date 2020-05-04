%% M모양 그래프
x=[0 1 1 4 7 7 8 8 7 4 1 0 0;...
    0 0 6 0 6 0 0 8 8 2 8 8 0;...
    1 1 1 1 1 1 1 1 1 1 1 1 1];
figure(1);line(x(1,:),x(2,:))
axis ([0 14 0 11])

%% x1 대칭
A=[1 0 0;0 -1 0;0 0 1];
y=A*x;
figure(2);
line(x(1,:),x(2,:));
line(y(1,:),y(2,:));grid on
axis([-10 10 -10 10])

%% x2대칭
A1=[-1 0 0;0 1 0;0 0 1];
y1=A1*x;
figure(3);
line(x(1,:),x(2,:));
line(y1(1,:),y1(2,:));grid on
axis([-10 10 -10 10])

%% 원점 대칭
A2=[-1 0 0;0 -1 0;0 0 1];
y2=A2*x;
figure(4);
line(x(1,:),x(2,:));
line(y2(1,:),y2(2,:));grid on
axis([-10 10 -10 10])

%% x1=x2 대칭
A3=[0 1 0;1 0 0;0 0 1];
y3=A3*x;
figure(5);
line(x(1,:),x(2,:));
line(y3(1,:),y3(2,:));grid on
axis([-10 10 -10 10])

%% x1방향으로 기울임
B=[1 0.5 0;0 1 0;0 0 1];
y4=B*x;
figure(6);
line(y4(1,:),y4(2,:));grid on
axis([-10 15 -10 10])

%% x2방향으로 기울임
B1=[1 0 0;0.5 1 0;0 0 1];
y5=B1*x;
figure(7);
line(y5(1,:),y5(2,:));grid on
axis([-10 15 -10 15])

%% 동시에 기울임

B2=[1 0.5 0;0.5 1 0;0 0 1];
y51=B2*x;
figure(8);
line(y51(1,:),y51(2,:));grid on
axis([-10 15 -10 15])
%% 평행이동
C=[1 0 2;0 1 3;0 0 1];
y6=C*x;
figure(8);
line(y6(1,:),y6(2,:));grid on
axis([-10 15 -10 15])

%% 평행이동 및 기울임
C1=[1 0 2;0 1 3;0 0 1];
B=[1 0.5 0;0 1 0;0 0 1];
y7=C1*B*x; % 평행이동 후 기울임. 두개를 곱함(덧셈은 의미가 달라짐)
figure(9);
line(y7(1,:),y7(2,:));grid on
axis([-10 15 -10 15])

%% 확대 및 축소
C=[1.3 0 0;0 1.3 0;0 0 1]; %확대 
D=[0.3 0 0;0 0.3 0;0 0 1]; %축소

v=C*x;
v1=D*x;
figure(10);
line(v(1,:),v(2,:),'color','g');hold on;grid on;axis([0 14 0 11]);
line(v1(1,:),v1(2,:),'color','r');
line(x(1,:),x(2,:),'color','b');

%% 연속적 확대 +축소(동영상)
figure(11);
for h=0:0.01:3
   E=h*[1 0 0;0 1 0;0 0 1];
   t=E*x;
   clf;axis([0 30 0 30]);
   line(t(1,:),t(2,:));
   pause(0.001);
end

for h=3:-0.01:0
   E=h*[1 0 0;0 1 0;0 0 1];
   t=E*x;
   clf;axis([0 30 0 30]);
   line(t(1,:),t(2,:));
   pause(0.001);
end

%% cw 방향 회전
figure(12);
for s=0:1:360
    th=s*pi/180;
   F=[cos(th) sin(th) 0;-sin(th) cos(th) 0;0 0 1];
   r=F*x;
   clf;axis([-20 20 -20 20]);grid on;
   line(r(1,:),r(2,:));
   pause(0.00001);
end
%% ccw 
for s=0:1:360
    th=s*pi/180;
   F=[cos(th) -sin(th) 0;sin(th) cos(th) 0;0 0 1];
   r=F*x;
   clf;axis([-20 20 -20 20]);grid on;
   line(r(1,:),r(2,:));
   pause(0.00001);
end
