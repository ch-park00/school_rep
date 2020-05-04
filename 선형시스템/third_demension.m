%%
x=[3;2;7];
figure(1);
for th=0:0.1:7*pi/3 %x1 rotation
    A=[cos(th) -sin(th) 0;sin(th) cos(th) 0;0 0 1];
    y=A*x;clf;
    subplot(311);axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y(1)],[0 y(2)],[0 y(3)]);xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    subplot(312);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y(1)],[0 y(2)],[0 y(3)]);xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    subplot(313);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y(1)],[0 y(2)],[0 y(3)]);ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end
figure(2)
for th1=0:0.1:9*pi/4 %x2 rotation
    A1=[cos(th1) 0 sin(th1);0 1 0;-sin(th1) 0 cos(th1)];
    y1=A1*y;clf;
    subplot(311);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    subplot(312);axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    subplot(313);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end
figure(3)
for th2=0:0.1:13*pi/6 %x3 rotation
    A2=[1 0 0;0 cos(th2) -sin(th2);0 sin(th2) cos(th2)];
    y2=A2*y1;clf;
    subplot(311);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    subplot(312);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    subplot(313);axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end