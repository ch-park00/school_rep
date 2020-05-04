%% 과제 1
px=[4 4 1 1 0 0 0 1 1 1 3 3 1 1 4];
py=[6 3 3 0 0 0 6 6 5 4 4 5 5 6 6];
cx=[4 4 8 8 5 5 8 8 4];
cy=[0 6 6 5 5 1 1 0 0];
hx=[8 8 9 9 11 11 12 12 11 11 9 9 8];
hy=[0 6 6 3.5 3.5 6 6 0 0 2.5 2.5 0 0];
x=[hx cx px;hy cy py];
figure(2)
line(x(1,:),x(2,:));axis([-15 15 -15 15]);grid on;

%% 과제4
%축소
for th=2*pi:-0.01:pi
   A=[cos(th) -sin(th);sin(th) cos(th)];clf;
   k=(th/(pi*2));
   t=k*A*x;axis([-25 25 -25 25]);grid;
   line(t(1,:),t(2,:));pause(0.0001);
end
% 확대
for th=pi:0.01:2*pi
   A=[cos(th) sin(th);-sin(th) cos(th)];clf;
   k=(th/(pi*2));
   t=k*A*x;axis([-25 25 -25 25]);grid;
   line(t(1,:),t(2,:));pause(0.0001);
end