x=[3;2;7];
figure(1);
for th1=0:0.1*pi:2*pi
    A1=[cos(th1) 0 sin(th1);0 1 0;-sin(th1) 0 cos(th1)];
    y1=A1*x;clf;
    subplot(311);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    subplot(312);axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    subplot(313);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end
%%
x=[1;0;0];
figure(1)
for th=0:0.1:2*pi
   A=[cos(th) 0 sin(th);0 1 0;-sin(th) 0 cos(th)];
   y=A*x;
   plot3([0 y(1)],[0 y(2)],[0 y(3)],'*-');grid;
   view([0 90 0]);axis([-10 10 -10 10 -10 10]);
   xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');
   pause(0.1);clf;
   
end

%%
x=[3;2;7];
figure(1);figure(2);figure(3)
for th=0:0.1:7*pi/3 %x1 rotation
    A=[cos(th) -sin(th) 0;sin(th) cos(th) 0;0 0 1];
    y=A*x;clf;
    movegui(figure(1),'northwest');axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y(1)],[0 y(2)],[0 y(3)]);
    xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    movegui(figure(2),'north');grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y(1)],[0 y(2)],[0 y(3)]);
    xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    movegui(figure(3),'northeast');grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y(1)],[0 y(2)],[0 y(3)]);
    ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end
figure(2)
for th1=0:0.1:9*pi/4 %x2 rotation
    A1=[cos(th1) 0 sin(th1);0 1 0;-sin(th1) 0 cos(th1)];
    y1=A1*y;clf;
    subplot(311);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    subplot(312);axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    subplot(313);grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y1(1)],[0 y1(2)],[0 y1(3)]);
    ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end
figure(4);figure(5);figure(6)
for th2=0:0.1:13*pi/6 %x3 rotation
    A2=[1 0 0;0 cos(th2) -sin(th2);0 sin(th2) cos(th2)];
    y2=A2*y1;clf;
    grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);
    xlabel('x1 axis');ylabel('x2 axis');
    view([0 0 90]);
    grid on;axis([-10 10 -10 10 -10 10]);
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);
    xlabel('x1 axis');zlabel('x3 axis');
    view([0 -90 0]);
    axis([-10 10 -10 10 -10 10]);grid on;
    line([0 y2(1)],[0 y2(2)],[0 y2(3)]);
    ylabel('x2 axis');zlabel('x3 axis');
    view([90 00 00]);
    pause(0.0001)
end