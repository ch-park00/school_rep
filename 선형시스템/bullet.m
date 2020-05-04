x=(1/2)*[0 3 3 -3 -3 -3 -3 3 3];
y=[0 2 2 2 2 7 7 7 7];
z=(1/2)*[0 3 -3 -3 3 3 -3 -3 3];

k=[x;y;z;ones(1,length(x))];
p=[1 2 3;1 3 4;1 4 5;1 2 5];
p1=[4 5 6 7;6 7 8 9;2 3 8 9;3 4 7 8;2 5 6 9];
c=['r' 'g' 'b' 'k' 'y'];
    for i=1:4
        patch([k(1,p(i,1)) k(1,p(i,2)) k(1,p(i,3))],[k(2,p(i,1)) k(2,p(i,2)) k(2,p(i,3))],...
            [k(3,p(i,1)) k(3,p(i,2)) k(3,p(i,3))],c(i));
    end
    for j=1:5
        patch([k(1,p1(j,1)) k(1,p1(j,2)) k(1,p1(j,3)) k(1,p1(j,4))],...
            [k(2,p1(j,1)) k(2,p1(j,2)) k(2,p1(j,3)) k(2,p1(j,4))],...
            [k(3,p1(j,1)) k(3,p1(j,2)) k(3,p1(j,3)) k(3,p1(j,4))],c(j));
    end
    view([0,-50,0]);
    xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');axis([-30 30 -30 30 -30 30])
    
%%
vpoint=[0,-50,0,1]'; % 내가 바라보는 좌표
vgain=1000;
cnt=1;
for x1=0:-0.5:-25
    clf;
    psi=(x1)*10/180*pi;
    Ry=[cos(psi) 0 sin(psi) 0;0 1 0 0;-sin(psi) 0 cos(psi) 0;0 0 0 1];
    k2=Ry*k;
    k2=[1 0 0 0;0 1 0 -0.5*cnt;0 0 1 0;0 0 0 1]*k2;
    dist=sqrt((k2(1,1)-vpoint(1))^2+(k2(2,1)-vpoint(2))^2+(k2(3,1)-vpoint(3))^2);
    k1=k2/(dist^2).*vgain;
    for i=1:4
        patch([k1(1,p(i,1)) k1(1,p(i,2)) k1(1,p(i,3))],[k1(2,p(i,1)) k1(2,p(i,2)) k1(2,p(i,3))],...
            [k1(3,p(i,1)) k1(3,p(i,2)) k1(3,p(i,3))],c(i));
    end
    for j=1:5
        patch([k1(1,p1(j,1)) k1(1,p1(j,2)) k1(1,p1(j,3)) k1(1,p1(j,4))],...
            [k1(2,p1(j,1)) k1(2,p1(j,2)) k1(2,p1(j,3)) k1(2,p1(j,4))],...
            [k1(3,p1(j,1)) k1(3,p1(j,2)) k1(3,p1(j,3)) k1(3,p1(j,4))],c(j));
    end
    xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');axis([-50 50 -50 50 -50 50])
    view(vpoint(1:3));grid;cnt=cnt+1;
    pause(0.00001);
end
%%
cnt=1;
for th=0:5:360
    clf;
   th1=(5/180)*pi;
   psi=psi+((5/180)*pi);
   vpoint=[cos(th1) -sin(th1) 0 0;sin(th1) cos(th1) 0 0;0 0 1 0;0 0 0 1]*vpoint;
   Ry=[cos(psi) 0 -sin(psi) 0;0 1 0 0;sin(psi) 0 cos(psi) 0;0 0 0 1];
    k3=Ry*k2;
    k3=[1 0 0 0;0 1 0 -0.5*cnt;0 0 1 0;0 0 0 1]*k3;
    dist=sqrt((k3(1,1)-vpoint(1))^2+(k3(2,1)-vpoint(2))^2+(k3(3,1)-vpoint(3))^2);
    k1=k3/(dist^2).*vgain;
    for i=1:4
        patch([k1(1,p(i,1)) k1(1,p(i,2)) k1(1,p(i,3))],[k1(2,p(i,1)) k1(2,p(i,2)) k1(2,p(i,3))],...
            [k1(3,p(i,1)) k1(3,p(i,2)) k1(3,p(i,3))],c(i));
    end
    for j=1:5
        patch([k1(1,p1(j,1)) k1(1,p1(j,2)) k1(1,p1(j,3)) k1(1,p1(j,4))],...
            [k1(2,p1(j,1)) k1(2,p1(j,2)) k1(2,p1(j,3)) k1(2,p1(j,4))],...
            [k1(3,p1(j,1)) k1(3,p1(j,2)) k1(3,p1(j,3)) k1(3,p1(j,4))],c(j));
    end
    xlabel('x1 axis');ylabel('x2 axis');zlabel('x3 axis');axis([-50 50 -50 50 -50 50])
    view(vpoint(1:3));grid on;cnt=cnt+1;
    pause(0.00001);
end